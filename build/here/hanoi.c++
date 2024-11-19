/*#include<iostream>
using namespace std;
void hanoi(int n,char from_rod,char to_rod,char aux_rod){
    if(n==0){
        return ;}
    hanoi(n-1,from_rod,aux_rod,to_rod);
    cout<<" move "<<n<<"from_rod"<<from_rod<<" to "<<to_rod<<endl;
    hanoi(n-1,aux_rod,to_rod,from_rod);
}*/

#include <bits/stdc++.h>
using namespace std;

void towerOfHanoi(int n, char from_rod, char to_rod,
                  char aux_rod)
{
    if (n == 0) {
        return;
    }
    towerOfHanoi(n - 1, from_rod, aux_rod, to_rod);
    cout << "Move disk " << n << " from rod " << from_rod
         << " to rod " << to_rod << endl;
    towerOfHanoi(n - 1, aux_rod, to_rod, from_rod);
}

int main(){

int n;
cout<<"Enter the number:";
cin>>n;
//cout<<"Tower of Hanoi:"<<hanoi(n);
towerOfHanoi(n,'A','B','C');
return 0;
}
