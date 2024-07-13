#include "graph_matrix.h"
#include "graph_list.h"
#include <memory>
using namespace DataStructure::graph;

int main() {
    std::unique_ptr<Graph<int>> graph = std::make_unique<GraphMatrix<int>>(10);
    std::unique_ptr<Graph<int>> graph2 = std::make_unique<GraphList<int>>(10);

    for (Vertex i = 0; i < 10; i += 2)
    {
        for (Vertex j = i + 1; j < 10; j += 2)
        {
            graph -> addEdge(i, j);
            graph2 -> addEdge(i, j);
        }
    }

    graph -> printGraph();
    graph2 -> printGraph();

    return 0;
}