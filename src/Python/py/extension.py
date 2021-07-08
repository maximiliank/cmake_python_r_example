import pandas as pd
from PyCppLib import vec_add


def py_sum(a: float, b: float):
    print("Called py_sum")
    return a + b


def vector_function(a: pd.Series, b: pd.Series):
    print("Called vector_function, convert pd.Series arguments to numpy and call C++ implementation")
    return vec_add(a.to_numpy(), b.to_numpy())
