#pragma once
#include "graph.h"
#include <forward_list>
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
        virtual int getEdge(Vertex from, Vertex to);
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
}