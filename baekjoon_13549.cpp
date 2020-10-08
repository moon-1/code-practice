#include <iostream>
#include <queue>
#include <deque>
using namespace std;
bool c[1000000];
int d[1000000];
int MAX = 1000000;
int main() {
    int n, m;
    cin >> n >> m;
    c[n] = true;
    d[n] = 0;
    deque<int> q;
    q.push_back(n);
    while (!q.empty()) {
        int now = q.front();
        q.pop_front();
        if (now*2 < MAX) {
            if (c[now*2] == false) {
                q.push_front(now*2);
                c[now*2] = true;
                d[now*2] = d[now];
            }
        }
        if (now-1 >= 0) {
            if (c[now-1] == false) {
                q.push_back(now-1);
                c[now-1] = true;
                d[now-1] = d[now] + 1;
            }
        }
        if (now+1 < MAX) {
            if (c[now+1] == false) {
                q.push_back(now+1);
                c[now+1] = true;
                d[now+1] = d[now] + 1;
            }
        }
    }
    cout << d[m] << '\n';
    return 0;
}