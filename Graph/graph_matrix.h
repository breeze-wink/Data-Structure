#pragma once
#include "graph.h"
#include <algorithm>
#include <functional>
#include <queue>
#include <stdexcept>
#include <sys/types.h>
#include <utility>
#include <vector>

namespace DataStructure::graph
{
    template <typename E>
    class GraphMatrix : public Graph<E>
    {
    public:
        GraphMatrix(int vertexCount_);
        virtual void addEdge(Vertex from, Vertex to, int weight = 1) override;
        virtual void removeEdge(Vertex from, Vertex to) override;
        virtual int getEdge(Vertex from, Vertex to) override;
        virtual void printGraph() override;
        virtual vector<Vertex> getAdjacentVertices(Vertex vertex) override;


        virtual vector<int> Dijkstra(Vertex start) override;
        virtual vector<int> Bellman_Ford(Vertex start, int steps = -1)override;
        vector<vector<int>> floyd();
        virtual vector<int> spfa(Vertex start)override;
        virtual bool containsNegativeCycle()override;
        virtual MSTResult Prim() override;
        virtual MSTResult Kruskal() override;

        ~GraphMatrix() = default;

    private:    
        std::vector<std::vector<int>> adjMatrix;
    };  

    template <typename E>
    GraphMatrix<E>::GraphMatrix(int vertexCount_): Graph<E>(vertexCount_)
    {
        adjMatrix.resize(this -> vertexCount, vector<int>(this -> vertexCount, INF));
        for (Vertex i = 0; i < this -> vertexCount; i++)
        {
            adjMatrix[i][i] = 0;
        }
    }
    template <typename E>
    void GraphMatrix<E>::addEdge(Vertex from, Vertex to, int weight)
    {
        if (from == to) return;

        if (from >= this -> vertexCount || to >= this -> vertexCount)
        {
            throw std::runtime_error("addEdge: vertex out of range");
        }
        adjMatrix[from][to] = std::min(weight, adjMatrix[from][to]);

        Edge e = {from, to, weight};
        
        auto it = this -> edges.find(e);

        if (it == this -> edges.end())
        {
            this -> edges.insert(e);
        }
        else
        {
            it -> weight = std::min(it -> weight, weight);
        }
    }

    template <typename E>
    void GraphMatrix<E>::removeEdge(Vertex from, Vertex to)
    {
        if (from >= this -> vertexCount || to >= this -> vertexCount)
        {
            throw std::runtime_error("removeEdge: vertex out of range");
        }
        Edge e = {from, to, adjMatrix[from][to]};
        
        auto it = this -> edges.find(e);
        if (it != this -> edges.end())
        {
            this -> edges.erase(it);
        }
        adjMatrix[from][to] = INF;
    }

    template <typename E>
    int GraphMatrix<E>::getEdge(Vertex from, Vertex to)
    {
        if (from >= this -> vertexCount || to >= this -> vertexCount)
        {
            throw std::runtime_error("getEdge: vertex out of range");
        }
        return adjMatrix[from][to];
    }

    template <typename E>
    
    vector<Vertex> GraphMatrix<E>::getAdjacentVertices(Vertex vertex)
    {

        if (vertex >= this -> vertexCount)
        {
            throw std::runtime_error("getAdjacentVertices: vertex out of range");
        }
        vector<Vertex> ans;
        for (Vertex i = 0; i < this -> vertexCount; i++)
        {
            if (adjMatrix[vertex][i] != INF || i != vertex)
            {
                ans.push_back(i);
            }
        }
        return ans;
    }

    template <typename E>

    void GraphMatrix<E>::printGraph()
    {
        for (Vertex i = 0; i < this -> vertexCount; i++)
        {
            std::cout << i << ": ";
            for (size_t j = 0; j < this -> vertexCount; j++)
            {
                if (adjMatrix[i][j] != INF && i != j)
                {
                    std::printf("(%lu, %d) ", j, adjMatrix[i][j]);
                }
            }
            std::cout << std::endl;
        }
    }

    template <typename E>
    vector<int> GraphMatrix<E>::Dijkstra(Vertex start)
    {
        if (start >= this -> vertexCount)
        {
            throw std::out_of_range("Dijkstra: start out of range");
        }

        vector<bool> visited(this -> vertexCount, false);
        vector<int> ans(this -> vertexCount, INF);

        ans[start] = 0;

        for (Vertex i = 0; i < this -> vertexCount; i ++)
        {
            Vertex nearNode = INF;
            for (Vertex j = 0; j < this -> vertexCount; j ++)
            {
                if (!visited[j] && (nearNode == INF || ans[j] < ans[nearNode]))
                {
                    nearNode = j;
                }
            }

            visited[nearNode] = true;
            for (Vertex j = 0; j < this -> vertexCount; j ++)
            {
                if (adjMatrix[nearNode][j] != INF)
                {
                    ans[j] = std::min(ans[j], ans[nearNode] + adjMatrix[nearNode][j]);
                }
            }
        }
        return ans;
    }

    template <typename E>
    vector<vector<int>> GraphMatrix<E>::floyd()
    {
        auto ans = adjMatrix;

        for (Vertex k = 0; k < this -> vertexCount; ++ k)
        {
            for (Vertex i = 0; i < this -> vertexCount; ++ i)
            {
                for (Vertex j = 0; j < this -> vertexCount; ++ j)
                {
                    ans[i][j] = std::min(ans[i][j], ans[i][k] + ans[k][j]);
                }
            }
        }
        return ans;
    }

    template <typename E>
    vector<int> GraphMatrix<E>::Bellman_Ford(Vertex start, int steps)
    {

        if (start >= this -> vertexCount)
        {
            throw std::out_of_range("Bellman-ford: start out of range");
        }

        vector<int> ans(this -> vertexCount, INF);
        vector<int> last(this -> vertexCount);
        ans[start] = 0;

        if (steps == -1) steps = this -> vertexCount - 1;

        for (int i = 0; i < steps; ++ i)
        {
            std::copy(ans.begin(), ans.end(), last.begin());
            for (const auto& e : this -> edges)
            {
                ans[e.to] = std::min(ans[e.to], last[e.from] + e.weight);
            }
        }

        //如果已经进行了 V - 1次松弛，可以再进行一次松弛，如果仍然有更小的距离，则说明图中存在负权环

        return ans;
    }

    template <typename E>
    vector<int> GraphMatrix<E>::spfa(Vertex start)
    {
        if (start >= this -> vertexCount)
        {
            throw std::out_of_range("spfa: start out of range");
        }

        std::queue<Vertex> q;
        vector<int> ans(this -> vertexCount, INF);
        vector<bool> inQueue(this -> vertexCount, false);

        ans[start] = 0;
        q.push(start);
        inQueue[start] = true;

        while (!q.empty())
        {
            Vertex v = q.front();
            q.pop();
            inQueue[v] = false;

            for (int i = 0; i < this -> vertexCount; i ++)
            {
                if (this -> adjMatrix[v][i] != INF && i != v && ans[i] > ans[v] + this -> adjMatrix[v][i])
                {
                    ans[i] = ans[v] + this -> adjMatrix[v][i];
                    if (!inQueue[i])
                    {
                        q.push(i);
                        inQueue[i] = true;
                    }
                }
            }
        }
        
        return ans;
    }

    template <typename E>
    bool GraphMatrix<E>::containsNegativeCycle()
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
            for (Vertex j = 0; j < this -> vertexCount; j ++)
            {
                if (adjMatrix[v][j] != INF && v != j)
                {
                    if (dist[j] > dist[v] + adjMatrix[v][j])
                    {
                        dist[j] = dist[v] + adjMatrix[v][j];
                        steps[j] = steps[v] + 1;
                        
                        if (steps[j] >= this -> vertexCount)
                        {
                            return true;
                        }
                        if (!inQueue[j])
                        {
                            q.push(j);
                        }
                    }
                }
            }
        }

        return true;
    }

    template <typename E>
    MSTResult GraphMatrix<E>::Prim()
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

            for (Vertex j = 0; j < this -> vertexCount; j ++)
            {
                if (adjMatrix[nearNode][j] != INF && adjMatrix[nearNode][j] < distences[j])
                {
                    distences[j] = adjMatrix[nearNode][j];
                    pre[j] = nearNode;
                }
            }
        }

        return std::make_pair(edgeSum, std::move(MSTedges));
    }

    template <typename E>
    MSTResult GraphMatrix<E>::Kruskal()
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
        vector<Edge> edges{this -> edges.begin(), this -> edges.end()};

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