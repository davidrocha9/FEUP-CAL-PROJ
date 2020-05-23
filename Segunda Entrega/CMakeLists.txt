cmake_minimum_required(VERSION 3.15)
project(Segunda_Entrega)

set(CMAKE_CXX_STANDARD 14)

add_executable(Segunda_Entrega main.cpp Menus/Menu.cpp Menus/Menu.h Menus/Utils.cpp Menus/Utils.h Graph/Graph.cpp Graph/Graph.h Files/FileReader.cpp Files/FileReader.h Graph/MutablePriorityQueue.h Graph/GraphViewer.cpp Graph/GraphViewer.h Algorithms/dijkstra.cpp Algorithms/dijkstra.h Algorithms/yen.cpp Algorithms/yen.h lib/connection.cpp lib/connection.h lib/edgetype.h lib/graphviewer.cpp lib/graphviewer.cpp Menus/Worker.h Menus/Worker.cpp Algorithms/bfs.cpp Algorithms/bfs.h Menus/pathGenerator.cpp Menus/pathGenerator.h Menus/Worker.cpp Menus/Worker.h Menus/Path.cpp Menus/Path.h)