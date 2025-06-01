#include <stdlib.h>
#include <time.h>
#include <random>
#include <algorithm>
#include <iomanip>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

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

    inline int FindMinPath(PriorityQueue<T>& p, Graph<T> g)
    {
        int minIndex = -1;
        int index = 0;
        double minVal = __DBL_MAX__;
        for (auto element : cxnPair[2])
        {
            cout << "Current element: " << element << " ";
            cout << "Node: " << cxnPair[1][index] << " ";
            bool temp = !p.InDequeue(cxnPair[1][index]);
            cout << temp;
            if(!p.InDequeue(cxnPair[1][index]) && element < minVal)
            {
                minVal = element;
                minIndex = index;
                cout << "<- stored!";
            }
            cout << endl;
            index++;
        }
        //minIndex = distance(cxnPair[2].begin(), find(cxnPair[2].begin(), cxnPair[2].end(), minVal));
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
        if(find(cxnPair[1].begin(), cxnPair[1].end(), node2) == cxnPair[1].end())
        {
            cxnPair[0].push_back(node1);
            cxnPair[1].push_back(node2);
            cxnPair[2].push_back(value);
        }
        else
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

    inline void PrintCxnPair()
    {
        for(int i = 0; i < cxnPair.size(); ++i)
        {
            for(auto element : cxnPair[i]) cout << element;
            cout << endl;
        }
    }

    double MST(PriorityQueue<T>& p, const Graph<T>& g)
    {
        int node1 = 0;
        int node2 = 0;
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
                while(i < p.dequeue.size())
                {

                    int node1 = p.dequeue[i++];
                    //cout << "Analyzing: " << node1 << endl;
                    for(int i = 0; i < g.size; i++)
                    {
                        //update queue
                        if(g.graph[node1][i] && !p.InDequeue(i))
                        {
                            if(!p.InQueue(i)) p.AddToQueue(i);
                        }
                        int j = 0;
                        while(j < p.queue.size())
                        {
                            node2 = p.queue[j++];
                            if(g.graph[node1][node2] > 0 && !p.InDequeue(node2))
                            {
                                UpdateCxnPair(node1, node2, g.graph[node1][node2], p);
                            }
                        }
                    } 
                }
                for(auto node : p.queue) cout << node;
                cout << endl;
                
                //PrintCxnPair();

                //MST += cxnPair[2][FindMinPath(p, g)];
                //cout << "Current MST: " << MST << endl;
                int index = FindMinPath(p, g);
                node1 = cxnPair[1][index];
                PrintCxnPair();
                cout << "Dequeue: ";
                for(auto node : p.dequeue) cout << node;
                cout << endl;
                cout << "minIndex: " << index << endl;
                cout << "next node: " << node1 << endl;
            }
            if (p.dequeue.size() == g.size) MSTFound = true;
            //cout << "Moving to next closed node" << endl;
        }
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
    void Prioritize(int node){iter_swap(queue.begin(), find(queue.begin(), queue.end(), node));} //Move node to top of queue
    inline void AddToQueue(int node){queue.push_back(node);}
    inline void AddToDequeue(int node){dequeue.push_back(node);}
    inline bool InQueue(int node) {return find(queue.begin(), queue.end(), node) != queue.end();}
    inline bool InDequeue(int node) {return find(dequeue.begin(), dequeue.end(), node) != dequeue.end();}
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
    const int density;
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

    int ReadSize(const string& fileName)
    {
        ifstream file(fileName + ".txt");
        string line;
        getline(file, line);
        int size = stoi(line);
        file.close();
        return size;
    }

    int ReadGraph(const string& fileName)
    {
        cout << "called 2" << endl;
        int lineNumber = 0;
        vector<int> temp;
        ifstream file(fileName + ".txt");
        if(!file.is_open())
        {
            cout << "Could not open the file, please check file name!" << endl;
            return false;
        }
        string line;
        getline(file, line);
        int size = stoi(line);
        graph.resize(size);
        for(int i = 0; i < size; ++i) 
        {
            graph[i].resize(size); 
             cout << "rows: " << graph.size() << " cols: " << graph[i].size() << endl;
        }
            while(getline(file, line))
        {
            istringstream iss(line);
            int number;
            while(iss >> number)
            {
                temp.push_back(number);
            }
            cout << "Attempting to place cxn b/n " << temp[0] << " and " << temp[1] << " with weight " << temp[2] << endl;
            graph[temp[0]][temp[1]] = graph[temp[1]][temp[0]] = temp[2];
            temp.clear();
        }
        file.close();
        return true;
    }

public:
    Graph(const int size, const int density) : size(size), density(density) //Initializer list constructor for a graph
    {
        while(!isConnected) //Repeat graph creation until the generated graph is connected
        {
            attempts++;
            graph.assign(size, vector<T>(size, 0.0));
            for(auto nodeSelect = graph.begin(); nodeSelect != graph.end(); ++nodeSelect)
            {
                int i = distance(graph.begin(), nodeSelect);
                for(auto nodeIter = nodeSelect->begin(); nodeIter != nodeSelect->end(); ++nodeIter)
                {
                    int j = distance(nodeSelect->begin(), nodeIter);
                    if (i != j && i < j) graph[i][j] = graph[j][i] = RandomDouble(1.0, 10.0) * static_cast<T>((rand() % 100) < density);
                }
            }
            isConnected = IsConnected();
        }
        
    }
    Graph(vector<vector<double>> graph) : graph(graph), size(graph[0].size()), density(100){};
    Graph(string fileName) : size(ReadSize(fileName)), density(100)
    {
        bool status;
        do
        {
            status = ReadGraph(fileName);
        }while(!status);
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

    ~Graph(){}
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

    vector<vector<double>> graph = {{0,  4, 0,  0,  0,  0, 0,  8, 0},
                                    {4,  0, 8,  0,  0,  0, 0, 11, 0},
                                    {0,  8, 0,  7,  0,  4, 0,  0, 2},
                                    {0,  0, 7,  0,  9, 14, 0,  0, 0},
                                    {0,  0, 0,  9,  0, 10, 0,  0, 0},
                                    {0,  0, 4, 14, 10,  0, 2,  0, 0},
                                    {0,  0, 0,  0,  0,  2, 0,  1, 6},
                                    {8, 11, 0,  0,  0,  0, 1,  0, 7},
                                    {0,  0, 2,  0,  0,  0, 6,  7, 0}};
    //Graph<double> g1("test");
    Graph<double> g2(graph);
    PriorityQueue<double> p(g2);
    PathFinding<double> pF(g2);

    cout << pF.MST(p, g2) << endl;
    //pF.PrintCxnPair();

    return 0;
}