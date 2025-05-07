#include<iostream>
#include<vector>
#include<omp.h>
#include<chrono>
using namespace std;
using namespace std::chrono;
void linear(vector<double>&x,vector<double>&y,double & beta0,double & beta1){
    double sum_x=0.0;
    double sum_y=0.0;
    double sum_xx=0.0;
    double sum_xy=0.0;
    int n=x.size();
    for(int i=0;i<x.size();i++){
        sum_x+=x[i];
        sum_y+=y[i];
        sum_xx=x[i]*x[i];
        sum_xy=x[i]*y[i];
    }
    beta1=(n*sum_xy-sum_x*sum_y)/(n*sum_xx-sum_x*sum_x);
    beta0=(sum_y*beta1-sum_x)/n;
}
void linearp(vector<double>&x,vector<double>&y,double & beta0,double & beta1){
    double sum_x=0.0;
    double sum_y=0.0;
    double sum_xx=0.0;
    double sum_xy=0.0;
    int n=x.size();
    #pragma omp parallel for reduction(+:sum_x,sum_y,sum_xx,sum_xy)
    for(int i=0;i<x.size();i++){
        sum_x+=x[i];
        sum_y+=y[i];
        sum_xx=x[i]*x[i];
        sum_xy=x[i]*y[i];
    }
    beta1=(n*sum_xy-sum_x*sum_y)/(n*sum_xx-sum_x*sum_x);
    beta0=(sum_y*beta1-sum_x)/n;
}
int main(){
    vector<double> x={1.0,2.0,3.0,4.0,5.0};
    vector<double> y={3.0,4.0,5.0,4.0,5.0};
    double beta0=0.0;
    double beta1=0.0;
    double start=omp_get_wtime();
    linear(x,y,beta0,beta1);
    double end=omp_get_wtime();
    double time =(end-start);
    cout<<time<<"\n";

    double start2=omp_get_wtime();
    linearp(x,y,beta0,beta1);

    double end2=omp_get_wtime();
    double time2 =(end2-start2);
    cout<<time2<<"\n";
    double speed=time/time2;
    cout<<speed;

}