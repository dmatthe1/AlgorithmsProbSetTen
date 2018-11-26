//CSCI 3322 Principles of Algorithms
//Problem Set Ten: Linear Fit
//Team F
//Pledged

#include <cmath>
#include <vector>
#include <stdio.h>
#include <algorithm>
#include <tuple>

using namespace std;
//LUP Decomposition Method
void LUP_Decomposition(vector<vector<double>>& matrix, vector<int>& arr){
  int n = matrix.size(); //size of the data
  int k_1;


  //
  for (int i = 0; i < n; i++) {
      arr[i] = i;
  }
  
  //
  for (int k = 0; k < n; k++) {
      
      double p = 0;
      for (int i = k; i < n; i++) {
          if (fabs(matrix[i][k]) > p) {
              p = fabs(matrix[i][k]);
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
      for (int i = 0; i < n; i++) {
          //exchange
          swap(matrix[k][i], matrix[k_1][i]);

      }

      //
      for (int i = k + 1; i < n; i++) {
          matrix[i][k] = matrix[i][k]/matrix[k][k];
          for (int j = k + 1; j < n; j++) {
              matrix[i][j] = matrix[i][j] - (matrix[i][k] * matrix[k][j]);
          }
      }

  }

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
    for(int j = i+1; j<n; j++){
      sum+=u[i][j]*arr_x[i];
    }
    arr_x[i] = (arr_y[i] - sum)/u[i][i];
  }

  return arr_x;
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
      ret[j][i] = a[i][j];
    }
  }
  return ret;
}



/*vector<vector<double>> inverse(vector<vector<double>> a){
  
}
vector<vector<double>> pseudoinverse(vector<vector<double>> matrix){

}*/

template<class T,class F>
vector<double> fitFuncs(const vector<T> &data, const vector<F> &functions) {
        vector<vector<double>> input (data.size(),vector<double>(functions.size(),0));
        vector<vector<double>> y_value (data.size(),vector<double> (1,0));
        for(int i = 0; i < data.size(); i++){
                y_value[i][0] = data[i].y;
                for(int j = 0; j < functions.size(); j++){
                        input[i][j] = functions[j](data[i].x);
                }
        }
        vector<vector<double>> input_t = transpose(input);
        cout<<"transpose"<<"\n";
        vector<int> p (functions.size()); 
        vector<vector<double>> matrix = mutiply(input_t,input);
        cout<<"mutiply"<<"\n";
        LUP_Decomposition(matrix,p);
        cout<<"decomposition"<<"\n";
        vector<vector<double>> l (matrix);
        vector<vector<double>> u (matrix);
        for(int i = 0; i < l.size(); i++){
                for(int j = 0; j < l[0].size(); j++){
                        if(i<j) l[i][j] = 0;
                        if(i==j) l[i][j] = 1;
                        if(i>j) u[i][j] = 0;
                }
        }
        cout<<"l u p"<<"\n";
        vector<double> right = transpose(mutiply(input_t, y_value))[0];
        vector<double> ret =  LUP_Solve (l,u,p,transpose(mutiply(input_t, y_value))[0]);
        for(double i:ret) cout<<i<<"\n";
        return ret;
}
