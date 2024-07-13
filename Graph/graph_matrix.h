#pragma once
#include "graph.h"

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

        ~GraphMatrix() = default;

    private:    
        std::vector<std::vector<int>> adjMatrix;
    };  

    template <typename E>
    GraphMatrix<E>::GraphMatrix(int vertexCount_): Graph<E>(vertexCount_)
    {
        adjMatrix.resize(this -> VertexCount, std::vector<int>(this -> VertexCount));
    }
    template <typename E>
    void GraphMatrix<E>::addEdge(Vertex from, Vertex to, int weight)
    {
        if (from >= this -> VertexCount || to >= this -> VertexCount)
        {
            throw std::runtime_error("addEdge: vertex out of range");
        }
        adjMatrix[from][to] = weight;   
    }

    template <typename E>
    void GraphMatrix<E>::removeEdge(Vertex from, Vertex to)
    {
        if (from >= this -> VertexCount || to >= this -> VertexCount)
        {
            throw std::runtime_error("removeEdge: vertex out of range");
        }
        adjMatrix[from][to] = 0;
    }

    template <typename E>
    int GraphMatrix<E>::getEdge(Vertex from, Vertex to)
    {
        if (from >= this -> VertexCount || to >= this -> VertexCount)
        {
            throw std::runtime_error("getEdge: vertex out of range");
        }
        return adjMatrix[from][to];
    }

    template <typename E>
    
    void GraphMatrix<E>::printGraph()
    {
        for (Vertex i = 0; i < this -> VertexCount; i++)
        {
            std::cout << i << ": ";
            for (size_t j = 0; j < this -> VertexCount; j++)
            {
                if (adjMatrix[i][j])
                {
                    std::printf("(%lu, %d) ", j, adjMatrix[i][j]);
                }
            }
            std::cout << std::endl;
        }
    }
}