#include <bits/stdc++.h>
using namespace std;

constexpr auto INF{1000};

auto reconstruct_path(const vector<int> &prev, int e)
{
    vector<pair<int, int>> path;
    for (auto i = e; prev[i] != -1; i = prev[i])
        path.push_back(make_pair(prev[i], i));
    reverse(path.begin(), path.end());
    return path;
}

auto bfs(const vector<vector<bool>> &g, int s, int e)
{
    vector<int> prev(g.size());
    prev[s] = -1;
    vector<bool> vis(g.size());
    vis[s] = true;
    queue<pair<int, int>> q;
    q.push(make_pair(s, 0));
    while (not q.empty())
    {
        auto [curr, cost] = q.front();
        q.pop();
        if (curr == e)
            return reconstruct_path(prev, e);
        for (auto i = 0; i < (int)vis.size(); i++)
        {
            if (g[curr][i] and not vis[i])
            {
                q.push(make_pair(i, cost + 1));
                prev[i] = curr;
                vis[i] = true;
            }
        }
    }

    return vector<pair<int, int>>();
}

void solve()
{
    int s, e, n, m;
    cin >> s >> e >> n >> m;
    vector<vector<bool>> g(INF, vector<bool>(INF));
    vector<string> mp(INF);
    for (auto i = 0; i < n; i++)
    {
        int x;
        string s;
        cin >> x >> s;
        mp[x] = s;
    }
    for (auto i = 0; i < m; i++)
    {
        int v, w;
        cin >> v >> w;
        g[v][w] = true;
        g[w][v] = true;
    }
    auto path = bfs(g, s, e);
    if (!path.size())
        cout << "sem conexao\n";
    else
        cout << path.size() << '\n';
    for (auto [a, b] : path)
        cout << mp[a] << " apertou a mao de " << mp[b] << '\n';
}

int main()
{
    solve();

    return 0;
}
