#include<iostream>
using namespace std;


int sum(int n){
    /* if(n<=1)
    return n;
  return n+sum(n-1);*/

  int sum =0;
  for(int i=0;i<=n;i++){
    sum += i;
  }
  return sum;
}

int main(){

int n;
cout<<"Enter the number:";
cin>>n;
cout<<"sum is:"<<sum(n);
return 0;
}
