### Title:    Exported Helper Functions for MIBRR
### Author:   Kyle M. Lang
### Created:  2014-DEC-09
### Modified: 2019-JAN-16

##--------------------- COPYRIGHT & LICENSING INFORMATION --------------------##
##  Copyright (C) 2019 Kyle M. Lang <k.m.lang@uvt.nl>                         ##
##                                                                            ##
##  This file is part of MIBRR.                                               ##
##                                                                            ##
##  This program is free software: you can redistribute it and/or modify it   ##
##  under the terms of the GNU General Public License as published by the     ##
##  Free Software Foundation, either version 3 of the License, or (at you     ##
##  option) any later version.                                                ##
##                                                                            ##
##  This program is distributed in the hope that it will be useful, but       ##
##  WITHOUT ANY WARRANTY; without even the implied warranty of                ##
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General  ##
##  Public License for more details.                                          ##
##                                                                            ##
##  You should have received a copy of the GNU General Public License along   ##
##  with this program. If not, see <http://www.gnu.org/licenses/>.            ##
##----------------------------------------------------------------------------##


## Sample the imputations from the stationary posterior predictive distibution
## of the missing data
getImpData <- function(mibrrFit, nImps) {
    impList <- list()
    for(m in 1 : nImps) impList[[m]] <- mibrrFit$getImpDataset()
    impList
}# END getImputedData()



## Extract the parameter samples from a fitted MibrrFit object:
getParams <- function(mibrrFit, target) {
    tmp <- mibrrFit$gibbsOut[[target]]
    out <- tmp[c("beta", "sigma")]
    
    if(mibrrFit$penalty != 0) {# Used shrinkage priors?
        out$tau <- tmp$tau
        
        if(mibrrFit$doMcem)
            out$lambda <- mibrrFit$lambdaMat[target, ]
        else
            out$lambda <- tmp$lambda
    }
    out
}



## Generate posterior predictions from a fitted BEN or BL model:
postPredict <- function(mibrrFit,
                        newData,
                        targetVars = NULL,
                        nDraws     = 0,
                        scale      = TRUE)
{
    if(!is.data.frame(newData)) stop("'newData' must be a data.frame")
    if(is.null(targetVars))     targetVars <- mibrrFit$targetVars

    if(scale) newData <- scale(newData)
    
    outList <- list()
    for(nm in targetVars) {
        pars     <- getParams(mibrrFit, nm)
        testData <- cbind(1, as.matrix(newData[ , colnames(pars$tau)]))

        if(nDraws > 0) {
            index <- sample(c(1 : length(pars$sigma)), nDraws)
            beta  <- pars$beta[index, ]
            sigma <- pars$sigma[index]
            
            out <- matrix(NA, nrow(testData), nDraws)
            for(j in 1 : nDraws)
                out[ , j] <- testData %*% matrix(beta[j, ]) +
                    rnorm(1, 0, sqrt(sigma[j]))
        }
        else {
            if(nDraws == 0) {
                beta  <- matrix(apply(pars$beta, 2, numMode))
                sigma <- numMode(pars$sigma)
            }
            else {# nDraws < 0
                beta  <- matrix(colMeans(pars$beta))
                sigma <- mean(pars$sigma)
            }
            out <- testData %*% beta + rnorm(1, 0, sqrt(sigma))
        }
        outList[[nm]] <- out
    }
    outList
}


## Access arbitrary fields in a 'MibrrFit' object:
getField <- function(mibrrFit, what) mibrrFit$field(what)


## Calculate the potential scale reduction factor (R-Hat)
                                        #calcRHat <- function(simsIn, nChains = 1)
                                        #{
                                        #    subChainLen <- floor(length(simsIn) / 2)
                                        #    nSubChains  <- nChains * 2
                                        #
                                        #    if(length(simsIn) %% nSubChains == 0) {
                                        #        simsMat <- matrix(simsIn, ncol = nSubChains)
                                        #    } else {
                                        #        simsMat <- matrix(
                                        #            simsIn[1 : (length(simsIn) - (nSubChains - 1))],
                                        #            ncol = nSubChains
                                        #        )
                                        #    }
                                        #
                                        #    wMean     <- colMeans(simsMat)
                                        #    grandMean <- mean(simsMat)
                                        #
                                        #    bVar <- (subChainLen / (nSubChains - 1)) * sum((wMean - grandMean)^2)
                                        #    wVar <- mean(apply(simsMat, 2, var))
                                        #    tVar <- ((subChainLen - 1) / subChainLen) * wVar + (1 / subChainLen) * bVar
                                        #    
                                        #    sqrt(tVar / wVar)
                                        #}# END calcRHat()
