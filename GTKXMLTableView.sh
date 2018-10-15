g++ `pkg-config gtkmm-3.0 --cflags --libs` `pkg-config libxml++-3.0 --cflags --libs` -c main.cpp trackpoint.cpp xmltablewindow.cpp
g++ main.o trackpoint.o xmltablewindow.o -o GTKXMLTableView `pkg-config gtkmm-3.0 --cflags --libs` `pkg-config libxml++-3.0 --cflags --libs`
./GTKXMLTableView


