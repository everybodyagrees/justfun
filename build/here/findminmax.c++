#include<iostream>
#include<climits>
using namespace std;


void findMinMax(int a[],int low,int high,int &min,int &max){

if(low == high){
    if(a[low]<min)
        min = a[low];
    if(a[low]>max)
        max = a[low];
    return;
}


//array contains only two elements
 if(high ==low+1){
    if(a[low]<a[high]){
   if(a[low]<min)
        min = a[low];
    if(a[high]>max)
        max = a[high];
 }else{
    if(a[high]<min)
        min = a[high];

    if(a[low]>max)
        max = a[low];

 }
 return;


}

int mid =(low+high)/2;
findMinMax(a,low,mid,min,max);
findMinMax(a,mid+1,high,min,max);
}
int main(){

int n;
int min = INT_MAX;
int max = INT_MIN;
cout<<"ENTER THE NUMBER OF ELEMENTS IN THE ARRAY:";
cin>>n;

int a[n];
cout<<"ENTER THE ELEMENTS OF THE ARRAY:";
for(int i=0;i<n;i++){
cin>>a[i];
}

findMinMax(a,0,n-1,min,max);

cout << "Minimum element: " << min << endl;
cout << "Maximum element: " << max << endl;


return 0;
}
