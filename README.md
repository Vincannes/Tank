# Tank
Convert mixing database from a software to another.


# Compile
## Windows

## Build cpp
```bash
 cls & g++ *.cpp -o main & main.exe 
```

From folder cpp/build
```bash
cls & 
cmake -DCMAKE_C_COMPILER="C:/mingw64/bin/gcc.exe" -DCMAKE_CXX_COMPILER="C:/mingw64/bin/g++.exe" -G "MinGW Makefiles" .. & cmake --build . --config Release 
& mklink /J D:\Desk\python\Tank\cpp\bin D:\Desk\python\Tank\cpp\build\Release 
```
```
cd /d D:\Desk\python\Tank\cpp\build & cls & cmake .. & cmake --build . --config Release & mklink /J D:\Desk\python\Tank\cpp\bin D:\Desk\python\Tank\cpp\build\Release 
```

## SimLink build cpp to ../cpp/lib 
```bash
mklink /J D:\Desk\python\Tank\cpp\bin D:\Desk\python\Tank\cpp\build\Release 
```
# TODO

- Make for different OS
    - [ ] Windows
    - [ ] Linux
    - [ ] Darwin
- [ ] Do docstring
- [ ] Matching Template get static token on it.
- [ ] if "/" remove "/" at the end of Root Path in tank initialisation
- [ ] Template name sometime first letter is remove at the name, check if the fist caract is a letter or "," when creating dictionnary for Paths
