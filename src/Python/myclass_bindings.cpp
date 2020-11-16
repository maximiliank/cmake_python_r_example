#include "CppLib/myclass.h"
#include "CppLib/myfunction.h"
#include <pybind11/pybind11.h>


PYBIND11_MODULE(PyCppLib, m)
{
    namespace py = pybind11;

    py::class_<CppLib::MyClass>(m, "MyClass")
            .def(py::init<double>())
            .def(py::init<double, double>())
            .def("Area", &CppLib::MyClass::Area, "Returns the are of MyClass");

    m.def("myfunction", &CppLib::myfunction);
}
