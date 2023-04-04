
#include <string>
#include <pybind11/pybind11.h>

namespace py = pybind11;

Tank run(std::string paths, std::string keys){

    Tank tank(paths, keys);
    return tank;

}

