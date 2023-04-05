
#include <string>
#include <pybind11/pybind11.h>

#include "tank_obj.h"

namespace py = pybind11;


Tank run(std::string paths, std::string keys){

    Tank tank(paths, keys);
    return tank;

}


// PYBIND11_MODULE(tank, m){

//     m.doc() = R"Add documentation here";

//     m.def("get_tank", &run);
// }
