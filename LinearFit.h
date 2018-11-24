//CSCI 3322 Principles of Algorithms
//Problem Set Ten: Linear Fit
//Team F
//Pledged

#include <math.h>
#include <vector>
#include <stdio.h>
#include <algorithm>

using namespace std;

//LUP Decomposition Method
template<class T,class F>
vector<double> fitFuncs(const vector<T> &data, const vector<F> &functions) {
    val n = data.size(); //size of the data
    val matrix; //matrix of size n
    vector<T> arr(n); //array of size n
    vector<double> returnVect; //vector to return

    //
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }

    //
    for (int k = 0; k < n; k++) {
        val p = 0;
        for (int i = k; i < n; i++) {
            if () {

            }
        }
        //check for singular matrix error
        if (p == 0) {
            //error singular matrix
        }
        //exchange

        //
        for (int i = 0; i < n; i++) {
            //exchange
        }

        //
        for (int i = k + 1; i < n; i++) {
            //equality
            for (int j = k + 1; j < n; j++) {
                matrix[i][j] = matrix[i][j] - (matrix[i][k] * matrix[k][j]);
            }
        }
    }
}
