#include <iostream>
#include <algorithm>
using namespace std;
long long d[1001];
long long a[1001];
int main(){
    int n;
    cin >> n;
    for(int i=0; i<n ; i++){
        cin >> a[i];
    }
    for(int i=0; i<n; i++){
        d[i] = a[i];
        for(int j=0; j<i; j++){
            if(a[j] < a[i] && d[i] < d[j]+a[i]){
                d[i] = d[j]+a[i];
            }
        }
    }
    long long ans =0;
    for(int i=0; i<n; i++){
    ans = max(ans,d[i]);
    }
    cout << ans;

    return 0;
}