#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

class Edge{
    public:
        Edge(int n10, int n20, int v):n1(n10), n2(n20), value(v){}
        int getn1() { return n1;}
        int getn2() { return n2;}
        int getvalue() { return value;}
        void setn1(int n) {n1 = n;}
        void setn2(int n) {n2 = n;}
        void setvalue(int n) {value = n;}
    private:
        int n1, n2, value;
};

bool sortingFunction(Edge i, Edge j) {return (i.getvalue() < j.getvalue());}

class graph {
    public:
        vector<Edge> returnVector() {return g;}
        void setEdge(int n1, int n2, int value) {Edge edge(n1, n2, value); g.push_back(edge);}
        vector<Edge> sortEdges() {
            sort(g.begin(), g.end(), sortingFunction);
        }
    private:
        vector<Edge> g;
} Graph;

bool alltrue (bool arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == false) {
            return false;
        }
    }
    return true;
}

Edge chooseNextEdge(bool closed[], vector<Edge> Edges) {
    for (int i = 0; i < Edges.size(); i++) {
        if (closed[Edges[i].getn1()] == true && closed[Edges[i].getn2()] == false) {
            return Edges[i];
        }
    }
};

void printarray(bool arr[],int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << ", ";
    cout << endl;
 }

int main() {

    ifstream myfile;
    myfile.open("data");
    int a;
    int b;
    int c;
    myfile >> a; // first value is useless since we're using vectors with the ability to use .size()
    while (myfile >> a) {
        myfile >> b;
        myfile >> c;
        Graph.setEdge(a,b,c);
    }
    myfile.close();


    Graph.sortEdges();
    vector<Edge> *vec = new vector<Edge>;
    *vec = Graph.returnVector(); // created a vector (using the graph) which is sorted in terms of value;
    bool closednodes[19] = {0}; // all nodes start not closed
    closednodes[19] = 0;
    int minSpanTreeLength = 0;
    closednodes[0] = true; // assign a first node to be true

    while (!alltrue(closednodes, 20)) { // while all the nodes have not been closed
        Edge Next = chooseNextEdge(closednodes, *vec);  // choose next edge
        closednodes[Next.getn2()] = true; // add the n2 to closed edge
        minSpanTreeLength += Next.getvalue();// add value to value
    }
    cout << "min span tree for data has the value " << minSpanTreeLength << endl;
    return 0;
}