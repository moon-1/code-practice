#include <iostream>
using namespace std;
long long d[201][201] = {0,};
long long mod = 1000000000;
int main(){
    int n,k;
    cin >> n >> k;
    d[0][0] = 1LL;
    for(int i=1 ; i<=n ; i++){
        for(int j=1; j<=k ; j++){
            for(int k=1; k<i;k++){
                if(i==1){
                    d[j][i] = 0;
                }
                if(j==1){
                    d[j][i] = 1;
                    break;
                }
                else{
                    d[j][i] += d[j-1][i-k];
                }
            }
            d[j][i] %= mod;
        }
    }
    cout << d[k][n];
    return 0;
}