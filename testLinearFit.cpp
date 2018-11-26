#include<fstream>
#include<algorithm>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<iostream>
#include<utility>
#include<set>
#include<tuple>
#include<cmath>
#include<functional>

using std::ofstream;
using std::endl;
using std::clock;
using std::vector;
using std::string;
using std::rand;
using std::cout;
using std::pair;
using std::set;
using std::tuple;
using std::make_tuple;
using std::get;
using std::sort;

#include "LinearFit.h"

class Point {
        public:
                Point(double vx,double vy):x(vx),y(vy) {}
                double x,y;
};


int main() {
        vector<Point> data1 = {Point(0,0),Point(1,1),Point(2,2),Point(3,3)};
        vector<std::function<double (double)>> fs1{[](double x){return 1.0;}, [](double x){return x;}};
        vector<double> fit1 = fitFuncs(data1,fs1);
        vector<vector<double>> a = {{1,2,0},
                                    {3,4,4},
                                    {5,6,3}};
        vector<vector<double>> a_1 = {{2,0,2,0.6},
                                      {3,4,4,-2},
                                      {5,5,4,2},
                                      {-1,-2,3.4,-1}};

        vector<int> p = {0,0,0};
        LUP_Decomposition(a,p);
        vector<vector<double>> l (a);
        vector<vector<double>> u (a);
        for(int i = 0; i < l.size(); i++){
                for(int j = 0; j < l[0].size(); j++){
                        if(i<j) l[i][j] = 0;
                        if(i==j) l[i][j] = 1;
                        if(i>j) u[i][j] = 0;
                }
        }
       /* vector<double> ret =  LUP_Solve (l,u,p,{3,7,8});
        for(double i:ret) cout<<i<<"\n";

        for(auto i:u){
                for(auto j:i){
                        cout<<j<<"\t";
                }
                cout<<"\n";
        }*/
        vector<Point> data3 = {Point(0,0),Point(1,1),Point(2,4),Point(3,9)};
        vector<std::function<double (double)>> fs3{[](double x){return 1.0;}, [](double x){return x;},[](double x){return x*x;}};
        vector<double> fit3 = fitFuncs(data3,fs3);
        for(double i:fit3) cout<<i<<"\n"; 

        return 0;
}
