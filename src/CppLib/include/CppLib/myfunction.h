#pragma once

#include <span>
#include <vector>

namespace CppLib {
    double myfunction(double a, double b);

    std::vector<double> vec_add(std::span<const double> a, std::span<const double> b);

    void vec_square_inplace(std::span<double> a);
}// namespace CppLib
