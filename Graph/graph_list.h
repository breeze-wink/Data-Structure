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
        using Edge = std::pair<Vertex, int>;

    public:
        GraphList<E>(int vertices);
        ~GraphList<E>() = default;
        virtual void addEdge(Vertex from, Vertex to, int weight = 1);
        virtual void removeEdge(Vertex from, Vertex to);
        virtual void printGraph();
        virtual vector<Vertex> getAdjacentVertices(Vertex vertex);
        virtual int getEdge(Vertex from, Vertex to);

        virtual vector<int> Dijkstra(Vertex start);
    private:
        std::vector<std::forward_list<Edge>> adjList;
    };

    template <typename E>
    GraphList<E>::GraphList(int vertices) : Graph<E>(vertices)
    {
        this -> VertexCount = vertices;
        adjList.resize(vertices);
    }

    template <typename E>
    void GraphList<E>::addEdge(Vertex from, Vertex to, int weight)
    {
        if (from == to) return;
        
        if (from >= this -> VertexCount || to >= this -> VertexCount)
        {
            throw std::out_of_range("addEdge: Vertex out of range");
        }
        adjList[from].emplace_front(std::make_pair(to, weight));
    }

    template <typename E>
    void GraphList<E>::removeEdge(Vertex from, Vertex to)
    {
        if (from >= this -> VertexCount || to >= this -> VertexCount)
        {
            throw std::out_of_range("removeEdge: Vertex out of range");
        }
        adjList[from].remove_if([&to](const Edge& edge){
            return edge.first == to;
        });
    }

    template <typename E>
    vector<Vertex> GraphList<E>::getAdjacentVertices(Vertex vertex)
    {
        if (vertex >= this -> VertexCount)
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
        if (from >= this -> VertexCount || to >= this -> VertexCount)
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
        for (Vertex i = 0; i < this -> VertexCount; i ++)
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
        using PIV = std::pair<int, Vertex>;

        std::priority_queue<PIV, vector<PIV>, std::greater<PIV>> heap;

        vector<bool> visited(this -> VertexCount, false);
        vector<E> ans(this -> VertexCount, INF);

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
}