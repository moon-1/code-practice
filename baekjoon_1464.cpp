#include <iostream>
#define MAX 1000000
using namespace std;
int d[MAX];
int go(int n){
    if(n==1) return 0;
    if(d[n] > 0) return d[n];//메모리제이션
    d[n] = go(n-1)+1;
    if(n%2 == 0){
        int temp = go(n/2) +1;
        if(d[n] > temp) d[n] = temp;
    }
    if(n%3 == 0){
        int temp = go(n/3) + 1;
        if(d[n] > temp) d[n] = temp;
    }
    return d[n];
}
int main(){
    int n;
    cin >> n;
    cout << go(n);
}