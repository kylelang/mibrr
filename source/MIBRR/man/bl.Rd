\name{bl}
\alias{bl}
\title{
Bayesian LASSO
}
\description{
  This function will fit the Bayesian LASSO to (possibly) incomplete data.
}
\usage{
bl(data,
   y,
   X            = NULL,
   iterations   = c(100, 10),
   sampleSizes  = list(rep(25, 2), rep(250, 2), rep(500, 2)),
   lam1PriorPar = NULL,
   doMcem       = TRUE,
   missCode     = NA,
   verbose      = TRUE,
   seed         = NULL,
   userRng      = "",
   control      = list()
   )  
}
\arguments{
  \item{data}{
    A, possibly incomplete, numeric data matrix or data frame to which the BL
    is to be fit.
  }
  \item{y}{
    The column label for the outcome variable.  
  }
  \item{X}{
    An optional character vector giving the column labels for the predictor
    variables. When \code{X = NULL} the target variable is regressed onto all
    other variables in \code{data}.
  }
  \item{iterations}{
    A two-element numeric vector giving the number of iterations to employ
    during the MCEM approximation and tuning phases, respectively.\cr
    Defaults to \code{iterations = c(100, 10)}.
  }
  \item{sampleSizes}{
    A list or vector giving the desired Gibbs sample sizes (see
    Details for more information).\cr 
    Defaults to \code{sampleSizes = list(rep(25, 2), rep(250, 2),
      rep(500, 2))}.
  }
  \item{doMcem}{
    A logical switch: Should the model be estimated using Markov Chain
    Expectation Maximization (MCEM)? If \code{doMcem = FALSE} the model
    is estimated as a fully Bayesian model by assigning hyper-priors to
    the penalty parameter.\cr
    Defaults to \code{doMcem = TRUE}.
  }
  \item{lam1PriorPar}{
    A two-element numeric vector giving the prior shape and rate
    parameters, respectively, for the squared LASSO penalty parameter's,
    \eqn{\lambda_1^2}{lambda1^2}, gamma prior.
  }
  \item{missCode}{
    An optional integer-valued code used to flag the missing data in
    \code{data}. Should take a value that cannot naturally occur in
    \code{data}. Not needed when the missing data are coded as \code{NA}.
  }
  \item{verbose}{
    A logical switch: Should verbose output be printed to stdout?\cr
    Defaults to \code{verbose = TRUE}.
  }
  \item{seed}{
    Either a positive, integer-valued seed a one-element character
    vector naming an extant R'Lecuyer RNG stream generated by the
    \pkg{rlecuyer} package (see \dQuote{Details}).
  }
  \item{userRng}{
    A character string giving the name of an \pkg{rlecuyer} RNG stream
    that is being actively used for random number generation in the
    current session. See \dQuote{Details} for more information about how
    this argument is used.
  }
  \item{control}{
    A list of control parameters for the Gibbs sampler and penalty parameter
    optimization (see Details for more information).
  }
}
\details{
  The \code{sampleSizes} argument must be a three-element list when
  \code{doMcem = TRUE}. In this case, the list must contain three
  two-element numeric (integer) vectors giving the number of MCMC draws
  to discard as burn-in and to retain, respectively, during the MCEM
  approximation, tuning, and sampling phases.

  When \code{doMcem = FALSE}, only a single Gibbs sample is drawn, so
  the\code{sampleSizes} argument must be a   two-element numeric
  (integer) vector giving the number of MCMC draws   to discard as
  burn-in and the number to retain in the final Gibbs sample.

  The \pkg{MIBRR} package uses \pkg{rlecuyer} to generate independent
  random number streams for all internal sub-processes. When the argument
  to \code{seed} is an integer, this value is used to seed the
  \pkg{rlecuyer} package via
  \code{rlecuyer::.lec.SetPackageSeed(rep(seed, 6))}. When the argument
  to \code{seed} names an extant \pkg{rlecuyer} stream, the internal RNG
  streams are seeded with the current state of the stream named in
  \code{seed} via
  \code{rlecuyer::.lec.SetPackageSeed(rlecuyer::.lec.GetState(seed))}. When
  \code{seed = NULL}, a transient seed is generated via \code{seed <-
  round(runif(1) * 1e8)}. The value used to seed the \pkg{rlecuyer}
  package (along with its name, if any) is saved in the \code{seed}
  field of the \code{MibrrFit} object.

  The \pkg{MIBRR} package uses \pkg{rlecuyer} random number streams
  internally. So, if an \pkg{rlecuyer} RNG stream, say \dQuote{s0}, is
  being used to generate random numbers in the current session, this
  stream's name should be given as the \code{userRng} argument. For
  example, if \code{.lec.CurrentStream("s0")} has been called and
  \code{.lec.CurrentStreamEnd()} has not been called, \code{bl} needs
  to be overtly notified of the non-standard RNG state via \code{userRng
  = "s0"}. Doing so will tell \code{bl} to re-set \dQuote{s0} as the
  active RNG stream on return. If no argument is provided for
  \code{userRng}, \code{bl} will attempt to leave the RNG state as it
  was when \code{bl} was called, but no \pkg{rlecuyer} RNG streams
  will not be re-set for use in the current session.
  
  \code{control} is a list containing the following named elements:
  \describe{
    \item{convThresh:}{
      The R-Hat value used to judge convergence. R-Hat values <
      \code{convThresh} arising from the final, retained Gibbs sample
      will trigger a warning.\cr
      Defaults to \code{convThres = 1.1}.
    }
    \item{lambda1Starts:}{
      An optional numeric vector giving starting values for
      the LASSO penalty parameter, \eqn{\lambda_1}{lambda1}. Values are recycled
      to populate a vector with \code{size = length(targetVars)}.\cr
      Defaults to \code{rep(0.5, length(targetVars))}.
    }
    \item{usePcStarts:}{
      A logical switch: Use the starting values for \eqn{\lambda_1}{lambda1}
      suggested by Park and Casella (2008)?\cr
      Defaults to \code{usePcStarts = FALSE}.
    }
    \item{smoothingWindow:}{
      An integer giving the number of approximation phase
      \eqn{\Lambda}{Lambda} values to average over to get the starting
      \eqn{\Lambda's}{Lambdas} for the MCEM tuning phase. Setting
      \code{smoothingWindow} > 1 can facilitate convergence of the MCEM tuning phase
      when burn-in \eqn{\Lambda}{Lambda} estimates are very noisy.\cr
      Defaults to \code{smoothingWindow = min(10, ceiling(nApprox / 10))} where
      \code{nApprox} is the number of MCEM approximation iterations. 
    }
    \item{minPredCor:}{
      The minimum correlation used by \code{mice::quickpred}
      when temporarily filling missing data before scaling or when filling
      missing data on covariates.\cr
      Defaults to \code{minPredCor = 0.3}.
    }
    \item{miceIters:}{
      The number of iterations used by the \pkg{mice} package when temporarily
      filling missing data before scaling or filling missing data on
      covariates.\cr
      Defaults to \code{miceIters = 10}.
    }
    \item{miceRidge:}{
      The ridge penalty used by the \pkg{mice} package when temporarily
      filling missing data before scaling or filling missing data on
      covariates.\cr
      Defaults to \code{miceRidge = 1e-4}.
    }
    \item{miceMethod:}{
      The elementary imputation method used by the \pkg{mice} package when
      temporarily filling missing data before scaling or filling missing data on
      covariates.\cr
      Defaults to \code{miceMethod = "pmm"}.
    }
    \item{checkConv:}{
      A logical switch: Should the stationary Gibbs samples be checked
      for convergence?\cr
      Defaults to \code{checkConv = TRUE}.
    }
  }
}
\value{
  A reference class object with class \code{MibrrFit}. This object
  contains a great deal of metadata and various pieces of output. Key
  output can be accessed via the convenience function
  \code{\link{getParams}}, and the \code{\link{getField}} function. See
  documentation for \code{\link{MibrrFit}} for more details.
}
\references{
  Lang, K. M. (2015) \emph{MIBEN: Multiple imputation with the
    Bayesian elastic net} (Unpublished doctoral dissertation). University of
  Kansas.
   
  Park, T. and Casella, G. (2008) The Bayesian Lasso. \emph{Journal of
    the American Statistical Association}, \bold{103}, 681--686.
  
  Zhao, Y., and Long, Q. (2013) Multiple imputation in the presence of
  high-dimensional data. \emph{Statistical Methods in Medical Research},
  \bold{0}(0), 1--15.
}
\author{
  Kyle M. Lang
}
\section{Warning}{
  This function is in a highly unstable \emph{alpha} level of development. Please
  anticipate frequent---and dramatic---changes to the functionality and user
  interface.
  
  You have been granted access to this package for evaluation purposes, only. This
  function is \strong{absolutely not} ready for use in real-world analyses!
}
\seealso{
\code{\link{ben}}, \code{\link{getParams}}, \code{\link{getField}}
}
\examples{
data(mibrrExampleData)

## MCEM estimation:
blOut <- bl(data       = mibrrExampleData,
            y          = "y",
            X          = setdiff(colnames(mibrrExampleData), c("y", "idNum")),
            iterations = c(50, 10)
            )

## Fully Bayesian estimation:
blOut <- bl(data         = mibrrExampleData,
            y            = "y",
            X            = setdiff(colnames(mibrrExampleData), c("y", "idNum")),
            doMcem       = FALSE,
            sampleSizes  = c(500, 500),
            lam1PriorPar = c(1.0, 0.1)
            )
}