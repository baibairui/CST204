#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Template class List for creating a linked list
template <class T>
class List {
private:
    // Internal node structure
    struct Node {
        T arr;       // Data stored in the node
        Node* next;   // Pointer to the next node
        Node(T d) : arr(d), next(NULL) {}  // Node constructor
    };
    Node* head;  // Head node of the list

public:
    List() : head(NULL) {}  // Constructor initializes an empty list

    // Add a new node at the beginning of the list
    void push(T arr) {
        Node* newNode = new Node(arr); // Create a new node
        newNode->next = head;           // New node points to the original head node
        head = newNode;                 // Update head to the new node
    }

    // Return the size of the list
    int arrsize() {
        Node* temp = head;
        int num = 0;
        while (temp) {
            temp = temp->next;
            num++;
        }
        return num;
    }

    // Destructor to free memory used by the list
    ~List() {
        Node* current = head;
        while (current != NULL) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    // Overload the [] operator to access elements in the list
    T& operator [] (int index) {
        Node* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->arr; // Return the data at the given index
    }
};

// Graph class representing a directed, weighted graph using an adjacency list
class Graph {
private:
    // Internal structure to represent an edge
    struct Edge {
        int weight;  // Weight of the edge
        int dest;    // Destination vertex
        Edge(int w, int d) : weight(w), dest(d) {} // Edge constructor
    };
    List<List<Edge>> adjList; // Adjacency list to store the edges

public:
    // Add a vertex to the graph
    void addVertex() {
        List<Edge> newVertex;
        adjList.push(newVertex);
    }

    // Add an edge to the graph
    void addEdge(int u, int v, int w) {
        Edge e(w, v);       // Create an edge
        adjList[u].push(e); // Add the edge to the adjacency list
    }

    // Count the total number of edges in the graph
    int countEdges() {
        int count = 0;
        for (int i = 0; i < adjList.arrsize(); i++) {
            count += adjList[i].arrsize();
        }
        return count;
    }

    // Constructor to create a graph with specified number of vertices and edges
    Graph(int num_vertices, int num_edges) {
        for (int i = 0; i < num_vertices; i++) {
            addVertex();
        }
        for (int i = 0; i < num_edges; i++) {
            int u = rand() % num_vertices; // Randomly choose a source vertex
            int v = rand() % num_vertices; // Randomly choose a destination vertex
            int w = rand() % 100;          // Randomly assign a weight
            addEdge(u, v, w);              // Add the edge to the graph
        }
    }
};
/*
int main() {
    srand(time(NULL));  // Seed the random number generator
    Graph A(1000, 100 * 100);   // Sparse Graph with 100x100 edges
    Graph B(1000, 600 * 600);   // Dense Graph with 600x600 edges
    Graph C(1000, 1000 * 1000); // Complete Graph with 1000x1000 edges

    // Print the number of edges in each graph
    cout << "Graph\tA\tB\tC\n";
    cout << "Edges\t" << A.countEdges() << "\t" << B.countEdges() << "\t" << C.countEdges() << "\n";

    return 0;
}*/
