#include <bits/stdc++.h>
using namespace std;

constexpr auto INF{1000};

auto bfs(const vector<vector<bool>> &g, int s, int e)
{
    vector<bool> vis(g.size());
    queue<pair<int, int>> q;
    q.push(make_pair(s, 0));
    while (not q.empty())
    {
        auto [curr, cost] = q.front();
        q.pop();
        if (curr == e)
            return cost;
        vis[curr] = true;
        for (auto i = 0; i < vis.size(); i++)
        {
            if (g[curr][i] and not vis[i])
                q.push(make_pair(i, cost + 1));
        }
    }
    return -1;
}

void solve()
{
    int s, e, n, m;
    cin >> s >> e >> n >> m;
    vector<vector<bool>> g(INF, vector<bool>(INF));
    for (auto i = 0; i < n; i++)
    {
        int x;
        string s;
        cin >> x >> s;
    }
    for (auto i = 0; i < m; i++)
    {
        int v, w;
        cin >> v >> w;
        g[v][w] = true;
        g[w][v] = true;
    }
    cout << bfs(g, s, e) << '\n';
}

int main()
{
    solve();

    return 0;
}
