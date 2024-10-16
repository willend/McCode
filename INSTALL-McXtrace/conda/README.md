# Install McXtrace 3.5.1 through conda-forge (macOS, Linux or Windows host)

* We a set of conda-packages for installing McXtrace 3.5.1.x through conda

## Get yourself a conda / mamba
Due to the complex [licensing situation](https://discuss.scientific-python.org/t/response-to-anaconda-switch-to-paid-plans/1395) with the commercial Anaconda ecosystem, we clearly recommend McXtrace users to start from an open-source entry-point such as
* [miniforge](https://github.com/conda-forge/miniforge) or
* [micromamba](https://mamba.readthedocs.io/en/latest/user_guide/micromamba.html)

## Optionally create a dedicated environment and load it
* ```conda create --name mcxtrace ```
* ```conda activate mcxtrace```

## Install McXtrace, compilers, openmpi
* ```mamba install mcxtrace compilers openmpi=4```
  
(From next McXtrace release newer openmpi versions are also OK, but the 3.5.1 version of mcrun has an issue with openmpi 5.x)

## Note for use on Windows
At the time of release for 3.5.1 MCPL is notr yet available for Windows on conda-forge, so related instruments will not compile/function.
We expect this dependency to become available during the fall/winter of 2024.

## Install McXtraceScript, jypyterlab ipympl
* ```mamba install pip jupyterlab ipympl```
* ```pip install mcxtracescript```

You are welcome to contact us in case of issues, e.g. via
*   [mcxtrace-users](mailto:mcxtrace-users@mcxtrace.org)
* by creating an issue on [the McCode issue tracker](https://github.com/McStasMcXtrace/McCode/issues)
