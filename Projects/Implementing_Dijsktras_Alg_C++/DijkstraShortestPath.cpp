#include <stdlib.h>
#include <time.h>
#include <random>
#include <iomanip>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
bool IsConnected(T** graph, int size)
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
}

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


template<typename T>
double Dijkstra(T** graph, const int size, int target)
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

template <typename T>
inline void ExportGraph(T** graph, const int size)
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
        cout << "Graph written to graph.csv" << endl;
}

inline void ExportDistances(double* distances, const int size)
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

inline double RandomDouble(double min, double max)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(1.0, 10.0);

    return dis(gen);
}

template<typename T>
T** GenerateGraph(const int size, const int density)
{
    T** graph = new T* [size]; // Create an array of pointers that point to booleans
    for(int i = 0; i < size; ++i) graph[i] = new T[size];
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

inline double Average(const double* distances, const int size)
{
    double sum = 0;
    for(int i = 0; i < size; ++i){sum += distances[i];}

    return sum/size;
}


int main()
{
    srand(time(0)); // seed rand()

    bool inputStatus;

    unsigned int userInput;
    do
    {
        inputStatus = true;
        cout << "Size of graph (please enter a positive integer greater than 1)?" << endl;
        if(!(cin >> userInput) || userInput <= 1)
        {
            cout << "Invalid Input, please enter a positive integer greater than 1" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            inputStatus = false;
        }
    }while(!inputStatus);

    const int size = userInput;

    do
    {
        inputStatus = true;
        cout << "Density of Graph? (1 to 100)" << endl;
        if(!(cin >> userInput) || userInput <= 0 || userInput >= 100)
        {
            cout << "Invalid Input, please enter number between 0 and 100" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            inputStatus = false;
        }
    }while(!inputStatus);

    const int density = userInput;

    do
    {
        bool graphType; 
        cout << "Weighted (1) or Unweighted (0)?" << endl;
        cin >> graphType;

        if(graphType)
        {
            cout << "Generating a weighted graph with " << size << " nodes with a density of " << density << "..." << endl;
            inputStatus = true;
            bool isConnected;
            int attempts = 0;
            do
            {
                attempts++;
                cout << "Attempts: ";
                cout << attempts << "\r";
                double** graph = GenerateGraph<double>(size, density);
                isConnected = IsConnected<double>(graph, size);
                if(isConnected)
                {
                    cout << endl << "Graph generated!" << endl;
                    do
                    {
                        cout << "Export adjacency matrix? Yes(1) No(0)" << endl;
                        cin >> userInput;
                        if(userInput == 1) ExportGraph<double>(graph, size);
                        else if(userInput == 0) ;
                        else 
                        {   
                            cout << "Invalid Input" << endl;
                            cin.clear();
                            cin.ignore(10000, '\n');
                            inputStatus = false;
                        }
                        do
                        {
                            cout << "Continue with shortest path calculation? Yes(1) No(0)" << endl;
                            cin >> userInput;
                            if (userInput == 1)
                            {
                                double* distances = new double[size];
                                for(int i = 0; i < size; ++i)
                                {
                                    distances[i] = Dijkstra<double>(graph, size, i);
                                    cout << "Path to node " << i << " found..." << endl;
                                }
                
                                cout << "Average shorest path: " << Average(distances, size) << endl;
                                do
                                {
                                    cout << "Export distances to all nodes? Yes(1) No(0)" << endl;
                                    cin >> userInput;
                                    if(userInput == 1) 
                                    {
                                        ExportDistances(distances, size);
                                        cout << "Exported to distances.csv!" << endl;
                                    }
                                    else if(userInput == 0){}
                                    else
                                    {
                                        cout << "Invalid Input" << endl;
                                        cin.clear();
                                        cin.ignore(10000, '\n');
                                        inputStatus = false;
                                    }

                                } while (!inputStatus);
                            }
                            else if(userInput == 0){}
                            else
                            {
                                cout << "Invalid Input" << endl;
                                cin.clear();
                                cin.ignore(10000, '\n');
                                inputStatus = false;
                            }
                        } while(!inputStatus);

                    } while (!inputStatus);
                }
                else
                {
                    for(int i = 0; i < size; ++i)
                    {
                        delete[] graph[i];
                    }
                    delete[] graph;
                }
            }while (!isConnected);

           
        }
        else if(!graphType)
        {
            cout << "Generating an unweighted graph with " << size << " nodes with a density of " << density << "..." << endl;
            inputStatus = true;
            bool isConnected;
            int attempts = 0;
            do
            {
                attempts++;
                cout << "Attempts: " << attempts << "\r";
                bool** graph = GenerateGraph<bool>(size, density);
                isConnected = IsConnected<bool>(graph, size);
                if(isConnected)
                {
                    cout << endl << "Graph generated!" << endl;
                    do
                    {
                        cout << "Export adjacency matrix? Yes(1) No(0)" << endl;
                        cin >> userInput;
                        if(userInput == 1) ExportGraph<bool>(graph, size);
                        else if(userInput == 0){}
                        else 
                        {   
                            cout << "Invalid Input" << endl;
                            cin.clear();
                            cin.ignore(10000, '\n');
                            inputStatus = false;
                        }
                        do
                        {
                            cout << "Continue with shortest path calculation? Yes(1) No(0)" << endl;
                            if (userInput == 1)
                            {
                                double* distances = new double[size];
                                for(int i = 0; i < size; ++i)
                                {
                                    distances[i] = Dijkstra<bool>(graph, size, i);
                                }
                
                                cout << "Average shorest path" << Average(distances, size) << endl;
                                do
                                {
                                    cout << "Export distances to all nodes? Yes(1) No(0)" << endl;
                                    cin >> userInput;
                                    if(userInput == 1) 
                                    {
                                        ExportDistances(distances, size);
                                        cout << "Exported to distances.csv!" << endl;
                                    }
                                    else if(userInput == 0){}
                                    else
                                    {
                                        cout << "Invalid Input" << endl;
                                        cin.clear();
                                        cin.ignore(10000, '\n');
                                        inputStatus = false;
                                    }

                                } while (!inputStatus);
                            }
                            else if(userInput == 0){}
                            else
                            {
                                cout << "Invalid Input" << endl;
                                cin.clear();
                                cin.ignore(10000, '\n');
                                inputStatus = false;
                            }
                        } while(!inputStatus);
                    } while (!inputStatus);
                }
                else
                {
                    for(int i = 0; i < size; ++i)
                    {
                        delete[] graph[i];
                    }
                    delete[] graph;
                }
            }while(!isConnected);

           

        }
        else
        {
            cout << "Invalid Input!" << endl; 
            cin.clear();
            cin.ignore(10000, '\n');
            inputStatus = false; 
        } 
    } while(!inputStatus);


    // // Cleanup
    // for(int i = 0; i < size; ++i)
    // {
    //     delete[] graph[i];
    // }
    // delete[] graph;

    return 0;
}