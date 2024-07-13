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
        virtual vector<Vertex> getAdjacentVertices(Vertex vertex);

        virtual vector<int> Dijkstra(Vertex start) override;
        vector<vector<int>> floyd();

        ~GraphMatrix() = default;

    private:    
        std::vector<std::vector<int>> adjMatrix;
    };  

    template <typename E>
    GraphMatrix<E>::GraphMatrix(int vertexCount_): Graph<E>(vertexCount_)
    {
        adjMatrix.resize(this -> VertexCount, vector<int>(this -> VertexCount, INF));
        for (Vertex i = 0; i < this -> VertexCount; i++)
        {
            adjMatrix[i][i] = 0;
        }
    }
    template <typename E>
    void GraphMatrix<E>::addEdge(Vertex from, Vertex to, int weight)
    {
        if (from == to) return;

        if (from >= this -> VertexCount || to >= this -> VertexCount)
        {
            throw std::runtime_error("addEdge: vertex out of range");
        }
        adjMatrix[from][to] = std::min(weight, adjMatrix[from][to]);   
    }

    template <typename E>
    void GraphMatrix<E>::removeEdge(Vertex from, Vertex to)
    {
        if (from >= this -> VertexCount || to >= this -> VertexCount)
        {
            throw std::runtime_error("removeEdge: vertex out of range");
        }
        adjMatrix[from][to] = INF;
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
    
    vector<Vertex> GraphMatrix<E>::getAdjacentVertices(Vertex vertex)
    {

        if (vertex >= this -> VertexCount)
        {
            throw std::runtime_error("getAdjacentVertices: vertex out of range");
        }
        vector<Vertex> ans;
        for (Vertex i = 0; i < this -> VertexCount; i++)
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
        for (Vertex i = 0; i < this -> VertexCount; i++)
        {
            std::cout << i << ": ";
            for (size_t j = 0; j < this -> VertexCount; j++)
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
        vector<bool> visited(this -> VertexCount, false);
        vector<int> ans(this -> VertexCount, INF);

        ans[start] = 0;

        for (Vertex i = 0; i < this -> VertexCount; i ++)
        {
            Vertex nearNode = INF;
            for (Vertex j = 0; j < this -> VertexCount; j ++)
            {
                if (!visited[j] && (nearNode == INF || ans[j] < ans[nearNode]))
                {
                    nearNode = j;
                }
            }

            visited[nearNode] = true;
            for (Vertex j = 0; j < this -> VertexCount; j ++)
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

        for (Vertex k = 0; k < this -> VertexCount; ++ k)
        {
            for (Vertex i = 0; i < this -> VertexCount; ++ i)
            {
                for (Vertex j = 0; j < this -> VertexCount; ++ j)
                {
                    ans[i][j] = std::min(ans[i][j], ans[i][k] + ans[k][j]);
                }
            }
        }
        return ans;
    }
}