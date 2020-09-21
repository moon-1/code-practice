#include <iostream>
#include <algorithm>
using namespace std;
long long d[100001][3];
long long score[100001][2];
int main(){
    int input1;
    cin >> input1;
    for(int a=0; a<input1 ; a++){
        int input2;
        cin >> input2;
        for(int b=1; b<=input2;b++){
            cin >> score[b][0];
        }
        for(int b=1; b<=input2;b++){
            cin >> score[b][1];
        }
        d[0][0] = d[0][1] = d[0][2] = 0;    
        for(int i=1 ; i<=input2; i++){
            d[i][0] = max({d[i-1][0],d[i-1][1],d[i-1][2]});
            d[i][1] = max(d[i-1][0],d[i-1][2])+score[i][0];
            d[i][2] = max(d[i-1][0],d[i-1][1])+score[i][1];
            
        }
        long long ans = max({d[input2][0],d[input2][1],d[input2][2]});
        cout << ans << '\n';
    }

    return 0;

}