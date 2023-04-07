/* File : tuto.i */
/* swig -c++ -python binder.i */
/* g++ -c binder_wrap.cxx -I C:\Users\vince\AppData\Local\Programs\Python\Python39\include   */
/* g++ -shared binder.so -o _binder.pyd -L C:\Users\vince\AppData\Local\Programs\Python\Python39\libs -l python3 */
/* cls & swig -c++ -python binder.i & g++ -c binder_wrap.cxx -I C:\Users\vince\AppData\Local\Programs\Python\Python39\include */
%module binder

%{
#include <map>
#include <string>
#include "utils.h"
#include "template_obj.h"
#include "templates_obj.h"
#include "tank_obj.h"
%}

%include "std_map.i"
%include "std_string.i"
%include "tank_obj.h"

