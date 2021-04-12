#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
using namespace std; 

// DEADBEEF means no edge between two nodes 
const int DEADBEEF = 9999;

// define the edge arch struct
typedef struct
{
  int u;      //node
  int v;      //node
  int cost;   //edge length between u & v
}Arc;

// compare according to edge cose
bool compare(Arc A, Arc B)
{
  return A.cost < B.cost ? true : false;
};

// graph class 
class Graph 
{
public:
  Graph();
  Graph(int Numbers);
  vector<Arc> vertexArc;              // edge vectors
  void AddEdge(int u, int v, int w);  // add edges
  int Kruskal();                      //Kruskal's algorithm
  // check if two nodes in same tree then form a loop
  bool FindTree(int u, int v, vector<vector<int>> &Tree);

private:
  int VerticesNum;      // Number of nodes of the Graph
}; 

Graph::Graph()
{
  VerticesNum = 0;
}

Graph::Graph(int Numbers)
{
  VerticesNum = Numbers;
}

// add edges
void Graph::AddEdge(int x, int y, int z)
{
  Arc temp;
  temp.u = x;
  temp.v = y;
  temp.cost = z;
  vertexArc.push_back(temp);
}

// Implement the Kruskal Minimum Spanning Tree Algorithm
int Graph::Kruskal() 
{ 
  int totalcost = 0; 
  sort(vertexArc.begin(), vertexArc.end(), compare); //sort edges by compare cost 
  vector<vector<int>> Tree(VerticesNum);
  for (int i = 0; i < VerticesNum; ++i)
  {
    Tree[i].push_back(i);             // initial of Tree
  }
  for (int i = 0; i < vertexArc.size(); ++i)
  {
    int u = vertexArc[i].u;
    int v = vertexArc[i].v;
    if (FindTree(u, v, Tree))         // compare if two nodes in same Tree
    {
      cout << "Node " << u << "--->" << "Node " << v << endl;
      totalcost = totalcost + vertexArc[i].cost;
    }
  }
  return totalcost; 
} 

// check if two nodes in same tree then form a loop
bool Graph::FindTree(int u, int v, vector<vector<int>> &Tree)
{
  int u_index = DEADBEEF;
  int v_index = DEADBEEF;
  for (int i = 0; i < Tree.size(); ++i)
  {
    if (find(Tree[i].begin(), Tree[i].end(), u) != Tree[i].end())
      u_index = i;
    if (find(Tree[i].begin(), Tree[i].end(), v) != Tree[i].end())
      v_index = i;
  }

  if (u_index != v_index)
  {
    for (int i = 0; i < Tree[v_index].size(); ++i)
    {
      Tree[u_index].push_back(Tree[v_index][i]);
    }
    Tree[v_index].clear();
    return true;
  }
  return false;
}

// main function
int main() 
{ 
/*   
// Since online c++ run and debug could not use local file and input, 
// I comment the construct of reading data from file. 
  fstream myfile("D:\\data.txt")
  int V;
  myfile >> V;
  Graph graph(V);
  int E = V * (V-1) / 2;
  for (i = 0; i < E; ++i)
  {
    int u =0;
    int v = 0;
    int cost = 0;
    myfile >> u >> v >> cost;
    graph.AddEdge(u, v, cost);
  }
*/

  // number of nodes and initial
  int nodes = 6; 
  Graph graph(nodes); 
  // two nodes and the cost of edge
  graph.AddEdge(0, 1, 6); 
  graph.AddEdge(0, 2, 1); 
  graph.AddEdge(0, 3, 5); 
  graph.AddEdge(1, 2, 5); 
  graph.AddEdge(1, 4, 3); 
  graph.AddEdge(2, 3, 5); 
  graph.AddEdge(2, 4, 6); 
  graph.AddEdge(2, 5, 4); 
  graph.AddEdge(3, 5, 2);
  graph.AddEdge(4, 5, 6);
  cout << "The Minimal Spanning Tree is "<< endl; 
  int total = 0;
  total = graph.Kruskal(); 
  cout << "Cost of Minimal Spanning Tree is " << total << endl;
  return 0;

} 