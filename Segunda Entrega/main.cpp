#include <iostream>
#include <fstream>
#include <chrono>
#include "Menus/Menu.h"
#include "Menus/Menu.h"
#include "Menus/Utils.h"
#include "Files/FileReader.h"
#include "Algorithms/dijkstra.h"
#include "Algorithms/dfs.h"

void generateGraphDijsktra(Graph graph) {
    srand(time(NULL));
    ofstream outputFile;
    string fileName = "./graph.csv";
    outputFile.open(fileName, ios::app);
    int j = 500;
    for (int n = 1; n <= 10; n ++) {
        // Start the clock for this n
        auto start = chrono::high_resolution_clock::now();
        // Create 1000 sequences
        for (int i = 0; i < j; i++) {
            int start_id = rand() % (graph.getVertexSet().size() - 1);
            if (graph.findVertex(start_id) == nullptr){
                continue;
            }
            int end = rand() % (graph.getVertexSet().size() - 1);
            if (graph.findVertex(end) == nullptr){
                continue;
            }
            vector<int> v;
            dijkstraShortestPath(graph, start_id, end, v);
        }

        // Stop the clock
        auto finish = chrono::high_resolution_clock::now();
        // Get the total time
        auto mili = chrono::duration_cast<chrono::milliseconds>(finish - start).count();
        // Print to the .csv file
        cout << j << " -> " << mili << endl;
        outputFile << j << "," << mili << endl;
        j += 100;
    }
    outputFile.close();
}

int main() {
    // para calcular graficos - manter comentado caso contrario
    Graph graph = createGraph(3, 1);
    //generateGraphDijsktra(graph);
    mainMenu();
    return 0;
}