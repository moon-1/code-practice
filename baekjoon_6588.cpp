#include <iostream>
using namespace std;
const int MAX = 1000000;
int prime[MAX];//소수값 저장
int pn;
bool check[MAX+1];//소수이면 false;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    //에라토스테네스의 체
    for(int i = 2; i <=MAX ; i++){
        if(check[i]==false){
            prime[pn++]= i;
        for(int j = i+i; j<=MAX;j+=i){
            check[j] = true;
            }
        }
    }
    while(true){
        int n;
        cin >> n;
        if(n == 0){
            break;
        }
        /*N=a+b일때 a,b둘다 소수라면 N-b=a도 소수이므로 N-b가 소수인것을 판별*/
        for(int i =1 ; i<pn ; i++){
            if(check[n-prime[i]] == false){
                cout << n << " = " << prime[i] << " + " << n-prime[i] << '\n';
                break;
            }
        }
    }
    return 0;
}