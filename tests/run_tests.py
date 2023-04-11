import os
import sys
import unittest
sys.path.append(os.path.dirname(os.path.dirname(os.path.dirname(__file__))))

if __name__ == "__main__":
    loader = unittest.TestLoader()
    current_folder = os.path.dirname(__file__)
    cpp_folder = os.path.join(current_folder, "tests_cpp")

    print("Loading tests from '{folder}'".format(folder=cpp_folder))
    test_suite = loader.discover(cpp_folder)
    test_count = test_suite.countTestCases()

    print("Executing {count} tests...".format(count=test_count))
    runner = unittest.TextTestRunner()
    runner.run(test_suite)
