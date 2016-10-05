// Title:    Function definitions for the MibrrGibbs2 class
// Author:   Kyle M. Lang
// Created:  2014-AUG-24
// Modified: 2016-MAY-15
// Purpose:  This class contains the Gibbs sampling-related functions for the
//           MIBRR package.

//--------------------- COPYRIGHT & LICENSING INFORMATION ---------------------//
//  Copyright (C) 2016 Kyle M. Lang <kyle.lang@ttu.edu>                        //  
//                                                                             //
//  This file is part of mibrr.                                                //
//                                                                             //
//  This program is free software: you can redistribute it and/or modify it    //
//  under the terms of the GNU Lesser General Public License as published by   //
//  the Free Software Foundation, either version 3 of the License, or          //
//  (at you option) any later version.                                         //
//                                                                             //
//  This program is distributed in the hope that it will be useful, but        //
//  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY //
//  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public    //
//  License for more details.                                                  //
//                                                                             //
//  You should have received a copy of the GNU Lesser General Public License   //
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.      //
//-----------------------------------------------------------------------------//

#include "MibrrGibbs2.hpp"

//////////////////////// CONSTRUCTORS / DESTRUCTOR //////////////////////////////
  
MibrrGibbs2::MibrrGibbs2() 
{
  // _beta, _tau, _nEmIters, and _nDraws need user-supplied starting values
  //_sigma             = 0.0;
  //_lambdas           = VectorXd(2);
  //_emConvTol         = 1.0e-5;
  //_lambdaWindow      = 1;
  //_drawNum           = 0;
  //_emIterNum         = 0;
  //_optIterCount      = 0;
  //_storeGibbsSamples = false;
  //_verboseErrors     = true;
  //_verboseIters      = true;
  //_useElasticNet     = true;
}


MibrrGibbs2::~MibrrGibbs2() 
{
}

/////////////////////////////////// MUTATOR /////////////////////////////////////

void MibrrGibbs2::setSimpleIntercept(bool simpleIntercept)
{
  _simpleIntercept = simpleIntercept;
}

////////////////////////// PARAMETER UPDATE FUNCTIONS ///////////////////////////

void MibrrGibbs2::updateTaus2(MibrrData2 &mibrrData)
{
  double lambda1 = _lambdas[0];
  double lambda2 = _lambdas[1];
  int nPreds = mibrrData.nPreds2(); 
  ArrayXd tauMeans;
  double tauScale = -1.0;// -1 to ensure an exception if try() fails
  
  try {
    if(_useElasticNet) {// Miben Version
      ArrayXd tauMeansNumerator = ArrayXd::Constant(nPreds, lambda1);
      
      tauMeans = tauMeansNumerator.sqrt() /
	(2.0 * lambda2 * _betas.tail(nPreds).array().abs());
      
      tauScale = lambda1 / (4.0 * lambda2 * _sigma); 
    }
    else {// MIBL Version
      double tauMeansNumerator = pow(lambda1, 2) * _sigma;
      
      tauMeans =
	(tauMeansNumerator / _betas.tail(nPreds).array().square()).sqrt();
      
      tauScale = pow(lambda1, 2);
    }
    if((tauMeans <= 0.0).any()) throw 1;
    if(tauScale <= 0.0) throw 2;
  }
  catch (int e) { tauError(e); }
  
  // Draw new values of the auxiliary penalty parameters:
  ArrayXd tmpDraws(nPreds);
  for(int i = 0; i < nPreds; i++)
    tmpDraws[i] = drawInvGauss(tauMeans[i], tauScale);
  
  ArrayXd newTaus;
  if(_useElasticNet) newTaus = (tmpDraws + 1.0) / tmpDraws; // MIBEN Version   
  else               newTaus = 1.0 / tmpDraws;              // MIBL Version
  
  _taus = newTaus;// Store the updated Taus
  
  // Add the updated Taus to their Gibbs sample:
  if(_storeGibbsSamples) _tauSam.row(_drawNum) = newTaus.transpose();
}// END updateTaus2()


void MibrrGibbs2::updateBetas2(MibrrData2 &mibrrData)
{
  int nPreds = mibrrData.nPreds2();
  int nObs = mibrrData.nResponses(_targetIndex);
  LDLT <MatrixXd> aMatrixCholesky;
  MatrixXd tmpMat;

  if(_useElasticNet) {// MIBEN Version
    double lambda2 = _lambdas[1];
    VectorXd transformedTaus = _taus / (_taus - 1.0);
    tmpMat = lambda2 * transformedTaus.asDiagonal();    
  }
  else {// MIBL Version
    VectorXd transformedTaus = 1.0 / _taus;
    tmpMat = transformedTaus.asDiagonal();
  }
  
  MatrixXd aMatrix;
  aMatrix = mibrrData.getIVs2(_targetIndex).transpose() *
    mibrrData.getIVs2(_targetIndex) + tmpMat;
  
  VectorXd betaMeans;
  MatrixXd betaCovariances;
  try {
    // Compute the Cholesky decomposition of the IV's penalized crossproducts,
    // and use it to compute the moments of beta's fully conditional posterior:
    aMatrixCholesky.compute(aMatrix);
    betaMeans =
      aMatrixCholesky.solve(mibrrData.getIVs2(_targetIndex).transpose() *
			    mibrrData.getDV(_targetIndex)); 
    
    tmpMat = _sigma * MatrixXd::Identity(nPreds, nPreds);   
    betaCovariances = aMatrixCholesky.solve(tmpMat);
  }
  catch(exception &e) { betaError(e); }

  // Draw a new value of the intercept term:
  VectorXd newBetas(nPreds + 1);
  double intMean;
  if(_simpleIntercept)
    intMean = mibrrData.getDV(_targetIndex).mean();
  else
    intMean = mibrrData.getDV(_targetIndex).mean() -
      mibrrData.getIVs2(_targetIndex).colwise().mean() * _betas.tail(nPreds);
  double intSd = sqrt(_sigma / double(nObs));
  newBetas[0] = R::rnorm(intMean, intSd);
  
  // Draw new values of the regression slope coefficients:
  newBetas.tail(nPreds) = mibrrData.drawMVN(betaMeans, betaCovariances);
  
  _betas = newBetas;// Store the updated Betas
  
  // Add the updated Betas to their Gibbs sample:
  if(_storeGibbsSamples) _betaSam.row(_drawNum) = newBetas.transpose();
}// END updateBetas2()
    

void MibrrGibbs2::updateSigma2(MibrrData2 &mibrrData)
{
  int nPreds = mibrrData.nPreds2();
  int nObs = mibrrData.nResponses(_targetIndex);
  double lambda1 = _lambdas[0];
  double lambda2 = _lambdas[1];
  VectorXd tmpBiasVector = VectorXd::Ones (nObs);
  double newSigma;

  // Compute the regularized residual sum of squares:
  double sse =
    (mibrrData.getDV(_targetIndex) - _betas[0] * tmpBiasVector -
     mibrrData.getIVs2(_targetIndex) * _betas.tail(nPreds)).transpose() *
    (mibrrData.getDV(_targetIndex) - _betas[0] * tmpBiasVector -
     mibrrData.getIVs2(_targetIndex) * _betas.tail(nPreds));
  
  if(_useElasticNet) {// MIBEN Version
    double scaleSum =
      (_taus / (_taus - 1.0) * _betas.tail(nPreds).array().square()).sum();
    
    double sigmaShape = (double(nObs) / 2.0) + double(nPreds);
    double sigmaScale = 0.5 * (sse + lambda2 * scaleSum +
			       (pow(lambda1, 2) / (4.0 * lambda2)) * _taus.sum()
			       );
    
    bool isDrawValid = false;
    double testDraw;
    while(!isDrawValid) {// Rejection sampling to draw a Sigma variate
      testDraw = drawInvGamma(sigmaShape, sigmaScale);
      double thresholdDraw = unif_rand();
      double uiGammaShape = pow(lambda1, 2) / (8.0 * testDraw * lambda2);
      double uiGammaDraw = calcIncGamma(0.5, uiGammaShape, false);
      isDrawValid = log(thresholdDraw) <= (double(nPreds) * log(tgamma(0.5))) -
	(double(nPreds) * log(uiGammaDraw));
      Rcpp::checkUserInterrupt();
    };
    newSigma = testDraw;
  }
  else {// MIBL Version
    VectorXd transformedTaus = 1.0 / _taus;
    MatrixXd tmpMat = transformedTaus.asDiagonal();
    
    double penaltyTerm =
      _betas.tail(nPreds).transpose() * tmpMat * _betas.tail(nPreds);
    double sigmaShape = 0.5 * ((double(nObs) - 1.0) + double(nPreds));
    double sigmaScale = 0.5 * (sse + penaltyTerm);
    
    // Draw a new sigma variate:
    newSigma = drawInvGamma(sigmaShape, sigmaScale);
  }
  
  _sigma = newSigma;// Store the updated Sigma
  
  // Add the updated sigma to its Gibbs sample:
  if(_storeGibbsSamples) _sigmaSam[_drawNum] = newSigma;
}// END updateSigma2()


void MibrrGibbs2::updateImputations2(MibrrData2 &mibrrData)
{
  int nObs = mibrrData.nObs();
  int nPreds = mibrrData.nPreds2();
  ArrayXb nonresponseVector = mibrrData.getNonresponseVector(_targetIndex);
  VectorXd tmpBiasVector = VectorXd::Ones(nObs);
  double tmpSd = sqrt(_sigma);
  VectorXd errorVector(nObs);
  
  // Draw the residual error terms for the imputation model:
  for(int i = 0; i < nObs; i++) errorVector[i] = R::rnorm(0.0, tmpSd);
  
  // Draw a vector of imputations from the posterior predictive distribution
  // of the missing data:
  VectorXd tmpImps = _betas[0] * tmpBiasVector +
    mibrrData.getFullIVs2(_targetIndex) * _betas.tail(nPreds) + errorVector;
  
  // Replace the missing data in the target variable with the imputations:
  for(int i = 0; i < nObs; i++)
    if(nonresponseVector[i] == true)
      mibrrData.setElement(tmpImps[i], i, _targetIndex);
  
  // Add the updated imputations to their Gibbs sample:
  if(_storeGibbsSamples) _impSam.row(_drawNum) = tmpImps.transpose();
}// END updateImputations2()


void MibrrGibbs2::doGibbsIteration2(MibrrData2 &mibrrData)
{  
  updateTaus2(mibrrData);
  updateBetas2(mibrrData);
  updateSigma2(mibrrData);
  updateImputations2(mibrrData);
  
  if(_storeGibbsSamples) _drawNum++;
}// END doGibbsIteration2()




double MibrrGibbs2::eNetLambdaObjective2(const std::vector<double> &lambdaVec,
					 std::vector<double> &gradVec,
					 void *extraOptData)
{
  bool nanLambdas = isnan(lambdaVec[0]) | isnan(lambdaVec[1]) |
    lambdaVec[0] != lambdaVec[0] | lambdaVec[1] != lambdaVec[1];
  
  if(nanLambdas) 
    throw invalid_argument("An Elastic Net penalty parameter is NaN.");  
  
  _optIterCount++; // Track the number of function evaluations
  
  int nPreds = _tauSam.cols();
  int nSams = _tauSam.rows();

  // BEGIN compute LL and gradient terms.
  ArrayXd tmpArray = 2.0 * _sigmaSam;
  double w1 = nPreds * log(lambdaVec[0]);
  ArrayXd w2 = lambdaVec[1] / tmpArray;
  ArrayXd w3 = 1 / tmpArray;
  
  tmpArray = 8.0 * _sigmaSam * lambdaVec[1];
  ArrayXd w4 = pow(lambdaVec[0], 2) / tmpArray;
  double w5 = nPreds / lambdaVec[0];
  double w6 = (nPreds * lambdaVec[0]) / (4.0 * lambdaVec[1]);
  
  tmpArray = 4.0 * _sigmaSam * lambdaVec[1];
  ArrayXd w7 = lambdaVec[0] / tmpArray;
  double w8 = (nPreds * pow(lambdaVec[0], 2)) / (8.0 * pow(lambdaVec[1], 2));
  
  tmpArray = 8.0 * _sigmaSam * pow(lambdaVec[1], 2);
  ArrayXd w9 = pow(lambdaVec[0], 2) / tmpArray;
  
  ArrayXd uiGammaArray(nSams); 
  for(int i = 0; i < nSams; i++)
    uiGammaArray[i] = R::pgamma(w4[i], 0.5, 1.0, 0, 0) * tgamma(0.5);
  
  ArrayXd term1 = uiGammaArray.log();
  ArrayXd term2 =
    ((_tauSam / (_tauSam - 1)) * _betaSam.array().square()).rowwise().sum();
  // END compute LL and gradient terms.
  
  if(!gradVec.empty()) {// Calculate the gradient vector:
    ArrayXd term3 = (1 / uiGammaArray) * (1 / w4.sqrt()) * (-1.0 * w4).exp() *
      (1 / _sigmaSam.array());
    gradVec[0] = (w5 + (w6 * term3) - w7 * _tauSam.rowwise().sum()).mean();
    gradVec[1] =
      (-1.0 * (w8 * term3) - (w3 * term2) + w9 * _tauSam.rowwise().sum()).mean();
  }
  
  // Calculate and return the objective value:
  return (w1 - (nPreds * term1) - (w2 * term2) -
	  (w4 * _tauSam.rowwise().sum())).mean();
}// END eNetLambdaObjective2()


// As suggested by the nlopt authors, specify a simple  wrapper function for
// eNetLambdaObjective() so that nlopt will run inside the MibrrGibbs class:
double eNetObjectiveWrap2(const std::vector<double> &lambdaVec, 
			  std::vector<double> &gradVec, 
			  void *extraOptData) 
{
  MibrrGibbs2 *obj = static_cast<MibrrGibbs2 *>(extraOptData);   
  return obj -> eNetLambdaObjective2(lambdaVec, gradVec, extraOptData);
}// END eNetObjectiveWrap2()


void MibrrGibbs2::optimizeMibenLambdas2(bool preOptimize) 
{
  std::vector<double> lambdaVec(2), gradVec(2), lamBounds(2);
  lambdaVec[0] = _lambdas[0];
  lambdaVec[1] = _lambdas[1];
  gradVec[0] = 0.0;
  gradVec[1] = 0.0;
  lamBounds[0] = 1.0e-4; // Set low bounds slightly above zero to avoid dividing 
  lamBounds[1] = 1.0e-4; // by zero when no regularization is needed.
  _optMethod = 0;
  nlopt::algorithm optAlg;
  string algName, outPrefix; 
  bool optimized = false;
  
  while(!optimized) {//Try different algorithms until convergence
    if(preOptimize) {
      _optPrefix = "pre-";
      if(_optMethod == 0) {
	optAlg = nlopt::LN_BOBYQA;
	_algName = "BOBYQA";
      }
      else if(_optMethod == 1) {
	optAlg = nlopt::LN_COBYLA;
	_algName = "COBYLA";
      }
      else if(_optMethod == 2) {
	optAlg = nlopt::LN_SBPLX;
	_algName = "SBPLX";
      }
      else if(_optMethod == 3) {
	optAlg = nlopt::LN_PRAXIS;
	_algName = "PRAXIS";
      }
    }
    else {
      _optPrefix = "";
      if(_optMethod == 0) {
	optAlg = nlopt::LD_MMA;
	_algName = "MMA";
      }
      else if(_optMethod == 1) {
	optAlg = nlopt::LD_VAR2;
	_algName = "VAR2";
      }
      else if(_optMethod == 2) {
	optAlg = nlopt::LD_VAR1;
	_algName = "VAR1";
      }
      else if(_optMethod == 3) {
	optAlg = nlopt::LD_LBFGS;
	_algName = "LBFGS";
      }
    }// END if(preOptimize}
    
    nlopt::opt myOptimizer(optAlg, 2);       // Initialize the optimizer object
    myOptimizer.set_max_objective(eNetObjectiveWrap2, this);
    myOptimizer.set_ftol_rel(_emConvTol);    // Stopping criterion
    myOptimizer.set_lower_bounds(lamBounds); // Force positive Lambdas	
    
    nlopt::result myResult;
    double maxLL = 0.0;
    try {
      myResult = myOptimizer.optimize(lambdaVec, maxLL);  
      if(myResult < 0) {            // Catch nlopt failure codes
	_optMethod ++;              // Try the next algorithm
	lambdaVec[0] = _lambdas[0]; // Reset the lambdas
	lambdaVec[1] = _lambdas[1];
	lambdaError();
      }
      else if(myResult > 0) {// Successful convergence!
	if(_verbose) {
	  cout << "Lambdas " << _optPrefix << "optimized with " << _algName;
	  cout << " in " << _optIterCount << " iterations" << endl;
	}	
	optimized = true;
      } 
    }
    catch(int &e) {
      throw e;
    }
    catch(exception &e) {        //Catch Lambdas == NaN
      _optMethod ++;             // Try the next algorithm
      lambdaVec[0] = _lambdas[0];
      lambdaVec[1] = _lambdas[1];// Reset lambdas
      lambdaError(e);
    }  
    _optIterCount = 0;
  }// END while(!optimized)      
  // Store the updated penalty parameters:
  _lambdas[0] = lambdaVec[0];
  _lambdas[1] = lambdaVec[1];
  _lambdaHistory.row(_emIterNum) = _lambdas.transpose();
}// END optimizeMibenLambdas2()


void MibrrGibbs2::updateLambdas2()
{
  if(_useElasticNet) {// MIBEN version
    // For MIBEN, optimization is done in two stages:
    // 1) A rough, gradient-free, pre-optimization is done to move the estimates
    //    into the neighborhood of the MLE.
    // 2) Gradient-based optimization is used to fine-tune the estimates from
    //    Step (1).
    optimizeMibenLambdas2(true);  // Pre-optimization
    optimizeMibenLambdas2(false); // Optimization    
  }
  else {// MIBL version:
    int nPreds = _tauSam.cols();
    
    // For MIBL, optimization is done via the closed-form update rule given by
    // Park and Casella (2008).
    double lambdaDenominator = (_tauSam.colwise().mean()).sum();
    double newLambda = sqrt((2.0 * double(nPreds)) / lambdaDenominator); 
    _lambdas[0] = newLambda;
    _lambdaHistory(_emIterNum, 0) = _lambdas[0];
  }
  
  // Do some housekeeping:
  _emIterNum++;
  _storeGibbsSamples = false;
  _drawNum = 0;
}// END updateLambdas2()
