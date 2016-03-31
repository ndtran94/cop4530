# makefile for BGS routing
# program #1
# COP4530

proj1.x : main.o route.o list.o
        g++47 -oproj1.x main.o route.o list.o
route.o : route.h route.cpp
        g++47 -c -I. route.cpp
list.o : list.h list.cpp
        g++47 -c -I. list.cpp
main.o : list.h route.h main.cpp
        g++47 -c -I. main.cpp