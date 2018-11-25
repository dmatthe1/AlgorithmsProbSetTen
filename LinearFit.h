//CSCI 3322 Principles of Algorithms
//Problem Set Ten: Linear Fit
//Team F
//Pledged

#include <math.h>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <tuple>

using namespace std;
//LUP Decomposition Method
tuple<vector<vector<double>>,vector<int>> LUP_Decomposition(vector<vector<double>> matrix){
  int n = matrix.size(); //size of the data

  vector<double> arr(n); //array of size n

  int k_1  = 0;

  //
  for (int i = 0; i < n; i++) {
      arr[i] = i;
  }

  //
  for (int k = 0; k < n; k++) {
      int p = 0;
      for (int i = k; i < n; i++) {
          if (matrix[i][k] > p) {
              p = matrix[i][k];
              k_1 = i;
          }
      }
      //check for singular matrix error
      if (p == 0) {
          //error singular matrix
          break;
      }
      //exchange
      swap(arr[k], arr[k_1]);

      //
      for (int i = k+1; i < n; i++) {
          //exchange
          swap(matrix[i][k], matrix[k_1][i]);
          for(int j = k+1; k<n; j++){
            matrix[i][j] = matrix[i][j]-matrix[i][k]*matrix[k][j];
          }
      }

      //
      for (int i = k + 1; i < n-1; i++) {
          matrix[i][k] = matrix[i][k]/matrix[k][k];
          //equality
          for (int j = k + 1; j < n-1; j++) {
              matrix[i][j] = matrix[i][j] - (matrix[i][k] * matrix[k][j]);
          }
      }

  }
  return make_tuple(matrix,arr);

}
//LUP solving method
vector<double> LUP_Solve(vector<vector<double>> l,vector<vector<double>> u,vector<int> pi,vector<double> b){

  int n = l.size();//size of rows of l
  vector<double> arr_x(n); //array of size n
  vector<double> arr_y(n);
  for(int i = 0; i < n; i++){
    double sum = 0;
    for(int j = 0; j<=i-1; j++){
      sum+=l[i][j]*arr_y[i];
    }
    arr_y[i] = b[pi[i]] - sum;
  }

  for(int i = n-1 ; i>=0; i--){
    double sum = 0;
    for(int j = 0; j<=i-1; j++){
      sum+=u[i][j]*arr_x[i];
    }
    arr_x[i] = (y[i] - sum)/u[i][i];
  }

  return x;
}

vector<vector<double>> mutiply(vector<vector<double>> a,vector<vector<double>> b){
  vector<vector<double>> ret (a.size(),vector<double>(b[0].size(),0));
  for(int i = 0; i<a.size();i++){
    for(int j = 0; j<b[0].size();j++){
      for(int k = 0; k<a[0].size();k++){
        ret[i][j] +=a[i][k]*b[k][j];
      }
    }
  }
  return ret;
}

vector<vector<double>> transpose(vector<vector<double>> a){
  vector<vector<double>> ret (a[0].size(),vector<double>(a.size(),0));
  for(int i = 0; i<a.size(); i++){
    for(int j = 0; j<a[0].size();j++){
      ret[j][i] = a[i][j]
    }
  }
  return ret;
}

vector<vector<double>> inverse(vector<vector<double>> a){
  
}
vector<vector<double>> pseudoinverse(vector<vector<double>> matrix){

}

template<class T,class F>
vector<double> fitFuncs(const vector<T> &data, const vector<F> &functions) {

}
