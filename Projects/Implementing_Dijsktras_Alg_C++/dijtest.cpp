// Online C++ compiler to run C++ program online
#include <iostream>
#include <random>
#include <fstream>
#include <sstream>
using namespace std;

//THIS WORKS... EXCEPT IN CASES WHERE THERE ARE TWO SAME PATHS -> FIXED

// STILL NEED TO FIX FOR THE CASE WHERE THE SHORTEST IMMEDIATE PATH ISN'T CORRECT -> FIXED

#include <iostream>
#include <random>
using namespace std;


void ReadGraph(double** graph, const int size)
{
    ifstream file("graph.csv");
    string line;
    int row = 0;

    while(getline(file, line) && row < size)
    {
        stringstream ss(line);
        string value;
        int col = 0;

        while(getline(ss, value, ',') && col < size)
        {
            graph[row][col] = stod(value);
            ++col;
        }
        ++row;
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
void PrintSet(T* set, const int size)
{
    for(int i = 0; i < size; ++i)
    {
        if(i == size-1) cout << set[i] << endl;
        else cout << set[i] << ", ";
    }
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
    bool foundEarly = false;
    
    if(target == 0) return 0;
    int count=0;
    int loopcount = 0;

    int node = 0; //Source node
    while(!pathFound)
    {
        cout << endl << "loop: " << loopcount++ << endl;
        cout << endl << "Distance set before: " << endl;
        PrintSet<double>(distance, size);
        cout << endl << "Open set before: " << endl;
        PrintSet<bool>(open, size);
        cout << endl << "Close set before: " << endl;
        PrintSet<bool>(close, size);
        if(open[node] && !close[node])
        {   
            close[node] = true;
            for(int i = 0; i < size; ++i)
            {
                cout << "analyzing " << i << " " << graph[node][i];
                if(graph[node][i] && !close[i]) 
                {
                    cout << " HIT!" << endl;
                    if(!open[i]) 
                    {
                        open[i] = true;
                        distance[i] = distance[node] + graph[node][i];
                        cout << "Node "<< i << " Distance " << distance[i] << endl;
                    }
                    else if(distance[i] > distance[node] + graph[node][i]) distance[i] = distance[node] + graph[node][i];
                    
                    // if(i == target && !foundEarly)
                    // {
                    //     distance[i] = distance[node] + graph[node][i];
                    //     foundEarly = true;
                    //     cout << "Target Found!" << endl;
                    // }
                }
                cout << endl;
            }   

            cout << "node analysis done" << endl;
            cout << endl << "Distance set after: " << endl;
            PrintSet<double>(distance, size);
            cout << endl << "Open set after: " << endl;
            PrintSet<bool>(open, size);
            cout << endl << "Close set after: " << endl;
            PrintSet<bool>(close, size);
            
            int prevNode = node;
            node = FindMinPath(distance, close, size);  
            
            //if(foundEarly && ( distance[prevNode] + graph[prevNode][node]) > distance[target]) return distance[target];
            
            //distance[node] = distance[prevNode] + graph[prevNode][node];

            if(distance[node] >= distance[target]) pathFound = true;

            
            cout << "Next node: " << node << " Distance: " << distance[node] << endl << endl;
        }   
    }
    return distance[target];
}

int main() {
    // Write C++ code here
    // const int size = 7;
    // double graphbase[size][size] = {{  0,  1,  1,  1,  0,  0,  0},
    //                                 {  1,  0,  0,  1,  1,  0,  0},
    //                                 {  1,  0,  0,  1,  0,  0,  },
    //                                 {  1,  1,  1,  0,  1,  1,  1},
    //                                 {  0,  1,  0,  1,  0,  0,  1},
    //                                 {  0,  0,  0,  1,  0,  0,  0},
    //                                 {  0,  0,  1,  1,  1,  0,  0}};
    
    /* double** graph = new double* [size];
    for(int i = 0; i < size; ++i) graph[i] = new double[size];
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            graph[i][j] = graphbase[i][j];
        }
    } */
    
    bool input;
    int size;
    bool inputStatus = true;
    do
    {
        cout << "Read graph grom graph.csv? Yes(1) No(0)" << endl;
        cin >> input;
        if(input) 
        {
            do
            {
                cout << "How many nodes? (positive int)" << endl;
                cin >> size;
                if(!cin)
                {
                    cout << "Invalid Input" << endl;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    inputStatus = false;
                }
                else{
                    double** graph = new double* [size];
                    for(int i = 0; i < size; ++i) graph[i] = new double[size]; 
                    ReadGraph(graph, size);

                    cout << Dijkstra<double>(graph, size, 1) << endl;
                }
            } while (!inputStatus);
            
        }
        else if(!input){}
        else 
        {   
            cout << "Invalid Input" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            inputStatus = false;
        }
    } while (!inputStatus);
    


    return 0;
}