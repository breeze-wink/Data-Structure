#pragma once
#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

using std::vector;

namespace DataStructure::graph
{
    using Vertex = size_t;
    constexpr int INF = std::numeric_limits<int>().max() / 2;

    struct Edge
    {
        Vertex from;
        Vertex to;
        int weight;
    };

    template <typename E>
    class Graph
    {
    public:
        Graph(size_t vertexCount) : vertexCount(vertexCount)
        {
            vertices.resize(vertexCount);
        }
        virtual void addEdge(Vertex from, Vertex to, int weight = 1) = 0;
        virtual void removeEdge(Vertex from, Vertex to) = 0;
        virtual void printGraph() = 0;
        virtual int getEdge(Vertex from, Vertex to) = 0;
        virtual vector<Vertex> getAdjacentVertices(Vertex vertex) = 0;
        
        virtual ~Graph() = default;


        virtual vector<int> Dijkstra(Vertex start) = 0;
        virtual vector<int> Bellman_Ford(Vertex start, int steps = -1) = 0;
        virtual vector<int> spfa(Vertex start) = 0;
        virtual bool containsNegativeCycle() = 0;

    public:
        void setVertex(Vertex vertex, E value);
        E getVertex(Vertex vertex);
        
    protected:
        size_t vertexCount;
        std::vector<E> vertices;
    };

    template <typename E>
    E Graph<E>::getVertex(Vertex vertex)
    {
        if (vertex >= this -> vertexCount)
        {
            throw std::runtime_error("getVertex: vertex out of range");
        }
        return this -> vertices[vertex];
    }
    template <typename E>
    void Graph<E>::setVertex(Vertex vertex, E value)
    {
        if (vertex >= this -> vertexCount)
        {
            throw std::runtime_error("setVertex: vertex out of range");
        }
        this -> vertices[vertex] = value;
    }
}