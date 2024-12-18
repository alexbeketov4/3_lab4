#pragma once
#include "Vertex.h"

template<class T>
class Graph
{
public:
    virtual void addVertex(T id) = 0;

    virtual void addEdge(T fromId, T toId, float weight) = 0;

    virtual int GetVertexCount() const = 0;

    virtual Vertex<T>* GetVertex(int id) const = 0;

    //virtual void removeVertex(T id) = 0;

    //virtual void removeEdge(T fromId, T toId) = 0;

    //virtual SetOnBinaryTree<Edge<T>*> getNeighbors(T id) const = 0;
};