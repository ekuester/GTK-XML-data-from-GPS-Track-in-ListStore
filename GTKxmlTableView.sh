#! /bin/sh -e
program="GTKxmlTableView"
./linguas.sh
echo "now compiling $program..." 
cd ./src
g++ `pkg-config gtkmm-3.0 --cflags --libs` `pkg-config libxml++-3.0 --cflags --libs` -c main.cpp trackpoint.cpp xmltablewindow.cpp
g++ main.o trackpoint.o xmltablewindow.o -o $program `pkg-config gtkmm-3.0 --cflags --libs` `pkg-config libxml++-3.0 --cflags --libs`
cd ..
./src/$program
