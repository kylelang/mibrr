// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <RcppEigen.h>
#include <Rcpp.h>

using namespace Rcpp;

// runGibbs
Rcpp::List runGibbs(Eigen::MatrixXd data, Eigen::VectorXd dataScales, int nTargets, Rcpp::List missList, Eigen::VectorXi respCounts, Eigen::VectorXd lambda1, Eigen::VectorXd lambda2, Eigen::VectorXd l1Parms, Eigen::VectorXd l2Parms, Eigen::VectorXd sigmaStarts, Eigen::MatrixXd tauStarts, Eigen::MatrixXd betaStarts, int burnSams, int totalSams, bool verbose, bool doBl, bool fullBayes, bool adaptScales, bool simpleIntercept, bool noMiss, std::vector<unsigned int> seeds);
RcppExport SEXP _MIBRR_runGibbs(SEXP dataSEXP, SEXP dataScalesSEXP, SEXP nTargetsSEXP, SEXP missListSEXP, SEXP respCountsSEXP, SEXP lambda1SEXP, SEXP lambda2SEXP, SEXP l1ParmsSEXP, SEXP l2ParmsSEXP, SEXP sigmaStartsSEXP, SEXP tauStartsSEXP, SEXP betaStartsSEXP, SEXP burnSamsSEXP, SEXP totalSamsSEXP, SEXP verboseSEXP, SEXP doBlSEXP, SEXP fullBayesSEXP, SEXP adaptScalesSEXP, SEXP simpleInterceptSEXP, SEXP noMissSEXP, SEXP seedsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type data(dataSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type dataScales(dataScalesSEXP);
    Rcpp::traits::input_parameter< int >::type nTargets(nTargetsSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type missList(missListSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXi >::type respCounts(respCountsSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type lambda1(lambda1SEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type lambda2(lambda2SEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type l1Parms(l1ParmsSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type l2Parms(l2ParmsSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type sigmaStarts(sigmaStartsSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type tauStarts(tauStartsSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type betaStarts(betaStartsSEXP);
    Rcpp::traits::input_parameter< int >::type burnSams(burnSamsSEXP);
    Rcpp::traits::input_parameter< int >::type totalSams(totalSamsSEXP);
    Rcpp::traits::input_parameter< bool >::type verbose(verboseSEXP);
    Rcpp::traits::input_parameter< bool >::type doBl(doBlSEXP);
    Rcpp::traits::input_parameter< bool >::type fullBayes(fullBayesSEXP);
    Rcpp::traits::input_parameter< bool >::type adaptScales(adaptScalesSEXP);
    Rcpp::traits::input_parameter< bool >::type simpleIntercept(simpleInterceptSEXP);
    Rcpp::traits::input_parameter< bool >::type noMiss(noMissSEXP);
    Rcpp::traits::input_parameter< std::vector<unsigned int> >::type seeds(seedsSEXP);
    rcpp_result_gen = Rcpp::wrap(runGibbs(data, dataScales, nTargets, missList, respCounts, lambda1, lambda2, l1Parms, l2Parms, sigmaStarts, tauStarts, betaStarts, burnSams, totalSams, verbose, doBl, fullBayes, adaptScales, simpleIntercept, noMiss, seeds));
    return rcpp_result_gen;
END_RCPP
}
// drawNorm
Eigen::VectorXd drawNorm(int n, double mean, double sd, unsigned int seed);
RcppExport SEXP _MIBRR_drawNorm(SEXP nSEXP, SEXP meanSEXP, SEXP sdSEXP, SEXP seedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type n(nSEXP);
    Rcpp::traits::input_parameter< double >::type mean(meanSEXP);
    Rcpp::traits::input_parameter< double >::type sd(sdSEXP);
    Rcpp::traits::input_parameter< unsigned int >::type seed(seedSEXP);
    rcpp_result_gen = Rcpp::wrap(drawNorm(n, mean, sd, seed));
    return rcpp_result_gen;
END_RCPP
}
// drawGamma
Eigen::VectorXd drawGamma(int n, double shape, double rate, unsigned int seed);
RcppExport SEXP _MIBRR_drawGamma(SEXP nSEXP, SEXP shapeSEXP, SEXP rateSEXP, SEXP seedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type n(nSEXP);
    Rcpp::traits::input_parameter< double >::type shape(shapeSEXP);
    Rcpp::traits::input_parameter< double >::type rate(rateSEXP);
    Rcpp::traits::input_parameter< unsigned int >::type seed(seedSEXP);
    rcpp_result_gen = Rcpp::wrap(drawGamma(n, shape, rate, seed));
    return rcpp_result_gen;
END_RCPP
}
// drawInvGamma
Eigen::VectorXd drawInvGamma(int n, double shape, double scale, unsigned int seed);
RcppExport SEXP _MIBRR_drawInvGamma(SEXP nSEXP, SEXP shapeSEXP, SEXP scaleSEXP, SEXP seedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type n(nSEXP);
    Rcpp::traits::input_parameter< double >::type shape(shapeSEXP);
    Rcpp::traits::input_parameter< double >::type scale(scaleSEXP);
    Rcpp::traits::input_parameter< unsigned int >::type seed(seedSEXP);
    rcpp_result_gen = Rcpp::wrap(drawInvGamma(n, shape, scale, seed));
    return rcpp_result_gen;
END_RCPP
}
// drawMvn
Eigen::MatrixXd drawMvn(int n, Eigen::VectorXd meanVec, Eigen::MatrixXd covMat, unsigned int seed);
RcppExport SEXP _MIBRR_drawMvn(SEXP nSEXP, SEXP meanVecSEXP, SEXP covMatSEXP, SEXP seedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type n(nSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type meanVec(meanVecSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type covMat(covMatSEXP);
    Rcpp::traits::input_parameter< unsigned int >::type seed(seedSEXP);
    rcpp_result_gen = Rcpp::wrap(drawMvn(n, meanVec, covMat, seed));
    return rcpp_result_gen;
END_RCPP
}
// calcIncGamma
double calcIncGamma(double shape, double cutVal, bool lowerTail);
RcppExport SEXP _MIBRR_calcIncGamma(SEXP shapeSEXP, SEXP cutValSEXP, SEXP lowerTailSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type shape(shapeSEXP);
    Rcpp::traits::input_parameter< double >::type cutVal(cutValSEXP);
    Rcpp::traits::input_parameter< bool >::type lowerTail(lowerTailSEXP);
    rcpp_result_gen = Rcpp::wrap(calcIncGamma(shape, cutVal, lowerTail));
    return rcpp_result_gen;
END_RCPP
}
// drawInvGauss
Eigen::VectorXd drawInvGauss(int n, double mu, double lambda, unsigned int seed);
RcppExport SEXP _MIBRR_drawInvGauss(SEXP nSEXP, SEXP muSEXP, SEXP lambdaSEXP, SEXP seedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type n(nSEXP);
    Rcpp::traits::input_parameter< double >::type mu(muSEXP);
    Rcpp::traits::input_parameter< double >::type lambda(lambdaSEXP);
    Rcpp::traits::input_parameter< unsigned int >::type seed(seedSEXP);
    rcpp_result_gen = Rcpp::wrap(drawInvGauss(n, mu, lambda, seed));
    return rcpp_result_gen;
END_RCPP
}
// drawGig
Eigen::VectorXd drawGig(int n, double lambda, double chi, double psi, unsigned int seed);
RcppExport SEXP _MIBRR_drawGig(SEXP nSEXP, SEXP lambdaSEXP, SEXP chiSEXP, SEXP psiSEXP, SEXP seedSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type n(nSEXP);
    Rcpp::traits::input_parameter< double >::type lambda(lambdaSEXP);
    Rcpp::traits::input_parameter< double >::type chi(chiSEXP);
    Rcpp::traits::input_parameter< double >::type psi(psiSEXP);
    Rcpp::traits::input_parameter< unsigned int >::type seed(seedSEXP);
    rcpp_result_gen = Rcpp::wrap(drawGig(n, lambda, chi, psi, seed));
    return rcpp_result_gen;
END_RCPP
}
// printObsIndices
std::vector<int> printObsIndices(Eigen::MatrixXd data, Eigen::VectorXd scales, std::vector< std::vector<int> > missIndices, Eigen::VectorXi respCounts, bool noMiss, int targetIndex);
RcppExport SEXP _MIBRR_printObsIndices(SEXP dataSEXP, SEXP scalesSEXP, SEXP missIndicesSEXP, SEXP respCountsSEXP, SEXP noMissSEXP, SEXP targetIndexSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type data(dataSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type scales(scalesSEXP);
    Rcpp::traits::input_parameter< std::vector< std::vector<int> > >::type missIndices(missIndicesSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXi >::type respCounts(respCountsSEXP);
    Rcpp::traits::input_parameter< bool >::type noMiss(noMissSEXP);
    Rcpp::traits::input_parameter< int >::type targetIndex(targetIndexSEXP);
    rcpp_result_gen = Rcpp::wrap(printObsIndices(data, scales, missIndices, respCounts, noMiss, targetIndex));
    return rcpp_result_gen;
END_RCPP
}
// printMissIndices
std::vector<int> printMissIndices(Eigen::MatrixXd data, Eigen::VectorXd scales, std::vector< std::vector<int> > missIndices, Eigen::VectorXi respCounts, bool noMiss, int targetIndex);
RcppExport SEXP _MIBRR_printMissIndices(SEXP dataSEXP, SEXP scalesSEXP, SEXP missIndicesSEXP, SEXP respCountsSEXP, SEXP noMissSEXP, SEXP targetIndexSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type data(dataSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type scales(scalesSEXP);
    Rcpp::traits::input_parameter< std::vector< std::vector<int> > >::type missIndices(missIndicesSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXi >::type respCounts(respCountsSEXP);
    Rcpp::traits::input_parameter< bool >::type noMiss(noMissSEXP);
    Rcpp::traits::input_parameter< int >::type targetIndex(targetIndexSEXP);
    rcpp_result_gen = Rcpp::wrap(printMissIndices(data, scales, missIndices, respCounts, noMiss, targetIndex));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_MIBRR_runGibbs", (DL_FUNC) &_MIBRR_runGibbs, 21},
    {"_MIBRR_drawNorm", (DL_FUNC) &_MIBRR_drawNorm, 4},
    {"_MIBRR_drawGamma", (DL_FUNC) &_MIBRR_drawGamma, 4},
    {"_MIBRR_drawInvGamma", (DL_FUNC) &_MIBRR_drawInvGamma, 4},
    {"_MIBRR_drawMvn", (DL_FUNC) &_MIBRR_drawMvn, 4},
    {"_MIBRR_calcIncGamma", (DL_FUNC) &_MIBRR_calcIncGamma, 3},
    {"_MIBRR_drawInvGauss", (DL_FUNC) &_MIBRR_drawInvGauss, 4},
    {"_MIBRR_drawGig", (DL_FUNC) &_MIBRR_drawGig, 5},
    {"_MIBRR_printObsIndices", (DL_FUNC) &_MIBRR_printObsIndices, 6},
    {"_MIBRR_printMissIndices", (DL_FUNC) &_MIBRR_printMissIndices, 6},
    {NULL, NULL, 0}
};

RcppExport void R_init_MIBRR(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
