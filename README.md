Create Python and R bindings for C++ with CMake
===============================================

This is an example CMake project to create Python and R bindings for your
C++ library using CMake. The usual tutorials for creating Python or R 
packages using C++ code relies on the respective tooling, see 
[Pybind11 Build systems](https://pybind11.readthedocs.io/en/stable/compiling.html "Python")
or [Rcpp introduction](https://cran.r-project.org/web/packages/Rcpp/vignettes/Rcpp-introduction.pdf "R").

The idea of this CMake setup is to bypass the respective build system and use CMake instead.
Mainly this works by building a shared library which is then included in the package.

The version number of the resulting package is set via the `CMake` variable `CppLIB_VERSION`.

Python
------

For creating the `Python` package `pybind11` is used together with `pip` to build or install the package. The binding 
code is placed in [`myclass_bindings.cpp`](src/Python/myclass_bindings.cpp).

The files `setup.py` and `init.py` are created via `configure_file`.

R
-

This setup uses `roxygen2` code documentation and `Rcpp` modules for package generation. Therefore
write your binding code as in [`myclass_export.cpp`](src/RPackage/src/myclass_export.cpp).

The `RPackageBuild` target then runs:
* Rcpp::compileAttributes()
* roxygen2::roxygenise(load_code=load_source)

to autogenerate the `RcppExports.cpp` and the `NAMESPACE` file before building the shared library. Further a `Makefile`
with no targets is created in the build directory together with the other required files to build a `R` package. 
Additionally the `R` directory is copied to the build folder. You can place there additional `.R` files if needed.
The file [`R/RCppLin-package.R`](src/RPackage/R/RCppLib-package.R) is required to load the class module exported within
`R`:
 
```
#' @useDynLib RCppLib, .registration = TRUE
#' @importFrom Rcpp sourceCpp
#' @export MyClass
NULL

Rcpp::loadModule("RCppLibModule", TRUE)
```

Make sure to adjust the name of your `R` library and the exported class within this file. Again, this file is processed
 by `roxygen2` to create appropriate entries in the `NAMESPACE` file. 

The `DESCRIPTION` file is created via `configure_file`.

Tests
-----

The testing section allows to check if the resulting package can be installed and used. For `python` it is installed in
a virtual environment in the binary directory of the test folder which is created on the first run.

For testing the `R` version of the package it will be installed into a ` libDir` inside binary test dir and the tests
are run by setting the environment variable `R_LIBS_USER`.

You can even write unit tests to test the package (for `R` the `testthat` package is required), see 
[`test_sample.py`](tests/Python/test_sample.py) or [`test_package.R`](tests/R/test_package.R).


Example usage
-------------

Tested it with `g++` 10.2.0, `R` 4.0.2 and `Python` 3.8.6 on linux.

Create a `build` directory and run `CMake`:

```shell script
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
```

Then you can create, install or test the package:

```shell script
# Python
# build
cmake --build . --target PyPackageBuild
# install
cmake --build . --target PyPackageInstall
# build test
cmake --build . --target PyTests

# R
# build
cmake --build . --target RPackageBuild
# install
cmake --build . --target RPackageInstall
# build test
cmake --build . --target RTests

# run all tests
ctest
```

If you only want to create only one of the packages you can add the following parameter to `CMake`:
* only `python`: `-DBUILD_RPACKAGE=OFF`
* only `R`: `-DBUILD_PYPACKAGE=OFF`
