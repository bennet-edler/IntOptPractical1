#include <iostream>
#include <vector>
using namespace std;

class Edge{
public:
    size_t weight;
    size_t source;
    size_t destination;
};
// add vector addition (to std::vector<int>)
vector<int> operator+(std::vector<int> &v1, const std::vector<int> &v2) {
    vector<int> v3(v2.size());
    for (int i = 0; i < v1.size(); i++){
        v3[i]=v1[i]+v2[i];
    }
    return v3;
}

// add vector subtraction (to std::vector<int>)
vector<int> operator-(std::vector<int> &v1, const std::vector<int> &v2) {
    vector<int> v3(v2.size());
    for (int i = 0; i < v1.size(); i++){
        v3[i]=v1[i]-v2[i];
    }
    return v3;
}

// add (rounded) scalar multiplication
vector<int> operator*(float t, const std::vector<int> &v) {
    vector<int> v2(v.size());
    for (int i = 0; i < v.size(); i++){
        v2[i]=(int)(t*v[i] + 0.5);
    }
    return v2;
}

void print_vector(vector<int> v) {
    cout << "(";
    for (int i = 0; i < v.size()-1; i++) {
        cout << v[i] << ", ";
    } cout << v[v.size()-1] << ")" << endl;
}

int l1_norm(vector<int> v) {
    int sum = 0;
    for (int i = 0; i < v.size(); i++) {
        sum += abs(v[i]);
    }
    return sum;
}

int l_infty_norm(vector<int> v) {
    int max = abs(v[0]);
    for (int i = 1; i < v.size(); i++) {
        if (abs(v[i]) > max) max = abs(v[i]);
    }
    return max;
}