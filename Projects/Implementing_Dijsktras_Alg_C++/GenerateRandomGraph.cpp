#include <stdlib.h>
#include <time.h>
#include <random>
#include <string.h>
#include <iostream>

using namespace std;

bool is_connected(bool* graph[], int size)
{
    int old_size = 0, c_size = 0;
    bool* close = new bool[size];
    bool* open = new bool[size];
    for(int i = 0; i < size; ++i)
    {
        open[i] = close[i] = false;
        open[0] = true;
    }
}

int main()
{
    // Create Adjacency Matrix
    bool** graph;
    srand(time(0)); // seed rand()
    graph = new bool* [size]; // Create an array of pointers that point to booleans

    for(int i = 0; i < size; ++i)
    {
        graph[i] = new bool[size];
    }
    
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            if(i == j)graph[i][j] = false;
            else graph[i][j] = graph[j][i] = (rand() % 100 < .19);
        }
    }

    // Cleanup
    for(int i = 0; i < size; ++i)
    {
        delete[] graph[i];
    }
    delete[] graph;

    return 0;
}