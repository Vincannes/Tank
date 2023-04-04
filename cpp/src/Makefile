all: prog

prog : utils.o template_keys.o template_obj.o conform_path.o main.o #tank.o -lstdc++
	g++ -o prog utils.o template_keys.o template_obj.o conform_path.o main.o

utils.o : utils.cpp
	g++ -o utils.o -c utils.cpp

template_keys.o : template_keys.cpp
	g++ -o template_keys.o -c template_keys.cpp

template_obj.o : template_obj.cpp
	g++ -o template_obj.o -c template_obj.cpp

conform_path.o : conform_path.cpp
	g++ -o conform_path.o -c conform_path.cpp

templates_obj.o : templates_obj.cpp
	g++ -o templates_obj.o -c templates_obj.cpp

#tank.o : tank.cpp
#	g++ -o tank.o -c tank.cpp

main.o : main.cpp
	g++ -o main.o -c main.cpp

clean :
	del *.o