// Title:    Gibbs Sampler for MIBEN & MIBL
// Author:   Kyle M. Lang
// Created:  2014-AUG-20
// Modified: 2015-FEB-25
// Purpose:  This code is part of the R package mibrr.
//           This function will do the Gibbs sampling for Multiple
//           Imputation with the Bayesian Elastic Net (MIBEN)
//           and Multiple Impution with the Bayesian LASSO (MIBL).

//--------------------- COPYRIGHT & LICENSING INFORMATION ---------------------//
//    Copyright (C) 2015 Kyle M. Lang <kylelang@ku.edu>                        //  
//                                                                             //
//    This program is free software: you can redistribute it and/or modify     //
//    it under the terms of the GNU General Public License as published by     //
//    the Free Software Foundation, either version 3 of the License, or        //
//    (at your option) any later version.                                      //
//                                                                             //
//    This program is distributed in the hope that it will be useful,          //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of           //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            //
//    GNU General Public License for more details.                             //
//                                                                             //
//    You should have received a copy of the GNU General Public License        //
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.    //
//-----------------------------------------------------------------------------//

#include <RcppEigen.h>

#include "MyParams.hpp"
#include "MyData.hpp"
#include "MyGibbs.hpp"

//#include <RcppEigen.h>

//using namespace std;
//using namespace Eigen;

// [[Rcpp::export]]
Rcpp::List runGibbs(Eigen::MatrixXd inData,
		    Eigen::VectorXd dataMeans,
		    Eigen::VectorXd dataScales,
		    int nTargets,  
		    Eigen::VectorXd lambda1Starts,
		    Eigen::VectorXd lambda2Starts,
		    Eigen::VectorXd sigmaStarts,
		    Eigen::MatrixXd tauStarts,
		    Eigen::MatrixXd betaStarts,
		    double missCode,
		    int nEmApproxIters,
		    int nEmTuneIters,
		    int emApprox_nBurnIns,
		    int emApprox_gibbsSampleSize,
		    int emTune_nBurnIns,		   
		    int emTune_gibbsSampleSize,
		    int posteriorGibbs_nBurnIns,
		    int posteriorGibbs_gibbsSampleSize,
		    int lambdaWindow,
		    double emConvTol,
		    bool verboseIters,
		    bool verboseErrors,
		    bool doMibl)
{
  // Initialize the various classes needed below:
  MyData myData(inData, 
		dataMeans,
		dataScales,
		missCode);
  MyGibbs *myGibbs = new MyGibbs[nTargets];
  
  // Specify some useful constants:
  int nPreds = myData.nPreds();
  int nObs = myData.nObs();
  int nTotalEmIters = nEmApproxIters + nEmTuneIters;
   
  // Initialize all parameters and setup 
  // the Gibbs sampler and the EM Optimization:
  myData.fillMissing(nTargets);
  for(int j = 0; j < nTargets; j++) {

    if(doMibl)// Are we running MIBL? 
      myGibbs[j].doMibl();

    Eigen::VectorXd betaStartVec = betaStarts.col(j);
    Eigen::ArrayXd tauStartArray =
      tauStarts.col(j).array();

    // Must call setupOptimizer() before startParameters()!
    myGibbs[j].setupOptimizer(nTotalEmIters,
			      lambdaWindow,
			      emConvTol);
    if(doMibl) 
      myGibbs[j].setupOptimizer(nTotalEmIters,
				lambdaWindow);

    myGibbs[j].startParameters(betaStartVec,
			       tauStartArray,
			       sigmaStarts[j],
			       lambda1Starts[j],
			       lambda2Starts[j]);
    
    myGibbs[j].setVerbosity(verboseIters, verboseErrors);
    myGibbs[j].setTargetIndex(j); 
  }
  
  // Specify containers for the parameters' starting values:
  Eigen::MatrixXd dvStartMat = MatrixXd(nObs, nTargets);

  for (int k = 0; k < (nTotalEmIters + 1); k++) {// LOOP over MCEM iterations
    int emIterNum = k + 1;
    int nGibbsIters, nBurnIns, nPosteriorBurnIns;
    if(k < nEmApproxIters) {
      // Small gibbs samples for EM burn in
      nGibbsIters = emApprox_gibbsSampleSize + emApprox_nBurnIns;
      nBurnIns = emApprox_nBurnIns;
    } 
    else if( (k >= nEmApproxIters) & (k < nTotalEmIters) ) {
      // Large gibbs samples for EM tuning phase
      nGibbsIters = emTune_gibbsSampleSize + emTune_nBurnIns;
      nBurnIns = emTune_nBurnIns;
    } 
    else {
      // Large final gibbs sample from the convergent model
      nPosteriorBurnIns = 
	posteriorGibbs_nBurnIns < 0 ? emTune_nBurnIns : posteriorGibbs_nBurnIns;
      nGibbsIters = nPosteriorBurnIns + posteriorGibbs_gibbsSampleSize;
      nBurnIns = nPosteriorBurnIns;
    }
    
    if(verboseIters) {
      if(k < nEmApproxIters) {
	cout << "\nDoing MCEM approximation iteration " << emIterNum;
	cout << " of " << nEmApproxIters << "\n" << endl;
      } 
      else if(k == nTotalEmIters) {
	cout << "\nSampling from the stationary posterior\n" << endl;
      }
      else {
	cout << "\nDoing MCEM tuning iteration " << emIterNum - nEmApproxIters;
	cout << " of " << nEmTuneIters << "\n" << endl;
      }
    }
    
    for (int i = 0; i < nGibbsIters; i++) {// LOOP over Gibbs iterations
      if( verboseIters & (i % (nGibbsIters / 10) == 0) ) {
	int iterOut = i + 1;
	cout << "Doing Gibbs iteration " << (i + 1);
	cout << " of " << nGibbsIters << endl;
	if( i == nGibbsIters - (nGibbsIters / 10) ) 
	  cout << "\n";// Improve aesthetics.
      }
      
      for (int j = 0; j < nTargets; j++) {// LOOP over target variables
	
	bool lastEmApprox = k == nEmApproxIters;
	
	if(lastEmApprox)
	  myGibbs[j].setLambdas();
	
	bool changeNDraws = 
	  (i == 0) & ((k == 0) | lastEmApprox | (k == nTotalEmIters));
	
	if(changeNDraws) 
	  myGibbs[j].setNDraws(nGibbsIters - nBurnIns);
	
	// Update the Gibbs samples:
	myGibbs[j].doGibbsIteration(myData);
	
	if ( (i + 1) == nBurnIns )
	  myGibbs[j].startGibbsSampling(myData);
       	
	if( (k < nTotalEmIters) & ( (i + 1) == nGibbsIters ) ) {
	  myGibbs[j].updateLambdas(); // Optimize the penalty parameters
	  myGibbs[j].restartParameters(myData);
	}
      }// CLOSE for (int j = 0; j < nTargets, j++)  
    }// CLOSE for (int i = 0; i < nGibbsIters; i++)
  }// END for(int k = 0; k < nTotalEmIters; k++)
  
  Rcpp::List outList(nTargets);
  for(int j = 0; j < nTargets; j++) {
    outList[j] = 
      Rcpp::List::create( Rcpp::Named("imps") = myGibbs[j].getImpSam(), 
			  Rcpp::Named("beta") = myGibbs[j].getBetaSam(),
			  Rcpp::Named("tau") = myGibbs[j].getTauSam(),
			  Rcpp::Named("sigma") = myGibbs[j].getSigmaSam(),
			  Rcpp::Named("lambdaHistory") = 
			  myGibbs[j].getLambdaHistory() );    
  }
  return outList;
}// END runGibbs() 


