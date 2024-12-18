#pragma once
#include "SetOnBinaryTree.h"
#include "Edge.h"

template <typename T>
class Edge;

template <typename T>
class Vertex
{
private:
    T id;
    SetOnBinaryTree<Edge<T>*> edges;

public:
    Vertex(T id) : id(id) {}

    T getId() const
    {
        return id;
    }

    void addEdge(Edge<T>* edge)
    {
        edges.Insert(edge);
    }

    void removeEdge(Edge<T>* edge)
    {
        edges.Delete(edge);

    }

    int GetCountOfEdges()
    {
        return edges.GetLength();
    }

    SetOnBinaryTree<Edge<T>*> getEdges() const
    {
        return edges;
    }
};