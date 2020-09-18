#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> D(n+1);
    for(int i=1; i<=n; i++){
        cin >> D[i];
    }
    vector<int> p(n+1);
    for(int i=1; i<=n ; i++){
        for(int j=1; j<=i ; j++)
        D[i] = max(D[i],D[i-j]+p[j]);
    }
    cout << D[n] << 'n';
    return 0;
}