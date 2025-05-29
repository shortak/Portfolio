#include <stdlib.h>
#include <time.h>
#include <random>
#include <iomanip>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

template <typename T> //Allow the graph to be bool if user chooses to generate an unweighted graph
class Graph
{
private:
    T** graph;
    const int size;
    const int density;
    int attempts = 0;
    bool isConnected = false;
    double* distances;

    int FindMinPath(double* distance, bool* close, const int size) //Finds the smallest path in the open set (queue) and returns the next node in the queue
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

    inline double RandomDouble(double min, double max) //Generate a random double number for edge placement
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(1.0, 10.0);

        return dis(gen);
    }
    
    inline double Average() //Find the average of any set of values in an array (used for shortest path calculation)
    {
        double sum = 0;
        for(int i = 0; i < size; ++i){sum += distances[i];}

        return sum/size;
    }
    
    bool IsConnected() //Checks for graph connectivity 
    {
        int old_size = 0, c_size = 0;
        bool* close = new bool[size];
        bool* open = new bool[size];
        for(int i = 0; i < size; ++i) open[i] = close[i] = false;
        open[0] = true;

        while(c_size < size) //Analyze graph until the closed set (dequeue) is as big as the size of the graph
        {
            for(int i = 0; i < size; ++i)
            {
                old_size = c_size;
                if(open[i] && !close[i]) //If we have a new open node to consider
                {
                    close[i] = true; c_size++; // Put the current node into the closed set (dequeue)
                    for(int j = 0; j < size; ++j) open[j] = open[j] || graph[i][j]; // Put all connecting nodes in the open set
                    if(c_size == size) 
                    {
                        delete[] open;
                        delete[] close;
                        return true;
                    }
                }
                if(old_size == c_size) //If we cannot add any more nodes to the closed set and closed set does not contain all nodes
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
    Graph(const int size, const int density) : size(size), density(density) //Initializer list constructor for a graph
    {
        while(!isConnected) //Repeat graph creation until the generated graph is connected
        {
            attempts++;
            graph = new T* [size];
            distances = new double [size];
            for(int i = 0; i < size; ++i) graph[i] = new T[size];
            for(int i = 0; i < size; ++i)
            {
                for(int j = 0; j < size; ++j) //Randomly place edges based on density
                {
                    if(i == j)graph[i][j] = false;
                    else graph[i][j] = graph[j][i] = RandomDouble(1.0, 10.0) * static_cast<double>((rand() % 100) < density);
                }
            }
            isConnected = IsConnected();
            if(!isConnected) //Deconstruct to prepare for the next generation
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

    T Edge(int x, int y) //If there is an edge, return the edge b/n x and y
    {
        if(graph[x][y]) return graph[x][y];
        else 
        {
            cout << "No edge between nodes " << x << " and " << y << endl;
            return graph[x][y];
        }
    }

    bool Adjacent(int x, int y) //Check if there exists an edge b/n x and y
    {
        if(graph[x][y]) return true;
        else return false;
    }

    void Neighbors(int x) //Find all nodes connected to x
    {
        cout << "Listing all nodes connected to " << x << "..." << endl;
        for(int i = 0; i < size; ++i)
        {
            if(graph[x][i]) cout << i << " ";
        }
        cout << endl;
    }

    void Add(int x, int y){graph[x][y] = graph[y][x] = 1;} //Add an edge between x and y
    
    void AddWeight(int x, int y, double weight){graph[x][y] = graph[y][x] = weight;} //Place a weighted edge between x and y

    void Delete(int x, int y){graph[x][y] = graph[y][x] = 0;} //Delete edge
    
    void SetEdgeValue(int x, int y, T value){graph[x][y] = graph[x][y] = value;} //Set an edge between x and y

    double Dijkstras(const int target) //Use Dijkstra's shortest path alg to find the shortest path from node 0 to target node
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

    double AvgShortestPath() //Iterate through each node to find the shortest path to that node, then average it out
    {
        for(int i = 0; i < size; ++i)
        {
            distances[i] = Dijkstras(i);
        }
        return Average();
    }

    void ExportGraph() //Export graph to csv
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

    void ExportDistances() //Export shortest distance to all nodes to csv
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

    ~Graph() //Destroy object
    {
        for(int i = 0; i < size; ++i) delete[] graph[i];
        delete[] graph;
    }
};


bool GetYesNo(const string& prompt) //Ask user for a yes or no input
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

int GetBoundedInt(const string& prompt, int min, int max) //Ask user for an integer between two integers
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