#include <iostream>
#define mod 9901;
using namespace std;
int d[100001][3];
int main(){
    int n;
    cin >> n;
    for(int i=1 ; i <=n ; i++){
        if(i==1){
            d[i][0] = 1;
            d[i][1] = 1;
            d[1][2] = 1;
            continue;
        }
        d[i][0] = d[i-1][0] + d[i-1][1] + d[i-1][2];
        d[i][1] = d[i-1][0] + d[i-1][2];
        d[i][2] = d[i-1][0] + d[i-1][1];
        for(int j=0;j<3;j++){
            d[i][j] %= mod;
        }
    }
    cout << (d[n][0] + d[n][1] + d[n][2])%mod;
    return 0;
}