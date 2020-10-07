#include <iostream>
#include <queue>
#include <vector>
using namespace std;
vector<int> a[100000];
int parent[100000];
int order[100000];
bool check[100000];
int main(){
    int n;
    cin >> n;
    for(int i=0; i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u -= 1; v -= 1;
        a[u].push_back(v);
        a[v].push_back(u);
    }
    for(int i=0; i<n; i++){
        cin >> order[i];
        order[i] -= 1;
    }
    queue<int> q;
    q.push(0);
    check[0] = true;
    int m = 1;// 큐의 크기
    for(int i=0; i<n ; i++){
        if(q.empty()){//아직 BFS가 진행중인데 큐가 비어있음
            cout << 0 << '\n';
            return 0;
        }
        int x = q.front(); q.pop();
        if(x != order[i]){//순서가 올바르지 않음
            cout << 0 << '\n';
            return 0;
        }
        int cnt = 0;//이번에 큐에 넣어야 할 정점의  수
        for(int y : a[x]){
            if(check[y] == false){
                parent[y] = x;
                cnt += 1;
            }
        }
        for(int j =0 ; j<cnt;j++){
            if(m+j >= n || parent[order[m+j]] != x){
                cout << 0 << '\n';
                return 0;
            }
            q.push(order[m+j]);
            check[order[m+j]] = true;
        }
        m += cnt;
    }
    cout << 1 << '\n';
    return 0;

}