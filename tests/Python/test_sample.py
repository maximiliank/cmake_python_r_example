import unittest
import PyCppLib


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


if __name__ == '__main__':
    unittest.main()
