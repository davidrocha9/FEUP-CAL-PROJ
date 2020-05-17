cmake_minimum_required(VERSION 3.15)
project(Segunda_Entrega)

set(CMAKE_CXX_STANDARD 14)

add_executable(Segunda_Entrega main.cpp Menus/Menu.cpp Menus/Menu.h Menus/Utils.cpp Menus/Utils.h Graph/Graph.cpp Graph/Graph.h Files/FileReader.cpp Files/FileReader.h Graph/MutablePriorityQueue.h Graph/GraphViewer.cpp Graph/GraphViewer.h lib/connection.cpp lib/connection.h lib/edgetype.h lib/graphviewer.cpp lib/graphviewer.cpp)