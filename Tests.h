#pragma once
#include <assert.h>
#include "DirectGraph.h"
#include "UndirectGraph.h"

void Test_of_AddVertex_DirectedGraph() 
{
    DirectedGraph<int> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);

    assert(graph.GetVertexCount() == 3);
    assert(graph.GetVertex(1)->getId() == 1);
    assert(graph.GetVertex(2)->getId() == 2);
    assert(graph.GetVertex(3)->getId() == 3);
}

void Test_of_AddEdge_DirectedGraph() 
{
    DirectedGraph<int> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addEdge(1, 2, 5.0f);
    graph.addEdge(2, 3, 2.0f);

    auto edges1 = graph.GetVertex(1)->getEdges();
    auto edges2 = graph.GetVertex(2)->getEdges();

    assert(edges1.GetLength() == 1);
    assert(edges1.Get(0)->getTo()->getId() == 2);
    assert(edges1.Get(0)->getWeight() == 5.0f);

    assert(edges2.GetLength() == 1);
    assert(edges2.Get(0)->getTo()->getId() == 3);
    assert(edges2.Get(0)->getWeight() == 2.0f);
}

void Test_of_FindShortestPath_DirectedGraph() 
{
    DirectedGraph<int> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addVertex(4);
    graph.addEdge(1, 2, 1.0f);
    graph.addEdge(2, 3, 2.0f);
    graph.addEdge(3, 4, 1.0f);
    graph.addEdge(1, 4, 5.0f);

    auto path = graph.FindShortestPath(1, 4);
    assert(path.GetLength() == 4);
    assert(path.Get(0) == 1);
    assert(path.Get(1) == 2);
    assert(path.Get(2) == 3);
    assert(path.Get(3) == 4);
}

void Test_of_AddVertex_UndirectedGraph() 
{
    UndirectedGraph<int> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);

    assert(graph.GetVertexCount() == 3);
    assert(graph.GetVertex(1)->getId() == 1);
    assert(graph.GetVertex(2)->getId() == 2);
    assert(graph.GetVertex(3)->getId() == 3);
}

void Test_of_AddEdge_UndirectedGraph() 
{
    UndirectedGraph<int> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addEdge(1, 2, 3.0f);
    graph.addEdge(2, 3, 4.0f);

    auto edges1 = graph.GetVertex(1)->getEdges();
    auto edges2 = graph.GetVertex(2)->getEdges();
    auto edges3 = graph.GetVertex(3)->getEdges();

    assert(edges1.GetLength() == 1);
    assert(edges1.Get(0)->getTo()->getId() == 2);
    assert(edges1.Get(0)->getWeight() == 3.0f);

    assert(edges2.GetLength() == 2);
    assert(edges2.Get(0)->getTo()->getId() == 1 || edges2.Get(1)->getTo()->getId() == 1);
    assert(edges2.Get(0)->getTo()->getId() == 3 || edges2.Get(1)->getTo()->getId() == 3);

    assert(edges3.GetLength() == 1);
    assert(edges3.Get(0)->getTo()->getId() == 2);
    assert(edges3.Get(0)->getWeight() == 4.0f);
}

void Test_of_FindShortestPath_UndirectedGraph() 
{
    UndirectedGraph<int> graph;
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addVertex(4);
    graph.addEdge(1, 2, 1.0f);
    graph.addEdge(2, 3, 2.0f);
    graph.addEdge(3, 4, 1.0f);
    graph.addEdge(1, 4, 5.0f);

    auto path = graph.FindShortestPath(1, 4);
    assert(path.GetLength() == 4);
    assert(path.Get(0) == 1);
    assert(path.Get(1) == 2);
    assert(path.Get(2) == 3);
    assert(path.Get(3) == 4);
}

void RunAllTests()
{
    Test_of_AddVertex_DirectedGraph();
    Test_of_AddEdge_DirectedGraph();
    Test_of_FindShortestPath_DirectedGraph();

    Test_of_AddVertex_UndirectedGraph();
    Test_of_AddEdge_UndirectedGraph();
    Test_of_FindShortestPath_UndirectedGraph();
}