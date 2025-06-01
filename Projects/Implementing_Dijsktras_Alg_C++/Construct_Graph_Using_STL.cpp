#include <stdlib.h>
#include <time.h>
#include <random>
#include <iomanip>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

template<typename T>
T** GenerateGraph(const int size, const int density)
{
    vector<vector<T>> Graph(size, vector<double>(size, 0.0));
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            if(i == j)graph[i][j] = false;
            else graph[i][j] = graph[j][i] = RandomDouble(1.0, 10.0) * static_cast<double>((rand() % 100) < density);
        }
    }

    return graph;
}

template<typename T>
T** GenerateGraph(const int size, const int density)
{
    vector<vector<T>> Graph(size, vector<double>(size, 0.0));
    for(auto nodeSelect = Graph.begin(); nodeSelect != Graph.begin(); ++nodeSelect)
    {
        int i = distance(Graph.begin(), nodeSelect);
        for(auto nodeIter = nodeSelect->begin(); nodeIter != nodeSelect->end(); ++nodeIter)
        {
            int j = distance(nodeSelect->begin(), nodeIter);
            if (i != j) *nodeIter = RandomDouble(1.0, 10.0) * static_cast<T>((rand() % 100) < density);
        }
    }
}