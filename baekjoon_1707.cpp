#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
vector<int> a[20001];
int group[20001];
void dfs(int node,int c){
    group[node] = c;
    //각각의 정점의 간선들을 순회
    for(int i=0;i<a[node].size();i++){
        int next = a[node][i];
        if(group[next]==0){//방문하지 않은 경우
            dfs(next,3-c);//방문, 그룹을 교환해줌(1->2,2->1)
        }
    }
}
int main(){
    int t;
    scanf("%d",&t);//테스트 케이스 입력받음
    while(t--){
        int n,m;
        scanf("%d %d",&n,&m);//정점, 간선 개수 
        for(int i=1;i<=n;i++){
            a[i].clear();
            group[i] = 0;
        }
        for(int i=0;i<m;i++){
            int u,v;
            scanf("%d %d",&u,&v);//간선 정보 
            a[u].push_back(v);
            a[v].push_back(u);
        }
        for(int i=1;i<=n;i++){
            if(group[i]==0){
                dfs(i,1);
            }
        }
        bool ok = true;
        for(int i=1;i<=n;i++){
            for(int j=0;j<a[i].size();j++){
                int k = a[i][j];
                if(group[i] == group[k]){
                    ok = false;
                }
            }
        }
        printf("%s\n",ok ? "YES" : "NO");
    }
    return 0;
}