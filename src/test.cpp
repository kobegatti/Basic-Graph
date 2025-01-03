#include "../header/basicGraph.hpp"
#include <assert.h>
#include <fstream>
#include <iostream>

#define PATH2 "data/graph2.json"
#define PATH4 "data/graph4.json"
#define PATH5 "data/graph5.json"
#define PATH5_COPY "data/graph5-copy.json"
#define PATH6 "data/graph6.json"

// File Read
void testFileRead(BasicGraph* g, std::string path, BasicGraph* expected)
{
    g->jsonToGraph(path);
    assert(*g==*expected);

    g->clearGraph();
    expected->clearGraph();
}

// File Write
void testFileWrite(BasicGraph* g, std::string path, BasicGraph* expected)
{
    g->graphToJson(path);
    expected->jsonToGraph(path);
    assert(*g==*expected);

    g->clearGraph();
    expected->clearGraph();
}

// Add/Remove Vertices and Edges
void testAddRemove1(BasicGraph* g, BasicGraph* expected)
{
    assert(*g==*expected);

    g->addVertex(1);
    assert(!(*g==*expected));

    g->removeVertex(1);
    assert(*g==*expected);

    g->clearGraph();
    expected->clearGraph();
}

void testAddRemove2(BasicGraph* g, BasicGraph* expected)
{
    assert(*g==*expected);

    expected->addVertex(1);

    g->addEdge(1, 2);
    g->addVertex(2);
    assert(!(*g==*expected));

    g->removeVertex(2);
    assert(*g==*expected);

    g->clearGraph();
    expected->clearGraph();
}

void testAddRemove3(BasicGraph* g, BasicGraph* expected)
{
    assert(*g==*expected);

    expected->addVertex(3);
    expected->addVertex(5);

    g->addEdge(3, 1);
    g->addVertex(5);
    assert(!(*g==*expected));

    g->removeVertex(1);
    assert(*g==*expected);

    g->clearGraph();
    expected->clearGraph();
}

void testAddRemove4(BasicGraph* g, BasicGraph* expected)
{
    assert(*g==*expected);

    expected->addEdge(1, 2);
    expected->addVertex(3);;
    expected->addVertex(5);

    g->addEdge(1, 2);
    g->addEdge(3, 4);
    g->addEdge(3, 5);
    assert(!(*g==*expected));

    g->removeEdge(3, 5);
    g->removeVertex(4);
    assert(*g==*expected);

    g->clearGraph();
    expected->clearGraph();
}

void testAddRemove5(BasicGraph* g, BasicGraph* expected)
{
    assert(*g==*expected);

    expected->addEdge(1, 2);
    expected->addEdge(1, 3);
    expected->addEdge(2, 3);
    expected->addEdge(3, 2);
    expected->addVertex(4);
    expected->addEdge(4, 2);
    expected->addEdge(4, 3);

    g->addEdge(1, 2);
    g->addEdge(1, 3);
    g->addEdge(2, 3);
    g->addEdge(3, 2);
    g->addVertex(4);
    g->addEdge(4, 2);
    g->addEdge(4, 3);
    g->addEdge(1, 4);
    assert(!(*g==*expected));

    g->removeEdge(1, 4);
    assert(*g==*expected);

    g->clearGraph();
    expected->clearGraph();
}

// BFS
bool compareMaps(const std::unordered_map<int, int>& m1, 
                    const std::unordered_map<int, int>& m2)
{
    if (m1.size() != m2.size()) { return false; }

    for (const auto& pair : m1)
    {
        if (m2.find(pair.first) == m2.end() || m2.at(pair.first) != pair.second)
        {
            return false;
        }
    }

    return true;
}
void testBFS(BasicGraph* graph, int root, std::unordered_map<int, int>& expected)
{
    std::unordered_map<int, int> actual = (*graph).BFS(root);

    assert(compareMaps(actual, expected));
    graph->clearGraph();
}

int main()
{
    BasicGraph graph, expected;

    std::cout << "Test File Read\n";
    expected.addEdge(1, 2);
    expected.addEdge(2, 3);
    expected.addEdge(3, 1);
    testFileRead(&graph, PATH4, &expected);

    expected.addVertex(1);
    testFileRead(&graph, PATH5, &expected);

    std::cout << "Test File Write\n";
    graph.addVertex(1);
    testFileWrite(&graph, PATH5_COPY, &expected);

    std::cout << "Test Add/Remove\n";
    testAddRemove1(&graph, &expected);
    testAddRemove2(&graph, &expected);
    testAddRemove3(&graph, &expected);
    testAddRemove4(&graph, &expected);
    testAddRemove5(&graph, &expected);

    std::cout << "Test BFS\n";
    graph.jsonToGraph(PATH4);
    std::unordered_map<int, int> expectedBFS1 = {{1, 0}, {2, 1}, {3, 2}};
    testBFS(&graph, 1, expectedBFS1);

    graph.jsonToGraph(PATH6);
    std::unordered_map<int, int> expectedBFS2 = {{1, 0}, {2, 1}, {3, 1}};
    testBFS(&graph, 1, expectedBFS2);

    graph.jsonToGraph(PATH2);
    std::unordered_map<int, int> expectedBFS3 = {{8, 0},
                                                {0, INT_MAX},
                                                {1, INT_MAX},
                                                {2, INT_MAX},
                                                {3, INT_MAX},
                                                {4, INT_MAX},
                                                {5, INT_MAX},
                                                {6, INT_MAX},
                                                {7, INT_MAX}};
    testBFS(&graph, 8, expectedBFS3);

    graph.jsonToGraph(PATH2);
    std::unordered_map<int, int> expectedBFS4 = {{8, INT_MAX},
                                                {0, 2},
                                                {1, 1},
                                                {2, 1},
                                                {3, 0},
                                                {4, 1},
                                                {5, 1},
                                                {6, 2},
                                                {7, 2}};
    testBFS(&graph, 3, expectedBFS4);

    return 0;
}