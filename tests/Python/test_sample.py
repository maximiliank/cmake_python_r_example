import unittest
import PyCppLib
import numpy as np


class TestPyCppLib(unittest.TestCase):

    def test_myclass1(self):
        mc = PyCppLib.MyClass(3)
        self.assertEqual(mc.Area(), 9)

    def test_myclass2(self):
        mc = PyCppLib.MyClass(3, 4)
        self.assertEqual(mc.Area(), 12)

    def test_myfunction(self):
        res = PyCppLib.myfunction(3, 4)
        self.assertEqual(res, 12)

    def test_vec_add(self):
        a = np.array([1., 2., 3.])
        b = np.array([4., 5., 6.])
        res = PyCppLib.vec_add(a, b)
        np.testing.assert_array_equal(res, np.array([5., 7., 9.]))

    def test_vec_square_inplace(self):
        a = np.array([4., 5., 6.])
        PyCppLib.vec_square_inplace(a)
        np.testing.assert_array_equal(a, np.array([16., 25., 36.]))


if __name__ == '__main__':
    unittest.main()
