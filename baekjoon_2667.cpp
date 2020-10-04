#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
int a[30][30]; //집 입력
int d[30][30];//방문 여부
int dx[] = {0,0,1,-1}; //{우,좌,하,상} 행
int dy[] = {1,-1,0,0}; // 열
int n;
int ans[25*25];
void dfs(int x,int y,int cnt){
    d[x][y] = cnt;
    for(int k=0;k<4;k++){//상하좌우 탐색
        int nx = x+dx[k];
        int ny = y+dy[k];
        if(0 <= nx && nx < n && 0<= ny && ny < n){//전체 범위를 벗어나지않을때
            if(a[nx][ny] == 1 && d[nx][ny] == 0){//방문한적없는데 집인 경우
                dfs(nx,ny,cnt);
            }
        }
    }
}
int main(){
    scanf("%d",&n);//가로,세로 면적 입력
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%1d",&a[i][j]);//집 위치 입력
        }
    }
    int cnt=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(a[i][j] == 1 && d[i][j] == 0){
                dfs(i,j,++cnt);//방문한적이 없는데, 집이 있는 경우 탐색 + 단지수+1
            }
        }
    }
    printf("%d\n",cnt);//전체 단지 갯수 
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            ans[d[i][j]] += 1;//각 단지의 집 수 세기
        }
    }
    sort(ans+1,ans+cnt+1);//오름차순 정렬
    for(int i=1;i<=cnt;i++){
        printf("%d\n",ans[i]);
    }
    return 0;
}