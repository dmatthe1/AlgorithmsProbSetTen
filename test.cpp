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

bool compVects(const vector<double> &a,const vector<double> &b) {
        if (a.size()!=b.size()){
                cout<< "Size mismatch "<<a.size()<< " " <<b.size()<<endl;
                return false;
        }
        for(unsigned int i=0; i<a.size(); ++i) {
                if(std::fabs(a[i]-b[i])>1e-2) {
                        cout << "Failed " << i << " " << a[i] << " " << b[i] << endl;
                        return false;
                }
        }
        return true;
}

int main(int argc,char** argv) {
        ofstream out("time.txt");
        std::srand(43);


        vector<Point> data1 = {Point(0,0),Point(1,1),Point(2,2),Point(3,3)};
        vector<std::function<double (double)>> fs1{[](double x){return 1.0;}, [](double x){return x;}};
        vector<double> fit1 = fitFuncs(data1,fs1);
        if(!compVects(fit1,{0,1})) {
                cout << "Failed fit 1" << endl;
                return 1;
        }

        vector<Point> data2 = {Point(0,1),Point(1,2),Point(2,3),Point(3,4)};
        vector<double> fit2 = fitFuncs(data2,fs1);
        if(!compVects(fit2,{1,1})) {
                cout << "Failed fit 2" << endl;
                return 1;
        }

        vector<Point> data3 = {Point(0,0),Point(1,1),Point(2,4),Point(3,9)};
        vector<std::function<double (double)>> fs3{[](double x){return 1.0;}, [](double x){return x;},[](double x){return x*x;}};
        vector<double> fit3 = fitFuncs(data3,fs3);
        if(!compVects(fit3,{0,0,1})) {
                cout << "Failed fit 3" << endl;
                return 1;
        }

        vector<double> ans4;
        vector<std::function<double (double)>> fs4;
        for(int i=0; i<8; ++i) {
                ans4.push_back(rand()%11-5);
                fs4.push_back([i] (double x) {return std::pow(x,i);});
        }
        vector<Point> data4;
        for(int i=0; i<1000000; ++i) {
                double x = rand()%1000000000/1e9;
                double y = 0.0;
                for(unsigned int j=0; j<ans4.size(); ++j) y += ans4[j]*fs4[j](x);
                data4.push_back(Point(x,y));
        }

        vector<double> ans5;
        for(int i=0; i<8; ++i) {
                ans5.push_back(rand()%11-5);
        }
        vector<Point> data5;
        for(int i=0; i<1000000; ++i) {
                double x = rand()%1000000000/1e9;
                double y = 0.0;
                for(unsigned int j=0; j<ans5.size(); ++j) y += ans5[j]*fs4[j](x);
                data5.push_back(Point(x,y));
        }

        vector<double> ans6;
        vector<std::function<double (double)>> fs6{
                [] (double x) { return 1.0; },
                [] (double x) { return x; },
                [] (double x) { return x*x; },
                [] (double x) { return x*x*x; },
                [] (double x) { return x*x*x*x; },
                [] (double x) { return std::sin(x); },
                [] (double x) { return std::cos(x); },
                [] (double x) { return std::tan(x); },
                [] (double x) { return std::sqrt(x); }
        };
        for(unsigned int i=0; i<fs6.size(); ++i) {
                ans6.push_back(rand()%10);
        }
        vector<Point> data6;
        for(int i=0; i<10000; ++i) {
                double x = rand()%1000000000/1e9*6.28;
                double y = 0.0;
                for(unsigned int j=0; j<ans6.size(); ++j) y += ans6[j]*fs6[j](x);
                data6.push_back(Point(x,y));
        }
        cout << "Start timing tests." << endl;
        double start = clock();

        vector<double> fit4 = fitFuncs(data4,fs4);
        vector<double> fit5 = fitFuncs(data5,fs4);
        vector<double> fit6 = fitFuncs(data6,fs6);

        out << (clock()-start)/CLOCKS_PER_SEC << endl;
        out.close();
        cout << "Done timing." << endl;
        if(!compVects(fit4,ans4)) {
                cout << "Failed fit 4" << endl;
                return 1;
        }
        if(!compVects(fit5,ans5)) {
                cout << "Failed fit 5" << endl;
                return 1;
        }
        if(!compVects(fit6,ans6)) {
                cout << "Failed fit 6" << endl;
                return 1;
        }


        return 0;
}
