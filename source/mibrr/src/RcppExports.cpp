// This file was generated by Rcpp::compileAttributes
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <RcppEigen.h>
#include <Rcpp.h>

using namespace Rcpp;

// drawInvGamma
Eigen::VectorXd drawInvGamma(int n, double shape, double scale);
RcppExport SEXP mibrr_drawInvGamma(SEXP nSEXP, SEXP shapeSEXP, SEXP scaleSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< int >::type n(nSEXP);
    Rcpp::traits::input_parameter< double >::type shape(shapeSEXP);
    Rcpp::traits::input_parameter< double >::type scale(scaleSEXP);
    __result = Rcpp::wrap(drawInvGamma(n, shape, scale));
    return __result;
END_RCPP
}
// drawMVN
Eigen::MatrixXd drawMVN(int n, Eigen::VectorXd meanVec, Eigen::MatrixXd covMat);
RcppExport SEXP mibrr_drawMVN(SEXP nSEXP, SEXP meanVecSEXP, SEXP covMatSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< int >::type n(nSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type meanVec(meanVecSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type covMat(covMatSEXP);
    __result = Rcpp::wrap(drawMVN(n, meanVec, covMat));
    return __result;
END_RCPP
}
// calcIncGamma
double calcIncGamma(double shape, double cutVal, bool lowerTail);
RcppExport SEXP mibrr_calcIncGamma(SEXP shapeSEXP, SEXP cutValSEXP, SEXP lowerTailSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< double >::type shape(shapeSEXP);
    Rcpp::traits::input_parameter< double >::type cutVal(cutValSEXP);
    Rcpp::traits::input_parameter< bool >::type lowerTail(lowerTailSEXP);
    __result = Rcpp::wrap(calcIncGamma(shape, cutVal, lowerTail));
    return __result;
END_RCPP
}
// drawInvGauss
Eigen::VectorXd drawInvGauss(int n, double mu, double lambda);
RcppExport SEXP mibrr_drawInvGauss(SEXP nSEXP, SEXP muSEXP, SEXP lambdaSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< int >::type n(nSEXP);
    Rcpp::traits::input_parameter< double >::type mu(muSEXP);
    Rcpp::traits::input_parameter< double >::type lambda(lambdaSEXP);
    __result = Rcpp::wrap(drawInvGauss(n, mu, lambda));
    return __result;
END_RCPP
}
// runGibbs
Rcpp::List runGibbs(Eigen::MatrixXd inData, Eigen::VectorXd dataScales, int nTargets, Rcpp::List missList, Eigen::VectorXi respCounts, Eigen::VectorXd lambda1Starts, Eigen::VectorXd lambda2Starts, Eigen::VectorXd sigmaStarts, Eigen::MatrixXd tauStarts, Eigen::MatrixXd betaStarts, int nApproxIters, int nTuneIters, int nApproxBurn, int nApproxGibbs, int nTuneBurn, int nTuneGibbs, int nPostBurn, int nPostGibbs, int lambdaWindow, double emConvTol, bool verbose, bool doBl, bool doImputation, bool adaptScales, bool simpleIntercept, bool twoPhaseOpt);
RcppExport SEXP mibrr_runGibbs(SEXP inDataSEXP, SEXP dataScalesSEXP, SEXP nTargetsSEXP, SEXP missListSEXP, SEXP respCountsSEXP, SEXP lambda1StartsSEXP, SEXP lambda2StartsSEXP, SEXP sigmaStartsSEXP, SEXP tauStartsSEXP, SEXP betaStartsSEXP, SEXP nApproxItersSEXP, SEXP nTuneItersSEXP, SEXP nApproxBurnSEXP, SEXP nApproxGibbsSEXP, SEXP nTuneBurnSEXP, SEXP nTuneGibbsSEXP, SEXP nPostBurnSEXP, SEXP nPostGibbsSEXP, SEXP lambdaWindowSEXP, SEXP emConvTolSEXP, SEXP verboseSEXP, SEXP doBlSEXP, SEXP doImputationSEXP, SEXP adaptScalesSEXP, SEXP simpleInterceptSEXP, SEXP twoPhaseOptSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type inData(inDataSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type dataScales(dataScalesSEXP);
    Rcpp::traits::input_parameter< int >::type nTargets(nTargetsSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type missList(missListSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXi >::type respCounts(respCountsSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type lambda1Starts(lambda1StartsSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type lambda2Starts(lambda2StartsSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type sigmaStarts(sigmaStartsSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type tauStarts(tauStartsSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type betaStarts(betaStartsSEXP);
    Rcpp::traits::input_parameter< int >::type nApproxIters(nApproxItersSEXP);
    Rcpp::traits::input_parameter< int >::type nTuneIters(nTuneItersSEXP);
    Rcpp::traits::input_parameter< int >::type nApproxBurn(nApproxBurnSEXP);
    Rcpp::traits::input_parameter< int >::type nApproxGibbs(nApproxGibbsSEXP);
    Rcpp::traits::input_parameter< int >::type nTuneBurn(nTuneBurnSEXP);
    Rcpp::traits::input_parameter< int >::type nTuneGibbs(nTuneGibbsSEXP);
    Rcpp::traits::input_parameter< int >::type nPostBurn(nPostBurnSEXP);
    Rcpp::traits::input_parameter< int >::type nPostGibbs(nPostGibbsSEXP);
    Rcpp::traits::input_parameter< int >::type lambdaWindow(lambdaWindowSEXP);
    Rcpp::traits::input_parameter< double >::type emConvTol(emConvTolSEXP);
    Rcpp::traits::input_parameter< bool >::type verbose(verboseSEXP);
    Rcpp::traits::input_parameter< bool >::type doBl(doBlSEXP);
    Rcpp::traits::input_parameter< bool >::type doImputation(doImputationSEXP);
    Rcpp::traits::input_parameter< bool >::type adaptScales(adaptScalesSEXP);
    Rcpp::traits::input_parameter< bool >::type simpleIntercept(simpleInterceptSEXP);
    Rcpp::traits::input_parameter< bool >::type twoPhaseOpt(twoPhaseOptSEXP);
    __result = Rcpp::wrap(runGibbs(inData, dataScales, nTargets, missList, respCounts, lambda1Starts, lambda2Starts, sigmaStarts, tauStarts, betaStarts, nApproxIters, nTuneIters, nApproxBurn, nApproxGibbs, nTuneBurn, nTuneGibbs, nPostBurn, nPostGibbs, lambdaWindow, emConvTol, verbose, doBl, doImputation, adaptScales, simpleIntercept, twoPhaseOpt));
    return __result;
END_RCPP
}
