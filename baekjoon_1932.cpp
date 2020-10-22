#include <iostream>
#include <algorithm>
long long d[501][501];
long long a[501][501];
long long ans=0;
using namespace std;
int main(){
    int n;
    cin >> n;
    for(int i=1; i<=n; i++){
        for(int j=1; j<i+1;j++){
            cin >> a[i][j];
        }
    }
    d[0][0] = 0;
    d[0][1] = 0;
        for(int i=1; i<=n ; i++){
        for(int j=1; j<=n ; j++){
        d[i][j] = max(d[i-1][j-1],d[i-1][j]) + a[i][j];
        }
    }
    for(int i=1; i<=n ; i++){
        ans = max(ans,d[n][i]);
    }
    cout << ans;
    return 0;
}