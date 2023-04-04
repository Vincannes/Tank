# Tank
Convert mixing database from a software to another.

# Working

# Compile
## Windows
```bash
cmake -DCMAKE_INSTALL_PREFIX=../lib ..
```
```bash
g++ *.cpp -o hello -I"D:\Desk\python\Tank\lib\rapidjson\include"  
```
```bash
g++ *.cpp -o hello && hello.exe "{'rootDir': 'C', 'desk': '@rootDir\\{dir}', 'test': '@desk\\{Shot}\\{Task}', 'nuke': '@test\\nuke\\{Shot}-{Task}-base-v{version}.nk', 'test_diff': '@desk\\nuke\\{Shot}-{Task}-base-v{version}.nk'}"          
```
Install Library
```bash
cmake -G "Visual Studio 17 2022" -A x64 -DCMAKE_INSTALL_PREFIX=../lib .. && cmake --build . --config Release --target install       
```
## Convert Python
```
D:\Desk\python\swigwin-4.1.1\swig.exe -c++ -python ./main.i   
```
```
g++ -c main_wrap.cxx -IC:\Users\vince\AppData\Local\Programs\Python\Python39\include  
```
```
g++ -shared main_wrap.o -o _main.so -lpython3.9   
```
