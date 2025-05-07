#include<iostream>
#include<vector>
#include<omp.h>
#include<chrono>
using namespace std;
using namespace std::chrono;
void b(vector<int> &arr,int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
            }
        }
    }
}
void bp(vector<int> &arr,int n){
    #pragma omp parallel for 
    for(int i=0;i<arr.size();i++){
        for(int j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
            }
        }
    }
}
void merge(vector<int>&a,int left,int right,int mid,int n){
    int n1=mid-left+1;
    int n2=right-mid;
    vector<int>L(n1),R(n2);
    for(int i=0;i<n1;i++){
        L[i]=a[left+i];
    }
    for(int i=0;i<n2;i++){
        R[i]=a[mid+i+1];
    }
    int i=0;
    int j=0;
    int k=left;
    while(i<n1 && j<n2){
        if(L[i]<R[j]){
            a[k++]=L[i++];
        }else{
            a[k++]=R[j++];
        }
    }
    while(i<n1){
        a[k++]=L[i++];
    }
    while(j<n2){
        a[k++]=R[j++];
    }
}
void m(vector<int>&a,int l,int r,int n){
    if(l<r){
        int mid=(l)+(r-l)/2;
        m(a,l,mid,n);
        m(a,mid+1,r,n);
        merge(a,l,r,mid,n);
    }
}
void mp(vector<int>&a,int l,int r,int n){
    
    if(l<r){
        int mid=(l)+(r-l)/2;
        
        
        if(r-l<1000){
            m(a, l, mid, n);
            m(a, mid + 1, r, n);
        }else{
        #pragma omp parallel sections 
        {
        #pragma omp section
        mp(a,l,mid,n);
        #pragma omp section
        mp(a,mid+1,r,n);
        }
    }
        merge(a,l,r,mid,n);
       
    }
}

int main(){
    int n=15000;
    vector<int> arr(n);
    for(int i=0;i<n;i++){
        arr[i]=rand()%n;
        }
        omp_set_num_threads(4);
     
    vector<int> a2=arr;
    double start=omp_get_wtime();
    b(a2,n);
    double end=omp_get_wtime();
    double time = end-start;
    cout<<"Time is : "<< time<<"\n";

    double start2=omp_get_wtime();
    bp(a2,n);
    double end2=omp_get_wtime();
    double time2 = end2-start2;
    cout<<"Time up factor is : "<< time2<<"\n";
    cout<<"Speed up : "<< time/time2<<"\n";

        vector<int> arr2=arr;
    double start3=omp_get_wtime();
    m(arr2,0,arr2.size()-1,n);
    double end3=omp_get_wtime();
    double time3 = end3-start3;
    cout<<"Time up factor is : "<< time3<<"\n";

        vector<int> arr4=arr;
    double start4=omp_get_wtime();
    mp(arr4,0,arr4.size()-1,n);
    double end4=omp_get_wtime();
    double time4= end4-start4;
    cout<<"Time up factor is : "<< time4<<"\n";
    cout<<"Speed up : "<< time3/time4<<"\n";

}