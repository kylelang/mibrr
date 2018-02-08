### Title:    Primary User-Facing Routines of the MIBRR Package
### Author:   Kyle M. Lang
### Created:  2014-DEC-12
### Modified: 2018-FEB-08
### Purpose:  The following functions implement MIBEN or MIBL to create multiple
###           imputations within a MICE framework that uses the Bayesian
###           Elastic Net (BEN) or the Bayesian LASSO (BL), respectively, as its
###           elementary imputation method.
### Notes:    - The ben and bl functions simply fit the Bayesian elastic net and
###             Bayesian LASSO models to (possibly) incomplete data without
###             returning any missing data imputations.

##--------------------- COPYRIGHT & LICENSING INFORMATION ---------------------##
##  Copyright (C) 2018 Kyle M. Lang <k.m.lang@uvt.nl>                          ##  
##                                                                             ##
##  This file is part of MIBRR.                                                ##
##                                                                             ##
##  This program is free software: you can redistribute it and/or modify it    ##
##  under the terms of the GNU General Public License as published by the      ##
##  Free Software Foundation, either version 3 of the License, or (at you      ##
##  option) any later version.                                                 ##
##                                                                             ##
##  This program is distributed in the hope that it will be useful, but        ##
##  WITHOUT ANY WARRANTY; without even the implied warranty of                 ##
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General   ##
##  Public License for more details.                                           ##
##                                                                             ##
##  You should have received a copy of the GNU General Public License along    ##
##  with this program. If not, see <http://www.gnu.org/licenses/>.             ##
##-----------------------------------------------------------------------------##


### Specify a wrapper function to implement Multiple Imputation with the
### Bayesian Elastic Net (MIBEN):
miben <- function(data,
                  targetVars     = NULL,
                  ignoreVars     = NULL,
                  iterations     = c(100, 10),
                  sampleSizes    = list(rep(25, 2), rep(250, 2), rep(500, 2)),
                  doMcem         = TRUE,
                  lam1PriorPar   = NULL,
                  lam2PriorPar   = NULL,
                  missCode       = NA,
                  verbose        = TRUE,
                  seed           = NULL,
                  control        = list()
                  )
{
    ## Initialize the output object:
    mibrrFit <- init(doBl         = FALSE,
                     doImp        = TRUE,
                     doMcem       = doMcem,
                     data         = data,
                     targetVars   = targetVars,
                     ignoreVars   = ignoreVars,
                     iterations   = iterations,
                     sampleSizes  = sampleSizes,
                     lam1PriorPar = lam1PriorPar,
                     lam2PriorPar = lam2PriorPar,
                     missCode     = missCode,
                     verbose      = verbose,
                     seed         = seed,
                     control      = control)

    ## Estimate the model with MCEM:
    if(doMcem) mibrrFit <- mcem(mibrrFit)
    else       mibrrFit$doGibbs()
    
    ## Clean up and return the fitted model object:
    postProcess(mibrrFit)
}# END miben()


### Specify a wrapper function to implement Multiple Imputation with the
### Bayesian Lasso (MIBL):
mibl <- function(data,
                 targetVars   = NULL,
                 ignoreVars   = NULL,
                 iterations   = c(100, 10),
                 sampleSizes  = list(rep(25, 2), rep(250, 2), rep(500, 2)),
                 doMcem       = TRUE,
                 lam1PriorPar = NULL,
                 missCode     = NA,
                 verbose      = TRUE,
                 seed         = NULL,
                 control      = list()
                 )
{
    ## Initialize the output object:
    mibrrFit <- init(doBl         = TRUE,
                     doImp        = TRUE,
                     doMcem       = doMcem,
                     data         = data,
                     targetVars   = targetVars,
                     ignoreVars   = ignoreVars,
                     iterations   = iterations,
                     sampleSizes  = sampleSizes,
                     lam1PriorPar = lam1PriorPar,
                     missCode     = missCode,
                     verbose      = verbose,
                     seed         = seed,
                     control      = control)
    
    ## Estimate the model with MCEM:
    if(doMcem) mibrrFit <- mcem(mibrrFit)
    else       mibrrFit$doGibbs()
    
    ## Clean up and return the fitted model object:
    postProcess(mibrrFit)
}# END mibl()


### Specify a wrapper function to fit the Bayesian Elastic Net (BEN):
ben <- function(data,
                y,
                X            = NULL,
                iterations   = c(100, 10),
                sampleSizes  = list(rep(25, 2), rep(250, 2), rep(500, 2)),
                doMcem       = TRUE,
                lam1PriorPar = NULL,
                lam2PriorPar = NULL,
                missCode     = NA,
                verbose      = TRUE,
                seed         = NULL,
                control      = list()
                )
{
    if(length(y) > 1) stop("Only one outcome variable is allowed.")

    ## Initialize the output object:
    mibrrFit <- init(doBl         = FALSE,
                     doImp        = FALSE,
                     doMcem       = doMcem,
                     data         = data,
                     targetVars   = y,
                     ignoreVars   = setdiff(colnames(data), c(y, X)),
                     iterations   = iterations,
                     sampleSizes  = sampleSizes,
                     lam1PriorPar = lam1PriorPar,
                     lam2PriorPar = lam2PriorPar,
                     missCode     = missCode,
                     verbose      = verbose,
                     seed         = seed,
                     control      = control)

    ## Estimate the model with MCEM:
    if(doMcem) mibrrFit <- mcem(mibrrFit)
    else       mibrrFit$doGibbs()
    
    ## Clean up and return the fitted model object:
    postProcess(mibrrFit)
}# END ben()


### Specify a wrapper function to fit the Bayesian LASSO (BL):
bl <- function(data,
               y,
               X            = NULL,
               iterations   = c(100, 10),
               sampleSizes  = list(rep(25, 2), rep(250, 2), rep(500, 2)),
               lam1PriorPar = NULL,
               doMcem       = TRUE,
               missCode     = NA,
               verbose      = TRUE,
               seed         = NULL,
               control      = list()
               )
{
    if(length(y) > 1) stop("Only one outcome variable is allowed.")
    
    ## Initialize the output object:
    mibrrFit <- init(doBl         = TRUE,
                     doImp        = FALSE,
                     doMcem       = doMcem,
                     data         = data,
                     targetVars   = y,
                     ignoreVars   = setdiff(colnames(data), c(y, X)),
                     iterations   = iterations,
                     sampleSizes  = sampleSizes,
                     lam1PriorPar = lam1PriorPar,
                     missCode     = missCode,
                     verbose      = verbose,
                     seed         = seed,
                     control      = control)

    ## Estimate the model with MCEM:
    if(doMcem) mibrrFit <- mcem(mibrrFit)
    else       mibrrFit$doGibbs()
    
    ## Clean up and return the fitted model object:
    postProcess(mibrrFit)
}# END bl()