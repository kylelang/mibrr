// Title:    Function definitions for the MibrrGibbs class
// Author:   Kyle M. Lang
// Created:  2014-AUG-24
// Modified: 2017-NOV-06
// Purpose:  This class contains the Gibbs sampling-related functions for the
//           MIBRR package.

//--------------------- COPYRIGHT & LICENSING INFORMATION ---------------------//
//  Copyright (C) 2017 Kyle M. Lang <k.m.lang@uvt.nl>                          //  
//                                                                             //
//  This file is part of MIBRR.                                                //
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

#include "MibrrGibbs.hpp"

//////////////////////// CONSTRUCTORS / DESTRUCTOR //////////////////////////////
  
MibrrGibbs::MibrrGibbs() 
{
  // _beta, _tau, and _nDraws need user-supplied starting values
  _sigma             = 0.0;
  _lambdas           = VectorXd(2);
  _drawNum           = 0;
  _storeGibbsSamples = false;
  _verbose           = true;
  _useElasticNet     = true;
}


MibrrGibbs::~MibrrGibbs() {}

//////////////////////////////// ACCESSORS //////////////////////////////////////

VectorXd MibrrGibbs::getBetas()           const { return _betas;                }
ArrayXd  MibrrGibbs::getTaus()            const { return _taus;                 }
double   MibrrGibbs::getSigma()           const { return _sigma;                }
MatrixXd MibrrGibbs::getBetaSam()         const { return _betaSam;              }
ArrayXXd MibrrGibbs::getTauSam()          const { return _tauSam;               }
VectorXd MibrrGibbs::getSigmaSam()        const { return _sigmaSam;             }
MatrixXd MibrrGibbs::getImpSam()          const { return _impSam;               }
int      MibrrGibbs::getNDraws()          const { return _nDraws;               }
bool     MibrrGibbs::getVerbosity()       const { return _verbose;              }
bool     MibrrGibbs::getElasticNetFlag()  const { return _useElasticNet;        }
bool     MibrrGibbs::getDoImp()           const { return _doImp;                }
bool     MibrrGibbs::getSimpleIntercept() const { return _simpleIntercept;      }


VectorXd MibrrGibbs::getLambdas() const
{ 
  VectorXd outLam;
  if(_useElasticNet) outLam = _lambdas;
  else               outLam = VectorXd::Constant(1, _lambdas[0]);
  return outLam; 
}


double MibrrGibbs::getLambdas(int index) const 
{ 
  return _lambdas[index - 1]; 
}


//////////////////////////////// MUTATORS ///////////////////////////////////////


void MibrrGibbs::setBetas      (VectorXd &betas)   { _betas = betas;            }
void MibrrGibbs::setTaus       (ArrayXd &taus)     { _taus = taus;              }
void MibrrGibbs::setSigma      (double sigma)      { _sigma = sigma;            }
void MibrrGibbs::setTargetIndex(int index)         { _targetIndex = index;      }
void MibrrGibbs::setNDraws     (int nDraws)        { _nDraws = nDraws;          }
void MibrrGibbs::setDoImp      (bool doImp)        { _doImp = doImp;            }
void MibrrGibbs::beQuiet       ()                  { _verbose = false;          }
void MibrrGibbs::doBl          ()                  { _useElasticNet = false;    }
void MibrrGibbs::useSimpleInt  ()                  { _simpleIntercept = true;   }
void MibrrGibbs::setLambdas    (VectorXd& lambdas) { _lambdas = lambdas;        }


void MibrrGibbs::setLambdas(double lambda1, double lambda2) 
{
  _lambdas[0] = lambda1;
  _lambdas[1] = lambda2;
}


void MibrrGibbs::setLambdas(double lambda) 
{
  _lambdas[0] = lambda;
  _lambdas[1] = 0.0;
}


void MibrrGibbs::startParameters(VectorXd &betaStarts,
				 ArrayXd  &tauStarts,
				 double   sigmaStart,
				 double   lambda1Start,
				 double   lambda2Start)
{
  _betas         = betaStarts;
  _taus          = tauStarts;
  _sigma         = sigmaStart;
  _lambdas[0]    = lambda1Start;
  _lambdas[1]    = lambda2Start;
}


void MibrrGibbs::startParameters(VectorXd &betaStarts,
				 ArrayXd  &tauStarts,
				 double   sigmaStart,
				 VectorXd &lambdaStartVec)
{
  _betas         = betaStarts;
  _taus          = tauStarts;
  _sigma         = sigmaStart;
  _lambdas       = lambdaStartVec;
}


void MibrrGibbs::startGibbsSampling(const MibrrData &mibrrData)
{
  if(_doImp) {
    int nMiss = mibrrData.nMiss(_targetIndex);
    _impSam   = MatrixXd(_nDraws, nMiss);
  }
  else {
    _impSam = MatrixXd::Zero(1, 1);
  }
  
  _betaSam  = MatrixXd(_nDraws, _betas.size());
  _tauSam   = MatrixXd(_nDraws, _taus.size());
  _sigmaSam = VectorXd(_nDraws);
  
  _storeGibbsSamples = true;
}


/////////////////////////// RANDOM VARIATE SAMPLERS /////////////////////////////


double MibrrGibbs::drawInvGamma(double shape, double scale) const
{
  return 1.0 / R::rgamma(shape, 1.0 / scale);
}//END drawInvGamma()


double MibrrGibbs::calcIncGamma(const double shape, 
				const double cutVal,
				const bool   lowerTail)
{
  double scale   = 1.0;
  int    lower   = (int)lowerTail;
  int    logTran = 0; // Don't want log transform
  
  return R::pgamma(cutVal, shape, scale, lower, logTran) * tgamma(shape);
}// END calcIncGamma()


double MibrrGibbs::drawInvGauss(const double mu, const double lambda)
{ 
  double b      = 0.5 * mu / lambda;
  double a      = mu * b;
  double c      = 4.0 * mu * lambda;
  double d      = pow(mu, 2);
  double outVal = 0.0;

  while(outVal <= 0.0) {
    double tmpDraw = norm_rand();
    double         v = pow(tmpDraw, 2); // Chi-Squared with df = 1
    if (mu <= 0.0) {
      throw invalid_argument("The Inverse Gaussian's mean is non-positive.\n");  
    }
    else if (lambda <= 0.0) { 
      throw invalid_argument("The Inverse Gaussian's scale is non-positive.\n");
    }
    else {
      double u = unif_rand();
      //Find the smallest root:
      double x = mu + a * v - b * sqrt(c * v + d * pow(v, 2));
      // Choose x with probability = mean / (mean + x), else choose d/x:
      outVal = ( u < ( mu / (mu + x) ) ) ? x : d / x; 
    }  
  }// CLOSE while(outVal !> 0.0)
  return outVal;
}// END drawInvGauss()


////////////////////////// PARAMETER UPDATE FUNCTIONS ///////////////////////////


void MibrrGibbs::updateTaus(const MibrrData &mibrrData)
{
  int     nPreds   = mibrrData.nPreds();
  double  tauScale = -1.0; // -1 to ensure an exception if try() fails
  ArrayXd tauMeans;
  
  try {
    if(_useElasticNet) {// Miben Version
      ArrayXd tauMeansNumerator = ArrayXd::Constant(nPreds, _lambdas[0]);
      
      tauMeans = tauMeansNumerator.sqrt() /
	(2.0 * _lambdas[1] * _betas.tail(nPreds).array().abs());
      
      tauScale = _lambdas[0] / (4.0 * _lambdas[1] * _sigma);
    }
    else {// MIBL Version
      double tauMeansNumerator = pow(_lambdas[0], 2) * _sigma;
      
      tauMeans =
	(tauMeansNumerator / _betas.tail(nPreds).array().square()).sqrt();
      
      tauScale = pow(_lambdas[0], 2);
    }
    if((tauMeans <= 0.0).any()) throw 1;
    if(tauScale <= 0.0)         throw 2;
  }
  catch(int e) { tauError(e); }
  
  // Draw new values of the auxiliary penalty parameters:
  ArrayXd tmpDraws(nPreds);
  for(int i = 0; i < nPreds; i++)
    tmpDraws[i] = drawInvGauss(tauMeans[i], tauScale);
  
  ArrayXd newTaus;
  if(_useElasticNet) newTaus = (tmpDraws + 1.0) / tmpDraws; // MIBEN Version   
  else               newTaus = 1.0 / tmpDraws;              // MIBL Version
  
  _taus = newTaus; // Store the updated Taus
  
  // Add the updated Taus to their Gibbs sample:
  if(_storeGibbsSamples) _tauSam.row(_drawNum) = newTaus.transpose();
}// END updateTaus()



void MibrrGibbs::updateBetas(const MibrrData &mibrrData)
{
  int             nPreds = mibrrData.nPreds();
  int             nObs   = mibrrData.nResp(_targetIndex);
  MatrixXd        tmpMat;
  LDLT <MatrixXd> aMatrixCholesky;
  
  if(_useElasticNet) {// MIBEN Version
    VectorXd transformedTaus = _taus / (_taus - 1.0);
    tmpMat = _lambdas[1] * transformedTaus.asDiagonal();    
  }
  else {// MIBL Version
    VectorXd transformedTaus = 1.0 / _taus;
    tmpMat = transformedTaus.asDiagonal();
  }
  
  MatrixXd aMatrix;
  aMatrix = mibrrData.getIVs(_targetIndex, true).transpose() *
    mibrrData.getIVs(_targetIndex, true) + tmpMat;
  
  VectorXd betaMeans;
  MatrixXd betaCovariances;
  try {
    // Compute the Cholesky decomposition of the IV's penalized crossproducts,
    // and use it to compute the moments of beta's fully conditional posterior:
    aMatrixCholesky.compute(aMatrix);
    betaMeans =
      aMatrixCholesky.solve(mibrrData.getIVs(_targetIndex, true).transpose() *
			    mibrrData.getDV(_targetIndex)); 
    
    tmpMat = _sigma * MatrixXd::Identity(nPreds, nPreds);   
    betaCovariances = aMatrixCholesky.solve(tmpMat);
  }
  catch(exception &e) { betaError(e); }

  // Draw a new value of the intercept term:
  double intSd = sqrt(_sigma / double(nObs));
  double intMean;
  if(_simpleIntercept)
    intMean = mibrrData.getDV(_targetIndex).mean();
  else
    intMean = mibrrData.getDV(_targetIndex).mean() -
      mibrrData.getIVs(_targetIndex, true).colwise().mean() *
      _betas.tail(nPreds);
  
  VectorXd newBetas(nPreds + 1);  
  newBetas[0] = R::rnorm(intMean, intSd);
  
  // Draw new values of the regression slope coefficients:
  newBetas.tail(nPreds) = mibrrData.drawMVN(betaMeans, betaCovariances);
  
  _betas = newBetas; // Store the updated Betas
  
  // Add the updated Betas to their Gibbs sample:
  if(_storeGibbsSamples) _betaSam.row(_drawNum) = newBetas.transpose();
}// END updateBetas()
    


void MibrrGibbs::updateSigma(const MibrrData &mibrrData)
{
  double   newSigma;
  int      nPreds        = mibrrData.nPreds();
  int      nObs          = mibrrData.nResp(_targetIndex);
  VectorXd tmpBiasVector = VectorXd::Ones(nObs);
  
  // Compute the regularized residual sum of squares:
  double sse =
    (mibrrData.getDV(_targetIndex) - _betas[0] * tmpBiasVector -
     mibrrData.getIVs(_targetIndex, true) * _betas.tail(nPreds)).transpose() *
    (mibrrData.getDV(_targetIndex) - _betas[0] * tmpBiasVector -
     mibrrData.getIVs(_targetIndex, true) * _betas.tail(nPreds));
  
  if(_useElasticNet) {// MIBEN Version
    double scaleSum =
      (_taus / (_taus - 1.0) * _betas.tail(nPreds).array().square()).sum();
    
    double sigmaShape = (double(nObs) / 2.0) + double(nPreds);
    double sigmaScale =
      0.5 * (sse + _lambdas[1] * scaleSum +
	     (pow(_lambdas[0], 2) / (4.0 * _lambdas[1])) * _taus.sum());
    
    bool   isDrawValid = false;
    double testDraw;
    while(!isDrawValid) {// Rejection sampling to draw a Sigma variate
      testDraw         = drawInvGamma(sigmaShape, sigmaScale);
      double threshold = unif_rand();
      double igShape   = pow(_lambdas[0], 2) / (8.0 * testDraw * _lambdas[1]);
      double igDraw    = calcIncGamma(0.5, igShape, false);
      isDrawValid      = log(threshold) <=
	(double(nPreds) * log(tgamma(0.5))) - (double(nPreds) * log(igDraw));
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
  
  _sigma = newSigma; // Store the updated Sigma
  
  // Add the updated sigma to its Gibbs sample:
  if(_storeGibbsSamples) _sigmaSam[_drawNum] = newSigma;
}// END updateSigma()



void MibrrGibbs::updateImputations(MibrrData &mibrrData)
{
  int         nMiss         = mibrrData.nMiss(_targetIndex);
  int         nPreds        = mibrrData.nPreds();
  VectorXd    tmpBiasVector = VectorXd::Ones(nMiss);
  VectorXd    errorVector(nMiss);
  
  // Draw the residual error terms for the imputation model:
  for(int i = 0; i < nMiss; i++) errorVector[i] = R::rnorm(0.0, sqrt(_sigma));
  
  // Draw a vector of imputations from the posterior predictive distribution
  // of the missing data:
  VectorXd tmpImps = _betas[0] * tmpBiasVector +
    mibrrData.getIVs(_targetIndex, false) * _betas.tail(nPreds) + errorVector;
  
  // Replace the missing data in the target variable with the imputations:
  mibrrData.fillMissing(tmpImps, _targetIndex);
  
  // Add the updated imputations to their Gibbs sample:
  if(_storeGibbsSamples) _impSam.row(_drawNum) = tmpImps.transpose();
}// END updateImputations()



void MibrrGibbs::doGibbsIteration(MibrrData &mibrrData)
{  
  updateTaus (mibrrData);
  updateBetas(mibrrData);
  updateSigma(mibrrData);
  if(_doImp) updateImputations(mibrrData);
  
  if(_storeGibbsSamples) _drawNum++;
}// END doGibbsIteration()


///////////////////////// EXCEPTION HANDLING FUNCTIONS //////////////////////////


void MibrrGibbs::tauError(int errorCode) const
{
  if(errorCode == 1) {
    Rcpp::Rcout << "\n";
    Rcpp::stop("Ouch! My tau is broken :(\nSomething terrible has occured \
while updating Tau,\nand one of its mean values is non-positive.\n");
  }
  else if (errorCode == 2) {
    Rcpp::Rcout << "\n";
    Rcpp::stop("Ouch! My tau is broken :(\nSomething terrible has occured \
while updating Tau,\nand one of its scale values is non-positive.\n");
  }
}



void MibrrGibbs::betaError(exception &e) const
{
  Rcpp::Rcerr << e.what() << endl;
  Rcpp::stop("Something terrible has occured while updating Beta.\nAbove this \
message, I've printed the that exception I caught.\nBeta luck next time.");
}