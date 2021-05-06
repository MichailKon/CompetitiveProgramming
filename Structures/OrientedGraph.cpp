#include <bits/stdc++.h>

template<int N>
class graph {
private:
    std::vector<std::pair<int, int>> g[N], gr[N];
    int used[N];
    std::vector<int> order;

    bool haveCycle(int v) {
        used[v] = 1;
        bool ans = 0;
        for (auto &[i, cost] : g[v]) {
            if (!used[i]) {
                ans |= haveCycle(i);
            } else if (used[i] == 1) {
                return true;
            }
        }
        used[v] = 2;
        return ans;
    }

    void dfs(int v, bool addToOrder = false) {
        used[v] = true;
        for (auto &[i, cost] : g[v]) {
            if (!used[v]) {
                dfs(i, addToOrder);
            }
        }
        if (addToOrder) {
            order.push_back(v);
        }
    }

    void go(int v, std::vector<int> &res) {
        res.push_back(v);
        used[v] = true;
        for (auto &i : g[v]) {
            if (!used[i]) {
                go(i, res);
            }
        }
    }

    void rgo(int v, std::vector<int> &res) {
        res.push_back(v);
        used[v] = true;
        for (auto &[i, cost] : gr[v]) {
            if (!used[i]) {
                rgo(i, res);
            }
        }
    }

    void rdfs(int v, bool addToOrder = false) {
        used[v] = true;
        for (auto &[i, cost] : gr[v]) {
            if (!used[i]) {
                rdfs(i, addToOrder);
            }
        }
        if (addToOrder) {
            order.push_back(v);
        }
    }

public:
    graph() {
        for (auto &i : g) {
            i.clear();
        }
    }

    void addEdge(const int &from, const int &to, const int &cost = 1) {
        g[from].emplace_back(to, cost);
        gr[to].emplace_back(from, cost);
    }

    bool haveCycle() {
        memset(used, 0, sizeof(used));
        bool ans = 0;
        for (int i = 0; i < N; i++) {
            if (!used[i]) {
                ans |= haveCycle(i);
            }
        }
        return ans;
    }

    std::vector<std::vector<int>> getSCS() {
        std::vector<std::vector<int>> res;
        order.clear();
        memset(used, 0, sizeof used);
        for (int i = 0; i < N; i++) {
            if (!used[i]) {
                dfs(i, true);
            }
        }
        memset(used, 0, sizeof used);
        for (auto &i : order) {
            if (!used[i]) {
                res.emplace_back();
                rgo(i, res.back());
            }
        }

        return res;
    }

    std::array<long long, N> dijkstra(int v) {
        std::priority_queue<std::pair<long long, int>,
                std::vector<std::pair<long long, int>>,
                std::greater<>> q;
        std::array<long long, N> dist;
        std::fill(dist.begin(), dist.end(), LONG_LONG_MAX);
        memset(used, 0, sizeof(used));
        dist[v] = 0;
        q.push(std::make_pair(0, v));

        while (!q.empty()) {
            auto[d, now] = q.top();
            q.pop();
            d = -d;
            if (used[now]) continue;
            used[now] = true;
            for (auto &[to, cost] : g[now]) {
                if (!used[to] && d + cost < dist[to]) {
                    dist[to] = d + cost;
                    q.push(std::make_pair(-dist[to], to));
                }
            }
        }

        return dist;
    }

    std::array<std::array<long long, N>, N> floyd() {
        std::array<std::array<long long, N>, N> ans;
        for (auto &i : ans) {
            for (auto &j : i) {
                j = LONG_LONG_MAX;
            }
        }

        for(int i = 0; i < N; i++) ans[i][i] = 0;
        for (int i = 0; i < N; i++) {
            for (auto &[to, cost] : g[i]) {
                ans[i][to] = std::min(ans[i][to], (long long) cost);
            }
        }

        for (int k = 0; k < N; k++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (ans[i][k] != LONG_LONG_MAX && ans[k][j] != LONG_LONG_MAX) {
                        ans[i][j] = std::min(ans[i][j], ans[i][k] + ans[k][j]);
                    }
                }
            }
        }

        return ans;
    }
};

int main() {
    graph<4> g;
    g.addEdge(0, 1, 2);
    g.addEdge(1, 2, 100);
    g.addEdge(2, 3, 1);
    g.addEdge(3, 1, 80);

    std::cout << g.haveCycle() << '\n';
    std::cout << '\n';

    for (auto &i : g.getSCS()) {
        for (auto &j : i) {
            std::cout << j << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';

    for (auto &i : g.dijkstra(0)) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
    std::cout << '\n';

    auto res = g.floyd();
    for (auto &i : res) {
        for (auto &j : i) {
            std::cout << j << ' ';
        }
        std::cout << '\n';
    }
}
