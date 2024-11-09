
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void print_vector(vector<int> v);

void read_file(string filename, int &n, int &m, int &delta, vector<int> &b, vector<int> &c, vector<vector<int>> &A){
    ifstream file(filename);
    if (file.is_open()) {
        file >> n;
        file >> m;
        for (int i = 0; i < m; i++) {
            int bi;
            file >> bi;
            b.push_back(bi);
        }

        for (int i = 0; i < n; i++) {
            int ci;
            file >> ci;
            c.push_back(ci);
        }

        for (int i = 0; i < n; i++) {
            vector<int> ai(m);
            A.push_back(ai);
        }
        for(int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int aij;
                file >> aij;
                A[j][i] = aij;
                if (abs(aij)>delta) delta = aij;
            }
        }
    }

    // print contents of the file
    cout << "read file: " << filename << endl;
    cout << "n: " << n << endl;
    cout << "m: " << m << endl;
    cout << "b: ";
    print_vector(b);
    cout << "c: ";
    print_vector(c);
    cout << "column vectors of A: " << endl;
    for(int i = 0; i < A.size(); i++) {
        print_vector(A[i]);
    }
    cout << endl;
}
