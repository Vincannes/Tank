# in __main__.py
import os
import unittest

if __name__ == "__main__":
    loader = unittest.TestLoader()
    current_folder = os.path.dirname(__file__)

    print("Loading tests from '{folder}'".format(folder=current_folder))
    test_suite = loader.discover(current_folder)
    test_count = test_suite.countTestCases()

    print("Executing {count} tests...".format(count=test_count))
    runner = unittest.TextTestRunner()
    runner.run(test_suite)