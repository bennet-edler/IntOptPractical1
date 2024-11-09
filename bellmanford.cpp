#include <vector>
#include <unordered_map>
#include <limits.h>
#include "utils.cpp"
using namespace std;

// Function to run the Bellman-Ford algorithm
size_t bellmanFord(vector<Edge>& graph, size_t vertices, size_t source, size_t target, 
unordered_map<size_t, vector<int>> index_position, int n, vector<int> b, vector<vector<int>> A)
{
    // Initialize distances from source to all vertices as
    // INFINITE
    unordered_map<size_t, size_t> distance;
    distance[source] = 1;

    // the shortest path to int1 goes over int 2
    unordered_map<size_t, size_t> source_index;

    // Relax all edges |V| - 1 times (where |V| is the
    // number of vertices)
    for (int i = 0; i < vertices - 1; ++i) {
        // Iterate through all edges
        for (const Edge& e : graph) {
            // Update distances if a shorter path is found
            if (distance[e.source]) {
                if ((!distance[e.destination]) || 
                (distance[e.source] + e.weight < distance[e.destination])) {
                    distance[e.destination] = distance[e.source] + e.weight;
                    source_index[e.destination] = e.source;
                }
            }
        }
    }

    // Check for negative-weight cycles by iterating through
    // all edges again
    for (const Edge& e : graph) {
        if (distance[e.source] && distance[e.source] + e.weight< distance[e.destination]) {
            cout << "Graph contains negative weight cycle\n";
            return INT_MAX;
        }
    }
    if (!distance[target]) return INT_MAX;

    // calculate path to b and calculate x
    size_t index = target;
    vector<size_t> backwards_path;
    while (index != source) {
        backwards_path.push_back(index);
        index = source_index[index];
    }
    backwards_path.push_back(source);
    cout << "path to solution: " << endl;
    vector<int> x(n);
    vector<int> last_position = b;
    print_vector(index_position[source]);
    for(int i = 0; i < backwards_path.size(); i++) {
        cout << "->";
        vector<int> position = index_position[backwards_path[backwards_path.size()-1-i]];
        print_vector(position);
        for(int j = 0; j < A.size(); j++) {
            if (A[j] == (position-last_position)) {
                x[j] +=1;
                break;
            }
        }
        last_position = position;
    }
    cout << endl << "x: ";
    print_vector(x);

    return distance[target]-1;
}