# MIBRR Development ToDo List
## Kyle M. Lang
## Last Update: 2017-OCT-01

# 2017-OCT-30:
## Find a good way to compute data centers with missing values

- Need to center data for the BEN to work, but center computed from incomplete data will be biased.
- How can we get unbiased centers to use for correctly re-centering the imputed data?

## Implement MCEM for MIBL

- Still need to add the deterministic update step for BL lambda

# 2017-SEP-30:
## Assess the current state of the package

- What works, what does not?

## Remove Nlopt - DONE (2017-OCT-01)

- Installing `NLopt` is proving to be a huge barrier to portability

## Replace NLopt with the initial R-based `optimx` optimization - DONE (2017-OCT-01)

- We may see a perfomance hit, but we'll probably fold the MCEM tasks into the Gibss sampler in the future, anyway
- Using `optimx` won't induce any portabi

# 2016-NOV-07:
## Check that we didn't break anything when moving to the new way of indexing missing data

- The results are looking dubious--we need to find out why
    - The initial missing data treatment is a prime suspect
    - As is the new indexing method and potential problems with the post-processing that it may have induced
    - If we can get a stable version running, we need to start some simulations before doing any more development work.

# 2016-NOV-05:
## Remove intercept regularization option -- DONE
## Use FIML to get means for centering -- DONE (and reverted)

- FIML will be cumbsersome/infeasible when P > N
    - I tried implmenting an imputation-based solution
    - Don't know if this worked, may be a cause of the poor performance that we need to track down.