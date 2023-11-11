#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

#include "../../Helpers/Meta.h"
#include "../../Helpers/Types.h"
#include "../../Helpers/Timer.h"
#include "../../Helpers/String/String.h"
#include "../../Helpers/Vector/Vector.h"

#include "../../DataStructures/Container/ExternalKHeap.h"
#include "../../DataStructures/Container/Set.h"
#include "../../DataStructures/Attributes/AttributeNames.h"

#include "../Algorithms/Dijkstra/Dijkstra.h"

using namespace std;

GRAPH readGraphFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        exit(EXIT_FAILURE);
    }

    GRAPH graph;
    string line;
    while (getline(file, line)) {
        istringstream iss(line);

        if (line[0] == 'c') {
            continue;  // Ignore comments
        } else if (line[0] == 'p') {
            string problemType;
            int vertices, edges;
            iss >> problemType >> vertices >> edges;
            graph = GRAPH(vertices);
        } else if (line[0] == 'a') {
            int u, v, w;
            iss >> u >> v >> w;
            graph.addEdge(u, v, w);
        }
    }

    file.close();
    return graph;
}

int main() {
    srand(static_cast<unsigned>(time(0)));  // Seed for random number generation

    GRAPH floridaGraph = readGraphFromFile("USA-road-d.FLA.gr");
    Dijkstra<GRAPH> dijkstraInstance(floridaGraph);

    clock_t start = clock();

    const int numPairs = 200;
    for (int i = 0; i < numPairs; ++i) {
        int source = rand() % floridaGraph.vert();
        int destination = rand() % floridaGraph.vert();

        dijkstraInstance.run(source, destination);

        cout << "Shortest Path: ";
        auto path = dijkstraInstance.getPath(destination);
        for (const auto& vertex : path) {
            cout << vertex << ' ';
        }
        cout << "sp: " << dijkstraInstance.getDistance(destination) << endl;
    }

    clock_t endt = clock();
    double runtime = static_cast<double>(endt - start) / CLOCKS_PER_SEC;
    cout << "Total runtime in seconds for " << numPairs << " random Dijkstra: " << runtime << endl;

    return 0;
}
