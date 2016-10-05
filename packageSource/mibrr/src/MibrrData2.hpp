// Title:    Header file for MibrrData2 Class
// Author:   Kyle M. Lang
// Created:  2014-AUG-24
// Modified: 2016-MAY-15
// Purpose:  This class contains data- and sampling-related functions
//           used by the MIBRR Gibbs sampler.

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

#ifndef MIBRRDATA2_H
#define MIBRRDATA2_H

#include "MibrrData.hpp"

using namespace std;
using namespace Eigen;

class MibrrData2: public MibrrData {
  
public:
  //////////////////////// CONSTRUCTORS / DESTRUCTOR ////////////////////////////
  
  MibrrData2(MatrixXd&);
  
  MibrrData2(MatrixXd&,
	     //VectorXd&,
	     VectorXd&,
	     double);
  
  ~MibrrData2();
  
  //////////////////////////////// ACCESSORS ////////////////////////////////////
  
  MatrixXd getIVs2(int);
  // @param:  the column-index of the current target variable
  // @return: the IVs of the imputation model with rows corresponding to
  //          missing DV observations deleted
  
  MatrixXd getFullIVs2(int);
  // @param:  the column-index of the current target variable
  // @return: the full IVs matrix for the imputation model

  int nPreds2() const;
  // @return: the number of predictors in the imputation model not counting
  //          the constant column.
};

#endif
