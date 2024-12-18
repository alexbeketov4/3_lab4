#pragma once
#include "Graph.h"
#include "DictionaryOnSequence.h"

template <typename T>
class DirectedGraph : public Graph<T>
{
private:
    DictionaryOnSequence<T, Vertex<T>*> vertices;
public:
    DirectedGraph() : vertices() {}

    /*~DirectedGraph() 
    {
        auto keys = vertices.GetKeys();
        for (int i = 0; i < keys.GetLength(); ++i) 
        {
            delete vertices.Get(keys.Get(i));
        }
    }*/
    ~DirectedGraph()
    {
        for (int i = 0; i < vertices.GetCount(); ++i)
        {
            delete vertices.Get(i + 1);
        }
    }

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
        Edge<T>* edge = new Edge<T>(from, to, weight);
        from->addEdge(edge);
    }

    int GetVertexCount() const override
    {
        return vertices.GetCount();
    }

    DictionaryOnSequence<T, Vertex<T>*> GetVertices()
    {
        return vertices;
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