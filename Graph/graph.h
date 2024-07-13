#pragma once
#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

namespace DataStructure::graph
{
    using Vertex = size_t;

    template <typename E>
    class Graph
    {
    public:
        Graph(size_t vertexCount) : VertexCount(vertexCount)
        {
            Vertices.resize(vertexCount);
        }
        virtual void addEdge(Vertex from, Vertex to, int weight = 1) = 0;
        virtual void removeEdge(Vertex from, Vertex to) = 0;
        virtual void printGraph() = 0;
        virtual int getEdge(Vertex from, Vertex to) = 0;
        virtual ~Graph() = default;

    public:
        void setVertex(Vertex vertex, E value);
        E getVertex(Vertex vertex);
        
    protected:
        size_t VertexCount;
        std::vector<E> Vertices;
    };

    template <typename E>
    E Graph<E>::getVertex(Vertex vertex)
    {
        if (vertex >= this -> VertexCount)
        {
            throw std::runtime_error("getVertex: vertex out of range");
        }
        return this -> Vertices[vertex];
    }
    template <typename E>
    void Graph<E>::setVertex(Vertex vertex, E value)
    {
        if (vertex >= this -> VertexCount)
        {
            throw std::runtime_error("setVertex: vertex out of range");
        }
        this -> Vertices[vertex] = value;
    }
}