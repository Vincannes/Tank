# Tank
Convert mixing database from a software to another.


# Compile
## Windows

## Build cpp
```bash
cd /d D:\Desk\python\Tank\cpp\src 
cls & g++ *.cpp -o main & main.exe 
```

From folder cpp/build
```bash
cls & cmake .. & cmake --build . --config Release & mklink /J D:\Desk\python\Tank\cpp\bin D:\Desk\python\Tank\cpp\build\Release 
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
