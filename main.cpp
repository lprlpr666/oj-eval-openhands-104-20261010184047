#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    if(!(cin >> n >> m)) return 0;
    vector<vector<int>> grid(m, vector<int>(n));
    pair<int,int> start{-1,-1}, home{-1,-1};
    vector<pair<int,int>> umbrellas;
    for(int i=0;i<m;++i){
        for(int j=0;j<n;++j){
            cin >> grid[i][j];
            if(grid[i][j]==2) start={i,j};
            else if(grid[i][j]==3) home={i,j};
            else if(grid[i][j]==4) umbrellas.emplace_back(i,j);
        }
    }
    const int INF = 1e9;
    auto bfs = [&](pair<int,int> src){
        vector<vector<int>> dist(m, vector<int>(n, INF));
        queue<pair<int,int>> q;
        if(grid[src.first][src.second]==1) return dist; // blocked
        dist[src.first][src.second]=0;
        q.push(src);
        int dirs[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
        while(!q.empty()){
            auto cur = q.front(); q.pop();
            int x = cur.first;
            int y = cur.second;
            for(auto &d:dirs){
                int nx=x+d[0], ny=y+d[1];
                if(nx<0||nx>=m||ny<0||ny>=n) continue;
                if(grid[nx][ny]==1) continue; // blocked
                if(dist[nx][ny]==INF){
                    dist[nx][ny]=dist[x][y]+1;
                    q.emplace(nx,ny);
                }
            }
        }
        return dist;
    };
    auto dist_start = bfs(start);
    auto dist_home = bfs(home);
    int ans = INF;
    for(auto &u: umbrellas){
        int d1 = dist_start[u.first][u.second];
        int d2 = dist_home[u.first][u.second];
        if(d1!=INF && d2!=INF) ans = min(ans, d1+d2);
    }
    if(ans==INF) cout << -1 << "\n"; // unreachable
    else cout << ans << "\n";
    return 0;
}
