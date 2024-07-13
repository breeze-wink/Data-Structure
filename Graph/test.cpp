#include "graph_matrix.h"
#include "graph_list.h"
#include <memory>
using namespace DataStructure::graph;

int main() {
    std::unique_ptr<Graph<int>> graph = std::make_unique<GraphMatrix<int>>(10);

    int n, m;
    std::cin >> n >> m;

    while (m --)
    {
        int x, y, z;
        std::cin >> x >> y >> z;

        graph -> addEdge(x - 1, y - 1, z);
    }

    auto res = graph -> Dijkstra(0);

    std::cout << res[n - 1] << std::endl;

    return 0;
}