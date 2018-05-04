// Title:    C++ Testing Function to Export in MIBRR
// Author:   Kyle M. Lang
// Created:  2014-AUG-20
// Modified: 2018-MAY-04

//--------------------- COPYRIGHT & LICENSING INFORMATION --------------------//
//  Copyright (C) 2018 Kyle M. Lang <k.m.lang@uvt.nl>                         //  
//                                                                            //
//  This file is part of MIBRR.                                               //
//                                                                            //
//  This program is free software: you can redistribute it and/or modify it   //
//  under the terms of the GNU General Public License as published by the     //
//  Free Software Foundation, either version 3 of the License, or (at you     //
//  option) any later version.                                                //
//                                                                            //
//  This program is distributed in the hope that it will be useful, but       //
//  WITHOUT ANY WARRANTY; without even the implied warranty of                //
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General  //
//  Public License for more details.                                          //
//                                                                            //
//  You should have received a copy of the GNU General Public License along   //
//  with this program. If not, see <http://www.gnu.org/licenses/>.            //
//----------------------------------------------------------------------------//

#include <RcppEigen.h>
#include "MibrrData.h"
#include "MibrrSamplers.h"

// [[Rcpp::export]]
Eigen::VectorXd drawInvGamma(int n, double shape, double scale)
{
  MibrrSamplers mibrrSamplers;
  VectorXd      out(n);
  for(int i = 0; i < n; i++) out[i] = mibrrSamplers.drawInvGamma(shape, scale);
  return out;
}

// [[Rcpp::export]]
Eigen::MatrixXd drawMvn(int n, Eigen::VectorXd meanVec, Eigen::MatrixXd covMat)
{
  MibrrSamplers mibrrSamplers;
  int          v = meanVec.size();
  MatrixXd     out(n, v);
  for(int i = 0; i < n; i++)
    out.row(i) = mibrrSamplers.drawMvn(meanVec, covMat);
  return out;
}

// [[Rcpp::export]]
double calcIncGamma(double shape, double cutVal, bool lowerTail)
{
  MibrrSamplers mibrrSamplers;
  return mibrrSamplers.calcIncGamma(shape, cutVal, lowerTail);
}

// [[Rcpp::export]]
Eigen::VectorXd drawInvGauss(int n, double mu, double lambda)
{
  MibrrSamplers mibrrSamplers;
  VectorXd      out(n);
  for(int i = 0; i < n; i++) out[i] = mibrrSamplers.drawInvGauss(mu, lambda);
  return out;
}

// [[Rcpp::export]]
Eigen::VectorXd drawGig(int n, double lambda, double chi, double psi)
{
  MibrrSamplers mibrrSamplers;
  VectorXd      out(n);
  for(int i = 0; i < n; i++) out[i] = mibrrSamplers.drawGig(lambda, chi, psi);
  return out;
}


// [[Rcpp::export]]
std::vector<int>
printObsIndices(Eigen::MatrixXd                 data,
		Eigen::VectorXd                 scales,
		std::vector< std::vector<int> > missIndices,
		Eigen::VectorXi                 respCounts,
		bool                            noMiss,
		int                             targetIndex)
{
  MibrrData mibrrData(data, scales, missIndices, respCounts, noMiss);
  return(mibrrData.getObsRows(targetIndex));
}

// [[Rcpp::export]]
std::vector<int>
printMissIndices(Eigen::MatrixXd                 data,
		 Eigen::VectorXd                 scales,
		 std::vector< std::vector<int> > missIndices,
		 Eigen::VectorXi                 respCounts,
		 bool                            noMiss,
		 int                             targetIndex)
{
  MibrrData mibrrData(data, scales, missIndices, respCounts, noMiss);
  return(mibrrData.getMissIndices(targetIndex));
}
