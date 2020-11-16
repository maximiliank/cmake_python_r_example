#include <Rcpp.h>

#include "CppLib/myclass.h"

RCPP_MODULE(RCppLibModule)
{
    Rcpp::class_<CppLib::MyClass>("MyClass")
            .factory([]() -> CppLib::MyClass* {
                Rcpp::stop("Default constructor is disabled for this class");
            })
            .constructor<double>()
            .constructor<double, double>()
            .const_method("Area", &CppLib::MyClass::Area, "Returns the area of MyClass");
}

#include "CppLib/myfunction.h"

//' Free function that returns the product of its two double arguments
//'
//' @return The product of its two double arguments
//'
//' @export
// [[Rcpp::export]]
double myfunction(const double a, const double b)
{
    return CppLib::myfunction(a, b);
}
