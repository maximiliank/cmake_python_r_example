#include "CppLib/myclass.h"

CppLib::MyClass::MyClass(double a)
    : a_(a), b_(a)
{}

CppLib::MyClass::MyClass(double a, double b)
    : a_(a), b_(b)
{}

double CppLib::MyClass::Area() const
{
    return a_ * b_;
}
