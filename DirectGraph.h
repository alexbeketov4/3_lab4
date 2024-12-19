#pragma once
#include "Graph.h"
#include "DictionaryOnSequence.h"
#include "ArraySequence.h"

template <typename T>
class DirectedGraph : public Graph<T>
{
private:
    DictionaryOnSequence<T, Vertex<T>*> vertices;
public:
    DirectedGraph() : vertices() {}

    ~DirectedGraph() 
    {
        auto keys = vertices.GetKeys();
        for (int i = 0; i < keys.GetLength(); ++i) 
        {
            delete vertices.Get(keys.Get(i));
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

    DictionaryOnSequence<T, Vertex<T>*> GetVertices() const override
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

    ArraySequence<T> FindShortestPath(T startId, T endId) const override
    {
        DictionaryOnSequence<T, float> distances;
        DictionaryOnSequence<T, T> previous;

        auto keys = vertices.GetKeys();
        for (int i = 0; i < keys.GetLength(); ++i)
        {
            distances.Add(keys.Get(i), std::numeric_limits<float>::infinity());
            previous.Add(keys.Get(i), T());
        }
        distances.Remove(startId);
        distances.Add(startId, 0);

        while (distances.GetCount() > 0)
        {
            T currentId = T();
            float currentDist = std::numeric_limits<float>::infinity();

            for (int i = 0; i < distances.GetCount(); ++i)
            {
                T key = distances.GetKey(i);
                float value = distances.Get(key);
                if (value < currentDist)
                {
                    currentId = key;
                    currentDist = value;
                }
            }

            if (currentId == endId)
                break;

            distances.Remove(currentId);

            Vertex<T>* currentVertex = GetVertex(currentId);
            auto edges = currentVertex->getEdges();

            for (int i = 0; i < edges.GetLength(); ++i)
            {
                Edge<T>* edge = edges.Get(i);
                if (edge == nullptr) continue;

                T neighborId = edge->getTo()->getId();
                float weight = edge->getWeight();

                float newDist = currentDist + weight;
                if (distances.ContainsKey(neighborId) && newDist < distances.Get(neighborId))
                {
                    distances.Remove(neighborId);
                    distances.Add(neighborId, newDist);
                    previous.Remove(neighborId);
                    previous.Add(neighborId, currentId);
                }
            }
        }

        ArraySequence<T> path;
        T current = endId;
        while (current != startId)
        {
            path.Prepend(current);
            current = previous.Get(current);
        }
        path.Prepend(startId);

        return path;
    }
};