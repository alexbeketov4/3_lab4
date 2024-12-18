#pragma once
#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "DictionaryOnSequence.h"

template <typename T>
class UndirectedGraph : public Graph<T>
{
private:
    DictionaryOnSequence<T, Vertex<T>*> vertices;

public:
    UndirectedGraph() : vertices() {}

    void addVertex(T id) override
    {
        if (!this->vertices.ContainsKey(id))
        {
            this->vertices.Add(id, new Vertex<T>(id));
        }
    }

    void addEdge(T fromId, T toId, float weight) override
    {
        Vertex<T>* from = GetVertex(fromId);
        Vertex<T>* to = GetVertex(toId);
        Edge<T>* edge1 = new Edge<T>(from, to, weight);
        Edge<T>* edge2 = new Edge<T>(to, from, weight);
        from->addEdge(edge1);
        to->addEdge(edge2);
    }

    int GetVertexCount() const override
    {
        return vertices.GetCount();
    }

    Vertex<T>* GetVertex(T id) const override
    {
        if (!this->vertices.ContainsKey(id))
        {
            throw "Vertex not found";
        }
        return this->vertices.Get(id);
    }
};