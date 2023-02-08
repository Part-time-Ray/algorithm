#include <bits/stdc++.h>
#define N 1000
#define INF 2147483647
using namespace std;
struct flow{
private:
    int map[N][N]={0};
    int max_flow; // answer
    int find_path(int src, int tar) {
        queue<int> bfs_queue;
        int bfs_last[N], bfs_min[N];
        int bfs_visit[N] = {0};
        
        bfs_min[src] = INF;
        bfs_last[src] = -1;
        bfs_queue.push(src);
        bfs_visit[src] = 1;
        
        bool have_ans = false;
        while(bfs_queue.size()) {
            int start = bfs_queue.front();
            bfs_queue.pop();
            if(start==tar) {have_ans=true; break;}
            for(int i=0 ; i<N ; i++) {
                if(map[start][i]!=0 && bfs_visit[i]==0) {
                    bfs_min[i] = min(bfs_min[start], map[start][i]);
                    bfs_last[i] = start;
                    bfs_queue.push(i);
                    bfs_visit[i]=1;
                }
            }
        }
        if(!have_ans) return 0;
        int cur = tar;
        int find_path_flow = bfs_min[tar];
        while(cur!=-1) {
            map[bfs_last[cur]][cur] -= find_path_flow;
            map[cur][bfs_last[cur]] += find_path_flow;
            cur = bfs_last[cur];
        }
        return find_path_flow;
    }
public:
    // "from" to "to" have a capacity
    void input(int from, int to, int capacity) {
        if(from<N && from>=0 && to<N && to>=0)
            map[from][to] += capacity;
    }
    // get the answer of max_flow
    int solve(int src, int tar) {
        if(src>=N || src<0 || tar>=N || tar<0) return -1;
        max_flow = 0;
        int new_flow=1;
        while(new_flow!=0) {
            new_flow = find_path(src, tar);
            max_flow+=new_flow;
        }
        return max_flow;
    }
};
