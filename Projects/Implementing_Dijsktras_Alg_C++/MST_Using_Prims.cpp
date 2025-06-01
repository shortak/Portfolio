#include <stdlib.h>
#include <time.h>
#include <random>
#include <algorithm>
#include <iomanip>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

//IF YOU ARE RUNNING THIS CODE FOR THE MST ALGORITHM...
//   The MST calculation is currently only available for graph that are read in from a file or if you generate a random weighted graph...
//   The MST calcuation is NOT available for a randomly generated unweighted graph!

template <typename T>
class PriorityQueue;

template<typename T>
class Graph;

template<typename T>
class PathFinding
{
private:
    vector<double> distances;
    vector<double> MSTVec;
    vector<double> ShortestPaths;
    vector<vector<double>> cxnPair;
    inline int FindMinPath(PriorityQueue<T>& p, Graph<T> g, vector<double> vect) //Finds the smallest path in the open set (queue) and returns the next node in the queue
    {
       int minIndex = -1;
       double minVal = __DBL_MAX__;
       for(int i = 0; i < g.size; ++i)
       {
            if(!p.InDequeue(i) && vect[i] < minVal)
            {
                minVal = vect[i];
                minIndex = i;
            }
       }
       return minIndex;
    }

    inline int FindMinPath(PriorityQueue<T>& p, Graph<T> g) //Check for which node has the smallest value provided that it is not in dequeue
    {
        int minIndex = -1;
        int index = 0;
        double minVal = __DBL_MAX__;
        for (auto element : cxnPair[2])
        {
            if(!p.InDequeue(cxnPair[1][index]) && element < minVal)
            {
                minVal = element;
                minIndex = index;
            }
            index++;
        }
        return minIndex;
    }

public:
    PathFinding(Graph<T> g) : distances(g.size, __DBL_MAX__), ShortestPaths(), MSTVec(g.size, __DBL_MAX__), cxnPair(3){};
    double Dijkstras(const int target, PriorityQueue<T>& p, const Graph<T>& g) //Use Dijkstra's shortest path alg to find the shortest path from node 0 to target node
    {
        p.queue.clear(); p.dequeue.clear();
        p.AddToQueue(0);
        distances[0] = 0;
        bool pathFound= false;

        if(target == 0) return 0;

        int node = 0; //Source node
        while(!pathFound)
        { 

            if(p.InQueue(node) && !p.InDequeue(node))
            {   
                p.AddToDequeue(node);
                for(int i = 0; i < g.size; ++i)
                {
                    if(g.graph[node][i] && !p.InDequeue(i)) 
                    {
                        if(!p.InQueue(i)) 
                        {
                            p.AddToQueue(i);
                            distances[i] = distances[node] + g.graph[node][i];
                        }
                        else if(distances[i] > distances[node] + g.graph[node][i]) distances[i] = distances[node] + g.graph[node][i];
                    }
                }   
                int prevNode = node;
                node = FindMinPath(p, g, distances);
                if(distances[node] >= distances[target]) pathFound = true;
            }   
        }
        return distances[target];
    }

    inline double AverageShortestPath(PriorityQueue<T>& p, const Graph<T>& g) //Find the average of any set of values in an array (used for shortest path calculation)
    {
        for(int i = 0; i < g.size; ++i) {ShortestPaths.push_back(Dijkstras(i, p, g));}

        return accumulate(ShortestPaths.begin(), ShortestPaths.end(), 0.0)/g.size;
    }

    inline void UpdateCxnPair(const int& node1, const int& node2, double value, PriorityQueue<T>& p)
    {
        if(find(cxnPair[1].begin(), cxnPair[1].end(), node2) == cxnPair[1].end()) //If the cxn does not exist
        {
            cxnPair[0].push_back(node1);
            cxnPair[1].push_back(node2);
            cxnPair[2].push_back(value);
        }
        else //Replce if cxn exists and value is smaller
        {
            auto it=find(cxnPair[1].begin(), cxnPair[1].end(), node2);
            int index = distance(cxnPair[1].begin(), it);
            if(cxnPair[2][index]>value)
            {
                cxnPair[0][index] = node1;
                cxnPair[1][index] = node2;
                cxnPair[2][index] = value;
            }
        }
    }

    inline void PrintCxnPair() //Print cxn pair vector (FOR DEBUGGING)
    {
        for(int i = 0; i < cxnPair.size(); ++i)
        {
            for(auto element : cxnPair[i]) cout << element << ", ";
            cout << endl;
        }
    }

    inline void SortCxnPair() //Sort cxn pair in order of smaller to largest node
    {

        cout << endl;
        int j = 0;
        while(j < cxnPair[0].size())
        {
            int index = distance(cxnPair[0].begin(), min_element(cxnPair[0].begin() + j, cxnPair[0].end()));
            if (index != j)
            {
                //swap j and index...
                for(int i = 0 ; i < 3; ++i)
                {
                    cxnPair[i][j] += cxnPair[i][index];
                    cxnPair[i][index] = cxnPair[i][j] - cxnPair[i][index];
                    cxnPair[i][j] = cxnPair[i][j] - cxnPair[i][index];

                }
            }
            j++;
        }
    }

    inline void DisplayTree() //Display node pair and connection value b/n them
    {
        int node1, node2, value;
        for(int i = 0; i < cxnPair[0].size() ; ++i)
        {
            node1 = cxnPair[0][i];
            node2 = cxnPair[1][i];
            value = cxnPair[2][i];
            cout << "(" << node1 << ", " << node2 << ")" << " -> " << value << endl;
        }
    }

    double MST(PriorityQueue<T>& p, const Graph<T>& g)
    {
        int node1 = 0;
        int node2 = 0;
        int loop = 0;
        double MST = 0;
        bool MSTFound = false;

        p.queue.clear();
        p.dequeue.clear();
        p.AddToQueue(node1);

        while(!MSTFound)
        {
            if(p.InQueue(node1) && !p.InDequeue(node1))
            {
                p.AddToDequeue(node1);
                int i = 0;
                //Iterate through dequeue
                while(i < p.dequeue.size())
                {

                    int node1 = p.dequeue[i++];
                    for(int i = 0; i < g.size; i++)
                    {
                        //Update queue
                        if(g.graph[node1][i] > 0 && !p.InDequeue(i))
                        {
                            if(!p.InQueue(i)) p.AddToQueue(i);
                        }
                        int j = 0;
                        //Iterate through queue
                        while(j < p.queue.size())
                        {
                            node2 = p.queue[j++];
                            if(g.graph[node1][node2] > 0 && !p.InDequeue(node2)) //Check if node1 and node2 have a cxn, if so, store it into cxn pair
                            {
                                UpdateCxnPair(node1, node2, g.graph[node1][node2], p);
                            }
                        }
                    } 
                }
                int index = FindMinPath(p, g);
                node1 = cxnPair[1][index];
            }
            if (p.dequeue.size() == g.size) MSTFound = true;
        }
        SortCxnPair();
        return accumulate(cxnPair[2].begin(), cxnPair[2].end(), 0);
    }

    void ExportDistances() //Export shortest distance to all nodes to csv
    {
        ofstream file("distances.csv");
        if (file.is_open())
        {
            for(int i = 0; i < distances.size(); ++i)
            {
                file << distances[i];
                if(i != distances.size()-1) file << ",";
            }
        }
    }
};

template <typename T>
class PriorityQueue
{
private:
    vector<int> queue;
    vector<int> dequeue;
    friend class PathFinding<T>;

public:
    PriorityQueue(Graph<T> graph) : queue(), dequeue() {};
    inline void AddToQueue(int node){queue.push_back(node);}
    inline void AddToDequeue(int node){dequeue.push_back(node);}
    inline bool InQueue(int node) {return find(queue.begin(), queue.end(), node) != queue.end();} //Check if node is in dequeue
    inline bool InDequeue(int node) {return find(dequeue.begin(), dequeue.end(), node) != dequeue.end();} //Check if node is in dequeue
    void RemoveQueue(int node)
    {
        queue.erase(find(queue.begin(), queue.end(), node));
        dequeue.push_back(node);
    }
};

template <typename T> //Allow the graph to be bool if user chooses to generate an unweighted graph
class Graph
{
private:
    vector<vector<T>> graph;
    const int size;
    int density;
    int attempts = 0;
    bool isConnected = false;
    friend class PriorityQueue<T>;
    friend class PathFinding<T>;

    inline double RandomDouble(double min, double max) //Generate a random double number for edge placement
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<> dis(1.0, 10.0);

        return dis(gen);
    }
    
    bool IsConnected() //Checks for graph connectivity 
    {
        vector<int> close;
        vector<int> open = {0};
        int i = 0;

        while(i < open.size())
        {
            int node = open[i++];
            if(find(close.begin(), close.end(), node) == close.end()) //If we have a new open node to consider
            {
                close.push_back(node); 
                open.erase(find(open.begin(), open.end(), node)); // Put the current node into the closed set (dequeue)
                for(int j = 0; j < size; ++j) if(graph[node][j]) open.push_back(j); // Put all connecting nodes in the open set
            }
        }
        return close.size() == size;
    }

    int CalculateDensity() //Calcuate graph density
    {
        vector<bool> cxns;
        for(int i = 0; i < graph.size(); ++i)
        {
            for(int j = 0; j < graph[i].size(); ++j)
            {
                cxns.push_back(graph[i][j] ? true : false ); //Populate bool vec to average out
            }
        }

        return accumulate(cxns.begin(), cxns.end(), 0) / graph.size();
    }

    inline int ReadSize(const string& fileName) //Read first line of the txt file for size
    {
        ifstream file(fileName + ".txt");
        string line;
        getline(file, line);
        int size = stoi(line);
        file.close();
        return size;
    }

    bool ReadGraph(const string& fileName) //Read graph from txt file
    {
        int lineNumber = 0;
        vector<int> temp;
        ifstream file(fileName + ".txt");
        if(!file.is_open()) //Input validation
        {
            cout << "Could not open the file, please check file name!" << endl;
            return false;
        }
        string line;
        getline(file, line);
        int size = stoi(line);

        graph.resize(size);
        for(int i = 0; i < size; ++i) graph[i].assign(size, 0); //Initialize graph to all 0s

        while(getline(file, line)) //Populate graph
        {
            istringstream iss(line);
            int number;
            while(iss >> number)
            {
                temp.push_back(number);
            }
            graph[temp[0]][temp[1]] = graph[temp[1]][temp[0]] = temp[2];
            temp.clear();
        }
        file.close();
        return true;
    }

public:
    Graph(const int size, const int density) : size(size), density(density) //Constructor for a random graph
    {
        while(!isConnected) //Repeat graph creation until the generated graph is connected
        {
            attempts++;
            graph.assign(size, vector<T>(size, 0.0)); //Initialize graph to all 0s
            for(auto nodeSelect = graph.begin(); nodeSelect != graph.end(); ++nodeSelect)
            {
                int i = distance(graph.begin(), nodeSelect);
                for(auto nodeIter = nodeSelect->begin(); nodeIter != nodeSelect->end(); ++nodeIter)
                {
                    int j = distance(nodeSelect->begin(), nodeIter);
                    //Place edge randomly based on density
                    if (i != j && i < j) graph[i][j] = graph[j][i] = RandomDouble(1.0, 10.0) * static_cast<T>((rand() % 100) < density);
                }
            }
            isConnected = IsConnected();
        }
        
    }
    Graph(vector<vector<double>> graph) : graph(graph), size(graph[0].size()){}; //In case user wants to add graph manually
    Graph(string fileName) : size(ReadSize(fileName)) //Constructor for reading in file
    {
        bool status;
        do
        {
            status = ReadGraph(fileName);
        }while(!status);
        
        density = CalculateDensity();
    }

    int GetAttempts(){return attempts;}
    bool GetCxnStatus(){return isConnected;}

    void OutputGraphInfo() //Display graph info if user loads one in from file
    {
        cout << "size: " << size << endl;
        cout << "density: " << density << endl;
        if(IsConnected())
        {
            cout << "connected!" << endl << endl;
        }
        else{
            cout << "disconnected!" << endl << endl;
        }
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
        cout << "Graph written to graph.csv!" << endl << endl;
    }

    ~Graph(){}
};

bool GetYesNo(const string& prompt) //Ask user for a yes or no input
{
    bool input;
    while(true)
    {
        cout << "-------------------------------"<< endl;
        cout << prompt << " Yes(1) No(0)" << endl;
        if(cin >> input) //Input Validation
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
        cout << "-------------------------------"<< endl;
        cout << prompt;
        if(cin >> input && input >= min && input <= max){return input;} //Input validation
        cout << "Invalid input. Please enter an integer between " << min << " and " << max << "." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

string GetFileName(const string& prompt)
{
    string input;
    bool containsExt = false;
    while(true)
    {
        cout << "-------------------------------"<< endl;
        cout << prompt;
        cin >> input;
        for(char c : input) if(c == '.') containsExt = true;
        if(!containsExt){return input;} //Input Validation
        
        cout << "Invalid input." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }
}



int main()
{
    srand(time(0));

    if(GetYesNo("Read in graph from txt file?"))
    {
        string fileName = GetFileName("Please enter text file name (exclude .txt): ");
        Graph<double> g(fileName);
        cout << endl << "Graph read!" << endl;
        g.OutputGraphInfo();
        PriorityQueue<double> p(g);
        PathFinding<double> pF(g);
        if(GetYesNo("Export graph to graph.csv?")) g.ExportGraph();
        if(GetYesNo("Continue to average shortest path calculation?"))
        {
            cout << endl << "Average shortest path: " << pF.AverageShortestPath(p, g) << endl << endl;
            if(GetYesNo("Export distances to distances.csv?")) pF.ExportDistances();
        }
        
        if(GetYesNo("Continue to MST Calculation?"))
        {
            int MST = pF.MST(p, g);
            cout << endl << "MST: " << MST << endl;
        } 
        if(GetYesNo("Display tree?")) pF.DisplayTree();

    }
    else
    {
        int size = GetBoundedInt("Size of graph (enter integer > 1): ", 2, 1000);
        int density = GetBoundedInt("Density of graph (0-100): ", 0, 100);
        bool isWeighted = GetYesNo("Weighted graph?");

        if(isWeighted)
        {
            cout << "Generating weighted graph with " << size << " nodes and density of " << density 
            << "..." << endl;
            Graph<double> g(size, density);
            PriorityQueue<double> p(g);
            PathFinding<double> pF(g);
            if(g.GetCxnStatus())
            {
                cout << "Graph generated in " << g.GetAttempts() << " attempt(s)" << endl;
                if(GetYesNo("Export graph to graph.csv?")) g.ExportGraph();
                if(GetYesNo("Continue to average shortest path calculation?"))
                {
                    cout << "Average shortest path: " << pF.AverageShortestPath(p, g) << endl;
                    if(GetYesNo("Export distances to distances.csv?")) pF.ExportDistances();
                }
                if(GetYesNo("Continue to MST Calculation?"))
                {
                    int MST = pF.MST(p, g);
                    cout << endl << "MST: " << MST << endl;
                } 
                if(GetYesNo("Display tree?")) pF.DisplayTree();
            }
        }
        else
        {
            cout << "Generating unweighted graph with " << size << " nodes and density of " << density
            << "..." << endl;
            Graph<bool> g(size, density);
            PriorityQueue<bool> p(g);
            PathFinding<bool> pF(g);
            if(g.GetCxnStatus())
            {
                cout << "Graph generated in " << g.GetAttempts() << " attempt(s)" << endl;
                if(GetYesNo("Export graph to graph.csv?")) g.ExportGraph();
                if(GetYesNo("Continue to average shortest path calculation?")) 
                {
                    cout << "Average shortest path: " <<pF.AverageShortestPath(p, g) << endl;
                    if(GetYesNo("Export distances to distances.csv?")) pF.ExportDistances();
                }
            }
        }
    }
    return 0;
}