#pragma once
#include "Vertex.h"

template <typename T>
class Vertex;

template <typename T>
class Edge
{
private:
    Vertex<T>* from;
    Vertex<T>* to;
    float weight;

public:
    Edge(Vertex<T>* from, Vertex<T>* to, float weight)
        : from(from), to(to), weight(weight) {}

    Vertex<T>* getFrom() const
    {
        return from ? from : nullptr;
    }

    Vertex<T>* getTo() const
    {
        return to ? to : nullptr;
    }

    float getWeight() const
    {
        return weight;
    }

    bool operator<(const Edge<T>& other) const
    {
        return this->weight < other.weight;
    }

    bool operator>(const Edge<T>& other) const
    {
        return this->weight > other.weight;
    }

    bool operator==(const Edge<T>& other) const
    {
        return this->from == other.from && this->to == other.to && this->weight == other.weight;
    }

    bool operator!=(const Edge<T>& other) const
    {
        return !(*this == other);
    }

    bool operator<=(const Edge<T>& other) const
    {
        return !(*this > other);
    }

    bool operator>=(const Edge<T>& other) const
    {
        return !(*this < other);
    }
};