#pragma once
#include "Vertex.h"
#include "DictionaryOnSequence.h"
#include "ArraySequence.h"

template<class T>
class Graph
{
public:
    virtual void addVertex(T id) = 0;

    virtual void addEdge(T fromId, T toId, float weight) = 0;

    virtual int GetVertexCount() const = 0;

    virtual Vertex<T>* GetVertex(int id) const = 0;

    virtual DictionaryOnSequence<T, Vertex<T>*> GetVertices() const = 0;

    virtual ArraySequence<T> FindShortestPath(T startId, T endId) const = 0;
};