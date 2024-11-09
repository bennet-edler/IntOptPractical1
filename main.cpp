
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <iostream>
#include <limits.h>
#include <fstream>
#include "filehandling.cpp"
#include "bellmanford.cpp"
using namespace std;

class Dynamic_Program {
  public:

    vector<vector<int>> A;
    vector<int> b;
    int delta;
    int m;
    vector<int> c;

    vector<Edge> edges;
    size_t size;
    size_t origin_index;
    size_t b_index;
    unordered_map<size_t, bool> index_visited;
    unordered_map<size_t, vector<int>> index_position;

    vector<vector<int>> b_integer_points;


    // basically just a hash function
    size_t vector_to_address(vector<int> v){
        size_t address = 0;
        size_t cells = 1;
        for (int i = 0; i < b.size(); i++) {
            int dist_border = abs(min(0, b[i]))+2*m*delta;
            address += cells*(dist_border+v[i]);
            cells *= (4*m*delta+abs(b[i])+1);
        }
        return address;
    }

    bool is_in_distance(vector<int> v) {
        // calculate distance to all integer points on b
        for (int i = 0; i < b_integer_points.size(); i++) {
            vector<int> point = b_integer_points[i];
            if (l_infty_norm(v-point) <= 2*m*delta) return true;
        } return false;
     }

    Dynamic_Program(vector<vector<int>> A, vector<int> b, int delta, int m, vector<int> c)
    : A(A), b(b), delta(delta), m(m), c(c)
    {   
        // calculate the maximal amount of vertices
        size = 1;
        for (int i = 0; i < b.size(); i++){
            size *= 4*m*delta+b[i]+1;
        }
        // calculate all integer points on b
        int number_of_points = l1_norm(b);
        for (int i = 0; i <= number_of_points; i++) {
            float t = (float)i/(float)number_of_points;
            b_integer_points.push_back(t * b);
        }

        // create graph
        vector<int> origin(b.size(), 0);
        origin_index = vector_to_address(origin);
        index_position[origin_index] = origin;
        add_node(origin, origin_index);
        b_index = vector_to_address(b);

    }

    void add_node(vector<int> position, size_t index) {
        for (int i = 0; i < A.size(); i++) {
            vector<int> next_pos = position+A[i];
            size_t next_index = vector_to_address(next_pos);

            if (is_in_distance(next_pos)){
                Edge edge{};
                edge.source = index;
                edge.destination = next_index;
                edge.weight = c[i]; 
                edges.push_back(edge);

                if (!index_visited[next_index]) {
                    index_visited[next_index] = true;
                    index_position[next_index] = next_pos;
                    add_node(next_pos, next_index);
                }
            }
        }
    }
};


int main() {
    int n;
    int m;
    vector<int> b;
    vector<int> c;
    vector<vector<int>> A;
    int delta = 0;

    read_file("instances/3.txt", n, m, delta, b, c, A);

    Dynamic_Program dp{A, b, delta, m, c};

    int result  = bellmanFord(dp.edges, dp.size, dp.origin_index, dp.b_index, dp.index_position, n, b, A);
    if (result == INT_MAX) cout << "no feasable path found" << endl;
    else cout << "result: " << result << endl;

}

/*
b)
consider 1.txt with n=5, m=3, delta=3, |b|=25
computing a solution took 2 minutes and 15 seconds
computing (4*m*delta+1)^m * |b|*n results in 6331625

consider 2.txt with n=4, m=2, delta=20, |b|=35
computing a solution took 7.05 seconds
computing (4*m*delta+1)^m * |b|*n results in 3628940

consider 3.txt with n=4, m=2, delta=6, |b|=46
computing a solution took 0.67 seconds
computing (4*m*delta+1)^m * |b|*n results in 441784

consider 4.txt with n=4, m=2, delta=7, |b|=41
computing a solution took 0.72 seconds
computing (4*m*delta+1)^m * |b|*n results in 532836


since 3.txt and 4.txt are close together in actual execution time, they should be as well in theoretical execution time (and they are)
the actual execution time of 2.txt is approximately 10 times bigger than of 3.txt and 4.txt the same relation holds for the theoretical executions time
1.txt should have, considering the theoretical execution time, the biggest actual execution time (which it has). 
furthermore should the actual execution time be approximately twice the actual execution time of 2.txt. But the actual execution time is much (20x) bigger.
*/
