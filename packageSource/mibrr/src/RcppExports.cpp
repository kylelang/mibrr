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
Rcpp::List runGibbs(Eigen::MatrixXd inData, Eigen::VectorXd dataScales, int nTargets, Eigen::VectorXd lambda1Starts, Eigen::VectorXd lambda2Starts, Eigen::VectorXd sigmaStarts, Eigen::MatrixXd tauStarts, Eigen::MatrixXd betaStarts, double missCode, int nMcemApproxIters, int nMcemTuneIters, int nMcemApproxBurn, int nMcemApproxGibbs, int nMcemTuneBurn, int nMcemTuneGibbs, int nMcemPostBurn, int nMcemPostGibbs, int lambdaWindow, double emConvTol, bool verboseIters, bool verboseErrors, bool doBen, bool regIntercept, bool doImputation);
RcppExport SEXP mibrr_runGibbs(SEXP inDataSEXP, SEXP dataScalesSEXP, SEXP nTargetsSEXP, SEXP lambda1StartsSEXP, SEXP lambda2StartsSEXP, SEXP sigmaStartsSEXP, SEXP tauStartsSEXP, SEXP betaStartsSEXP, SEXP missCodeSEXP, SEXP nMcemApproxItersSEXP, SEXP nMcemTuneItersSEXP, SEXP nMcemApproxBurnSEXP, SEXP nMcemApproxGibbsSEXP, SEXP nMcemTuneBurnSEXP, SEXP nMcemTuneGibbsSEXP, SEXP nMcemPostBurnSEXP, SEXP nMcemPostGibbsSEXP, SEXP lambdaWindowSEXP, SEXP emConvTolSEXP, SEXP verboseItersSEXP, SEXP verboseErrorsSEXP, SEXP doBenSEXP, SEXP regInterceptSEXP, SEXP doImputationSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type inData(inDataSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type dataScales(dataScalesSEXP);
    Rcpp::traits::input_parameter< int >::type nTargets(nTargetsSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type lambda1Starts(lambda1StartsSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type lambda2Starts(lambda2StartsSEXP);
    Rcpp::traits::input_parameter< Eigen::VectorXd >::type sigmaStarts(sigmaStartsSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type tauStarts(tauStartsSEXP);
    Rcpp::traits::input_parameter< Eigen::MatrixXd >::type betaStarts(betaStartsSEXP);
    Rcpp::traits::input_parameter< double >::type missCode(missCodeSEXP);
    Rcpp::traits::input_parameter< int >::type nMcemApproxIters(nMcemApproxItersSEXP);
    Rcpp::traits::input_parameter< int >::type nMcemTuneIters(nMcemTuneItersSEXP);
    Rcpp::traits::input_parameter< int >::type nMcemApproxBurn(nMcemApproxBurnSEXP);
    Rcpp::traits::input_parameter< int >::type nMcemApproxGibbs(nMcemApproxGibbsSEXP);
    Rcpp::traits::input_parameter< int >::type nMcemTuneBurn(nMcemTuneBurnSEXP);
    Rcpp::traits::input_parameter< int >::type nMcemTuneGibbs(nMcemTuneGibbsSEXP);
    Rcpp::traits::input_parameter< int >::type nMcemPostBurn(nMcemPostBurnSEXP);
    Rcpp::traits::input_parameter< int >::type nMcemPostGibbs(nMcemPostGibbsSEXP);
    Rcpp::traits::input_parameter< int >::type lambdaWindow(lambdaWindowSEXP);
    Rcpp::traits::input_parameter< double >::type emConvTol(emConvTolSEXP);
    Rcpp::traits::input_parameter< bool >::type verboseIters(verboseItersSEXP);
    Rcpp::traits::input_parameter< bool >::type verboseErrors(verboseErrorsSEXP);
    Rcpp::traits::input_parameter< bool >::type doBen(doBenSEXP);
    Rcpp::traits::input_parameter< bool >::type regIntercept(regInterceptSEXP);
    Rcpp::traits::input_parameter< bool >::type doImputation(doImputationSEXP);
    __result = Rcpp::wrap(runGibbs(inData, dataScales, nTargets, lambda1Starts, lambda2Starts, sigmaStarts, tauStarts, betaStarts, missCode, nMcemApproxIters, nMcemTuneIters, nMcemApproxBurn, nMcemApproxGibbs, nMcemTuneBurn, nMcemTuneGibbs, nMcemPostBurn, nMcemPostGibbs, lambdaWindow, emConvTol, verboseIters, verboseErrors, doBen, regIntercept, doImputation));
    return __result;
END_RCPP
}
