#include<iostream>
#include<vector> 
#include<omp.h>
#include<chrono>
using namespace std;
using namespace std::chrono;
int add(vector<int> &a){
    int sum=0;
    for(int i=0;i<a.size();i++){
        sum+=a[i];
    }
    return sum;
}
int addp(vector<int> &a){
    int sum=0;
    #pragma omp parallel for reduction(+:sum)
    for(int i=0;i<a.size();i++){
        sum+=a[i];
    }
    return sum;
}
int avgp(vector<int> &a){
    int total=0;
    #pragma omp parallel for reduction(+:total)
    for(int i=0;i<a.size();i++){
        total+=a[i];
    }
    return total/a.size();
}
int avg(vector<int> &a){
    int total=0;
    
    for(int i=0;i<a.size();i++){
        total+=a[i];
    }
    return total/a.size();
}
int minp(vector<int> &a){
    int min=a[0];
    #pragma  omp parallel for reduction(min:min)
    for(int i=1;i<a.size();i++){
        if(min>a[i]){
            min=a[i];
        }
    }
    return min;
}
int min(vector<int> &a){
    int min=a[0];
    
    for(int i=1;i<a.size();i++){
        if(min>a[i]){
            min=a[i];
        }
    }
    return min;
}

int maxp(vector<int> &a){
    int max=a[0];
    #pragma  omp parallel for reduction(max:max)
    for(int i=1;i<a.size();i++){
        if(max<a[i]){
            max=a[i];
        }
    }
    return max;
}

int max(vector<int> &a){
    int max=a[0];
    
    for(int i=1;i<a.size();i++){
        if(max>a[i]){
            max=a[i];
        }
    }
    return max;
}

int main(){
    int n=100000000;
    vector<int> arr(n);
    for(int i=0;i<n;i++){
        arr[i]=rand()%n;
    }
    double start=omp_get_wtime();
    int ans= add(arr);
    cout<< "Summation is "<< ans<<"\n";
    double end=omp_get_wtime();
    double time = (end-start);
    cout<<"Time is  :"<<time<<"\n";

    double start2=omp_get_wtime();
    int ans2= addp(arr);
    cout<< "Summation is "<< ans2<<"\n";
    double end2=omp_get_wtime();
    double time2 = (end2-start2);
    cout<<"Time is  :"<<time2<<"\n";
    cout<<"Speed Up Factor : "<<time/time2<<"\n";

    double start3=omp_get_wtime();
    int ans3= avg(arr);
    cout<< "Average is "<< ans3<<"\n";
    double end3=omp_get_wtime();
    double time3 = (end3-start3);
    cout<<"Time is  :"<<time3<<"\n";


    double start4=omp_get_wtime();
    int ans4= avgp(arr);
    cout<< "Average  is "<< ans4<<"\n";
    double end4=omp_get_wtime();
    double time4 = (end4-start4);
    cout<<"Time is  :"<<time4<<"\n";
    cout<<"Speed Up Factor : "<<time3/time4<<"\n";

    double start5=omp_get_wtime();
    int ans5= max(arr);
    cout<< "Max is "<< ans5<<"\n";
    double end5=omp_get_wtime();
    double time5 = (end5-start5);
    cout<<"Time is  :"<<time5<<"\n";


    double start6=omp_get_wtime();
    int ans6= maxp(arr);
    cout<< "Max is "<< ans6<<"\n";
    double end6=omp_get_wtime();
    double time6 = (end6-start6);
    cout<<"Time is  :"<<time6<<"\n";
    cout<<"Speed Up Factor : "<<time5/time6<<"\n";


    double start7=omp_get_wtime();
    int ans7= min(arr);
    cout<< "Min is "<< ans7<<"\n";
    double end7=omp_get_wtime();
    double time7 = (end7-start7);
    cout<<"Time is  :"<<time7<<"\n";


    double start8=omp_get_wtime();
    int ans8= minp(arr);
    cout<< "Min is "<< ans8<<"\n";
    double end8=omp_get_wtime();
    double time8 = (end8-start8);
    cout<<"Time is  :"<<time8<<"\n";
    cout<<"Speed Up Factor : "<<time7/time8<<"\n";


}