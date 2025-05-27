// Online C++ compiler to run C++ program online
#include <iostream>
#include <random>
using namespace std;

//THIS WORKS... EXCEPT IN CASES WHERE THERE ARE TWO SAME PATHS -> FIXED

// STILL NEED TO FIX FOR THE CASE WHERE THE SHORTEST IMMEDIATE PATH ISN'T CORRECT -> FIXED

#include <iostream>
#include <random>
using namespace std;

int FindMinPath(double* open, double* close, const int size)
{
    double temp = __DBL_MAX__;
    int iterator = 0;
    int node;
    while (iterator != size)
    {
        if (open[iterator] < temp && close[iterator] == 0 && open[iterator] != 0) 
        {
            temp = open[iterator];
            node = iterator;
        }
        iterator++;
    }

    return node;
}

template<typename T>
double Dijkstra(T** graph, const int size, int target)
{
    double* distance = new double[size];
    double* open = new double[size];
    double* close = new double[size];
    for(int i = 0; i < size; ++i) 
    {
        open[i] = close[i] = 0;
        distance[i] = __DBL_MAX__;
    }

    open[0] = 1; 
    distance[0] = 0;
    bool pathFound= false;
    bool foundEarly = false;
    
    if(target == 0) return 0;
    int count=0;
    int loopcount = 0;

    int node = 0; //Source node
    while(!pathFound)
    {
        if(open[node] > 0 && close[node] == 0)
        {   
            close[node] = 1;
            for(int i = 0; i < size; ++i)
            {
                if(graph[node][i] > 0 && close[i] == 0) 
                {

                    open[i] =  graph[node][i]; //index is the node, actual value is distance to that node from node i
                    if(i == target && !foundEarly)
                    {
                        distance[i] = distance[node] + graph[node][i];
                        foundEarly = true;
                    }
                }
            }   
            int prevNode = node;
                node = FindMinPath(open, close, size);  
                
                if(foundEarly && ( distance[prevNode] + graph[prevNode][node]) > distance[target]) return distance[target];
                
                distance[node] = distance[prevNode] + graph[prevNode][node];

                if(distance[node] >= distance[target]) pathFound = true;
        }   
    }
    return distance[target];
}

int main() {
    // Write C++ code here
    double graphbase[5][5] = {{  0,6.4,  0,  0,  9},
                              {6.4,  0,3.6,3.7,  1},
                              {  0,3.6,  0,  0,  0},
                              {  0,3.7,  0,  0,  0},
                              {  9,  1,  0,  0,  0}};
    
    double** graph = new double* [5];
    for(int i = 0; i < 5; ++i) graph[i] = new double[5];
    for(int i = 0; i < 5; ++i)
    {
        for(int j = 0; j < 5; ++j)
        {
            graph[i][j] = graphbase[i][j];
        }
    }
    
    
    cout << Dijkstra<double>(graph, 5, 4) << endl;

    return 0;
}