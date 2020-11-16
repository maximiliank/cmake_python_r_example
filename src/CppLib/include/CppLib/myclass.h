#pragma once

namespace CppLib {
    class MyClass {
        double a_;
        double b_;

    public:
        explicit MyClass(double a);
        explicit MyClass(double a, double b);

        double Area() const;
    };
}// namespace CppLib
