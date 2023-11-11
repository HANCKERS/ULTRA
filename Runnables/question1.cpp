#include "../Algorithms/Dijkstra/Dijkstra.h"  
#include "../Helpers/Helpers.h"
#include <iostream>
#include <ctime>

using namespace std;

int main() {
    FloridaGraph floridaGraph;
    // Load the graph from your data source (e.g., file or memory)

    const int numPairs = 200;

    srand(time(nullptr));

    double totalRuntime = 0.0;

    for (int i = 0; i < numPairs; ++i) {
        const Vertex source = Random::nextInt(floridaGraph.numVertices());
        const Vertex destination = Random::nextInt(floridaGraph.numVertices());

        const auto start = chrono::high_resolution_clock::now();

        Dijkstra<FloridaGraph> dijkstra(floridaGraph);
        dijkstra.run(source, destination);

        const auto end = chrono::high_resolution_clock::now();
        const double runtime = chrono::duration<double>(end - start).count();

        totalRuntime += runtime;

        cout << "Source: " << source << ", Target: " << destination << "\n";
        cout << "Shortest Path: ";
        for (const Vertex vertex : dijkstra.getPath(destination)) {
            cout << vertex << " - ";
        }
        cout << "\nShortest path length: " << dijkstra.getDistance(destination) << "\n\n";
    }

    cout << "Total runtime in seconds for 200 random Dijkstra: " << totalRuntime << "\n";

    return 0;
}
