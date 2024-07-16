#pragma once
#include "graph.h"
#include "graph_matrix.h"
#include <forward_list>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>
#include <list>


namespace DataStructure::graph
{
    template <typename E>
    class GraphList: public Graph<E>
    {
        using PVI = std::pair<Vertex, int>;

    public:
        GraphList<E>(int vertices);
        ~GraphList<E>() = default;
        virtual void addEdge(Vertex from, Vertex to, int weight = 1) override;
        virtual void removeEdge(Vertex from, Vertex to) override;
        virtual void printGraph() override;
        virtual vector<Vertex> getAdjacentVertices(Vertex vertex) override;
        virtual int getEdge(Vertex from, Vertex to) override;
        


        virtual vector<int> Dijkstra(Vertex start) override;
        virtual vector<int> Bellman_Ford(Vertex start, int steps = -1) override;
        virtual vector<int> spfa(Vertex start) override;
        virtual bool containsNegativeCycle() override;
        virtual MSTResult Prim() override;
        virtual MSTResult Kruskal() override;
    private:
        std::vector<std::forward_list<PVI>> adjList;
    };

    template <typename E>
    GraphList<E>::GraphList(int vertices) : Graph<E>(vertices)
    {
        this -> vertexCount = vertices;
        adjList.resize(vertices);
    }

    template <typename E>
    void GraphList<E>::addEdge(Vertex from, Vertex to, int weight)
    {
        if (from == to) return;
        
        if (from >= this -> vertexCount || to >= this -> vertexCount)
        {
            throw std::out_of_range("addEdge: Vertex out of range");
        }
        adjList[from].emplace_front(std::make_pair(to, weight));
    }

    template <typename E>
    void GraphList<E>::removeEdge(Vertex from, Vertex to)
    {
        if (from >= this -> vertexCount || to >= this -> vertexCount)
        {
            throw std::out_of_range("removeEdge: Vertex out of range");
        }
        adjList[from].remove_if([&to](const PVI& edge){
            return edge.first == to;
        });
    }

    template <typename E>
    vector<Vertex> GraphList<E>::getAdjacentVertices(Vertex vertex)
    {
        if (vertex >= this -> vertexCount)
        {
            throw std::out_of_range("getAdjacentVertices: Vertex out of range");
        }
        vector<Vertex> result;
        for (const auto& edge : adjList[vertex])
        {
            result.push_back(edge.first);
        }
    }

    template <typename E>
    int GraphList<E>::getEdge(Vertex from, Vertex to)
    {
        if (from >= this -> vertexCount || to >= this -> vertexCount)
        {
            throw std::out_of_range("getEdge: Vertex out of range");
        }
        for (const auto& edge : adjList[from])
        {
            if (edge.first == to)
            {
                return edge.second;
            }
        }

        return -1;
    }

    template <typename E>
    void GraphList<E>::printGraph()
    {
        for (Vertex i = 0; i < this -> vertexCount; i ++)
        {
            std::cout << i << ": ";
            for (const auto& edge : adjList[i])
            {
                std::cout << "(" << edge.first << ", " << edge.second << ") ";
            }
            std::cout << std::endl;
        }
    }

    template <typename E>
    vector<int> GraphList<E>::Dijkstra(Vertex start)
    {
        if (start >= this -> vertexCount)
        {
            throw std::out_of_range("Dijkstra: start vertex is out of range");
        }

        using PIV = std::pair<int, Vertex>;

        std::priority_queue<PIV, vector<PIV>, std::greater<PIV>> heap;

        vector<bool> visited(this -> vertexCount, false);
        vector<E> ans(this -> vertexCount, INF);

        heap.push(std::make_pair(start, 0));

        while (heap.size())
        {
            auto p = heap.top();
            heap.pop();

            int distance = p.first;
            Vertex nearNode = p.second;

            if (visited[nearNode])
            {
                continue;
            }

            visited[nearNode] = true;

            for (const auto& edge : adjList[nearNode])
            {
                if (ans[edge.first] > distance + edge.second)
                {
                    ans[edge.first] = distance + edge.second;
                    heap.push(std::make_pair(ans[edge.first], edge.first));
                }
            }
        }

        return ans;
    }

    template <typename E>
    vector<int> GraphList<E>::Bellman_Ford(Vertex start, int steps)
    {
        if (start >= this -> vertexCount)
        {
            throw std::out_of_range("Bellman-ford: start vertex is out of range");
        }
        vector<Edge> edges;
        vector<int> ans(this -> vertexCount, INF);
        vector<int> last(this -> vertexCount);
        ans[start] = 0;

        for (Vertex i = 0; i < this -> vertexCount; i ++)
        {
            for (auto e : adjList[i])
            {
                edges.emplace_back(Edge{i, e.first, e.second});
            }
        }

        if (steps == -1) steps = this -> vertexCount - 1;

        for (int i = 0; i < steps; ++ i)
        {
            std::copy(ans.begin(), ans.end(), last.begin());
            for (const auto& e : edges)
            {
                ans[e.to] = std::min(ans[e.to], last[e.from] + e.weight);
            }
        }

        return ans;
    }

    template <typename E>
    vector<int> GraphList<E>::spfa(Vertex start)
    {
        if (start >= this -> vertexCount)
        {
            throw std::out_of_range("spfa: start vertex is out of range");
        }

        vector<int> ans(this -> vertexCount, INF);
        vector<bool> inQueue(this -> vertexCount, false);
        std::queue<Vertex> q;

        ans[start] = 0;
        q.push(start);
        inQueue[start] = true;

        while (!q.empty())
        {
            Vertex v = q.front();
            q.pop();
            inQueue[v] = false;

            for (const auto& e : this -> adjList[v])
            {
                Vertex to = e.first;
                int dist = e.second;

                if (ans[to] > ans[v] + dist)
                {
                    ans[to] = ans[v] + dist;
                    if (!inQueue[to])
                    {
                        inQueue[to] = true;
                        q.push(to);
                    }
                }
            }
        }

        return ans;
    }

    template <typename E>
    bool GraphList<E>::containsNegativeCycle()
    {
        std::queue<Vertex> q;
        vector<int> dist(this -> vertexCount, 0);
        vector<uint> steps(this -> vertexCount, 0);
        vector<bool> inQueue(this -> vertexCount, true);
        
        for (Vertex i = 0; i < this -> vertexCount; i++)
        {
            q.push(i);
        }

        while (!q.empty())
        {
            Vertex v = q.front();
            q.pop();
            inQueue[v] = false;

            for (const auto& e : adjList[v])
            {
                Vertex to = e.first;
                int weight = e.second;

                if (dist[to] > dist[v] + weight)
                {
                    dist[to] = dist[v] + weight;
                    steps[to] = steps[v] + 1;

                    if (steps[to] >= this -> vertexCount)
                    {
                        return true;
                    }

                    if (!inQueue[to])
                    {
                        q.push(to);
                    }
                }
            }
        }

        return false;
    }

    template <typename E>
    MSTResult GraphList<E>::Prim()
    {
        vector<int> distences(this -> vertexCount, INF);
        vector<int> pre(this -> vertexCount, -1);
        vector<bool> inMST(this -> vertexCount, false);
        vector<Edge> MSTedges;
        int edgeSum = 0;
        distences[0] = 0;
        
        for (int i = 0; i < this -> vertexCount; i ++)
        {
            int nearNode = -1;

            for (Vertex j = 0; j < this -> vertexCount; j ++)
            {
                if (! inMST[j] && (nearNode == -1 || distences[j] > distences[nearNode]))
                {
                    nearNode = j;
                }
            }
            
            if (distences[nearNode] == INF)
            {
                return std::make_pair(-1, vector<Edge>()); // 不存在MST
            }

            inMST[nearNode] = true;
            MSTedges.emplace_back(Edge{(Vertex)(pre[nearNode]), (Vertex)(nearNode), distences[nearNode]});
            edgeSum += distences[nearNode];

            for (const auto& e : adjList[nearNode])
            {
                Vertex j = e.first;
                int dist = e.second;

                if (dist < distences[j])
                {
                    distences[j] = dist;
                    pre[j] = nearNode;
                }
            }
        }

        return std::make_pair(edgeSum, std::move(MSTedges));
    }

    template <typename E>
    MSTResult GraphList<E>::Kruskal()
    {
        vector<Edge> MSTedges;
        int edgeSum = 0;
        uint edgeCount = 0;

        vector<Vertex> father(this -> vertexCount);
        for (int i = 0; i < this -> vertexCount; ++i)
        {
            father[i] = i;
        }

        //边的存储可以直接加一个成员变量，在插入的时候就维护
        vector<Edge> edges;

        for (Vertex i = 0; i < this -> vertexCount; ++ i)
        {
            for (Vertex j = 0; j < this -> vertexCount; ++ j)
            {
                if (this -> adjMatrix[i][j] != INF && i != j)
                {
                    edges.emplace_back(Edge{i, j, this -> adjMatrix[i][j]});
                }
            }
        }

        std::sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) {
            return a.weight < b.weight;
        });

        std::function<Vertex(Vertex)> find = [&](Vertex x) { //有趣的写法
            if (father[x] != x) {
                father[x] = find(father[x]);
            }
            return father[x];
        };

        for (const auto& edge : edges)
        {
            Vertex a = edge.from, b = edge.to;
            if (find(a) != find(b))
            {
                father[find(a)] = find(b);
                MSTedges.emplace_back(edge);
                edgeSum += edge.weight;
                edgeCount ++;
            }
        }

        if (edgeCount != this -> vertexCount - 1)
        {
            return std::make_pair(-1, vector<Edge>());
        }

        return std::make_pair(edgeSum, std::move(MSTedges));
    }
}