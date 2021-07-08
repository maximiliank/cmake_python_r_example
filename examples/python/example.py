import pandas as pd
from PyCppLib.extension import py_sum, vector_function
from PyCppLib import myfunction, vec_add, vec_square_inplace

print(py_sum(1., 3.))
print(myfunction(2., 3.))

df = pd.DataFrame({'a': [1., 2., 3.], 'b': [4., 5., 6.]})
print(vec_add(df['a'].to_numpy(), df['b'].to_numpy()))
res = vector_function(df['a'], df['b'])
print(res)
print("Calling vec_square_inplace on res")
vec_square_inplace(res)
print(res)
