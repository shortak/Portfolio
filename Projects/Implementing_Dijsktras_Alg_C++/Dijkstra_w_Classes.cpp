#include <stdlib.h>
#include <time.h>
#include <random>
#include <iomanip>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
class Graph
{
private:
    T** graph;
    const int size;
    const int density;
    int attempts = 0;
    bool isConnected = false;
    double* distances;

    int FindMinPath(double* distance, bool* close, const int size)
    {
        double temp = __DBL_MAX__;
        int iterator = 0;
        int node;
        while (iterator != size)
        {
            if (distance[iterator] < temp && !close[iterator]) 
            {
                temp = distance[iterator];
                node = iterator;
            }
            iterator++;
        }
        return node;
    }

    inline double RandomDouble(double min, double max)
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(1.0, 10.0);

        return dis(gen);
    }
    
    inline double Average()
    {
        double sum = 0;
        for(int i = 0; i < size; ++i){sum += distances[i];}

        return sum/size;
    }
    
    bool IsConnected()
    {
        int old_size = 0, c_size = 0;
        bool* close = new bool[size];
        bool* open = new bool[size];
        for(int i = 0; i < size; ++i) open[i] = close[i] = false;
        open[0] = true;

        while(c_size < size)
        {
            for(int i = 0; i < size; ++i)
            {
                old_size = c_size;
                if(open[i] && !close[i]) // If we have a new open node to consider
                {
                    close[i] = true; c_size++; // Put the node we are exploring into the closed set
                    for(int j = 0; j < size; ++j) open[j] = open[j] || graph[i][j]; // Put all connecting nodes in the open set
                    if(c_size == size) 
                    {
                        delete[] open;
                        delete[] close;
                        return true;
                    }
                }
                if(old_size == c_size)
                {
                    delete[] open;
                    delete[] close;
                    return false;
                } 
            }
        }
        return false;
    }

public:
    Graph(const int size, const int density) : size(size), density(density)
    {
        while(!isConnected)
        {
            attempts++;
            graph = new T* [size];
            distances = new double [size];
            for(int i = 0; i < size; ++i) graph[i] = new T[size];
            for(int i = 0; i < size; ++i)
            {
                for(int j = 0; j < size; ++j)
                {
                    if(i == j)graph[i][j] = false;
                    else graph[i][j] = graph[j][i] = RandomDouble(1.0, 10.0) * static_cast<double>((rand() % 100) < density);
                }
            }
            isConnected = IsConnected();
            if(!isConnected)
            {
                for(int i = 0; i < size; ++i) delete[] graph[i];
                delete[] graph;
                delete[] distances;
            }
        }
        
    }

    int GetAttempts(){return attempts;}
    int GetCxnStatus(){return isConnected;}
    int GetDensity(){return density;}

    double Dijkstras(const int target)
    {
        double* distance = new double[size];
        bool* open = new bool[size];
        bool* close = new bool[size];
        for(int i = 0; i < size; ++i) 
        {
            open[i] = close[i] = false;
            distance[i] = __DBL_MAX__;
        }

        open[0] = true; 
        distance[0] = 0;
        bool pathFound= false;
        
        if(target == 0) return 0;
        int count=0;
        int loopcount = 0;

        int node = 0; //Source node
        while(!pathFound)
        {
            if(open[node] && !close[node])
            {   
                close[node] = true;
                for(int i = 0; i < size; ++i)
                {
                    if(graph[node][i] && !close[i]) 
                    {
                        if(!open[i]) 
                        {
                            open[i] = true;
                            distance[i] = distance[node] + graph[node][i];
                        }
                        else if(distance[i] > distance[node] + graph[node][i]) distance[i] = distance[node] + graph[node][i];
                    }
                }   
                int prevNode = node;
                node = FindMinPath(distance, close, size);
                if(distance[node] >= distance[target]) pathFound = true;
            }   
        }
        return distance[target];
    }

    double AvgShortestPath()
    {
        for(int i = 0; i < size; ++i)
        {
            distances[i] = Dijkstras(i);
        }
        return Average();
    }

    void ExportGraph()
    {
        ofstream file("graph.csv");
        if (file.is_open())
        {
            for(int i = 0; i < size; ++i)
            {
                for (int j = 0; j < size; ++j)
                {
                    file << graph[i][j];
                    
                    if(j != size-1) file << ",";
                    if(j == size-1) file << endl;
                }
            }
        }
        file.close();
        cout << "Graph written to graph.csv!" << endl;
    }

    void ExportDistances()
    {
        ofstream file("distances.csv");
        if (file.is_open())
        {
            for(int i = 0; i < size; ++i)
            {
                file << distances[i];
                if(i != size-1) file << ",";
            }
        }
    }

    ~Graph()
    {
        for(int i = 0; i < size; ++i) delete[] graph[i];
        delete[] graph;
    }
};

bool GetYesNo(const string& prompt)
{
    bool input;
    while(true)
    {
        cout << prompt << " Yes(1) No(0)" << endl;
        if(cin >> input)
        {
            if(input) return true;
            if(!input) return false;
        }
        else
        {
            cout << "Invalid Input. Please enter 1 or 0." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

int GetBoundedInt(const string& prompt, int min, int max)
{
    int input;
    while(true)
    {
        cout << prompt;
        if(cin >> input && input >= min && input <= max)
        {
            return input;
        }
        cout << "Invalid input. Please enter an integer between " << min << " and " << max << "." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

int main()
{
    int size = GetBoundedInt("Size of graph (enter integer > 1): ", 2, 1000);
    int density = GetBoundedInt("Density of graph (0-100): ", 0, 100);
    bool isWeighted = GetYesNo("Weighted graph?");

    if(isWeighted)
    {
        cout << "Generating weighted graph with " << size << " nodes and density of " << density 
        << "..." << endl;
        Graph<double> g(size, density);
        if(g.GetCxnStatus())
        {
            cout << "Graph generated in " << g.GetAttempts() << " attempt(s)" << endl;
            if(GetYesNo("Export graph to graph.csv?")) g.ExportGraph();
            if(GetYesNo("Continue to average shortest path calculation?"))
            {
                cout << "Average shortest path: " <<g.AvgShortestPath() << endl;
                if(GetYesNo("Export distances to distances.csv?")) g.ExportDistances();
            }
        }
    }
    else
    {
        cout << "Generating unweighted graph with " << size << " nodes and density of " << density
        << "..." << endl;
        Graph<bool> g(size, density);
        if(g.GetCxnStatus())
        {
            cout << "Graph generated in " << g.GetAttempts() << " attempt(s)" << endl;
            if(GetYesNo("Export graph to graph.csv?")) g.ExportGraph();
            if(GetYesNo("Continue to average shortest path calculation?")) 
            {
                cout << "Average shortest path: " <<g.AvgShortestPath() << endl;
                if(GetYesNo("Export distances to distances.csv?")) g.ExportDistances();
            }
        }
    }
    return 0;
}