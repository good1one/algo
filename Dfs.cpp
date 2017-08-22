#include <algorithm>
#include <iostream>
#include <vector>


class Graph {
private:
    size_t sz;
    size_t component_sz = 0;
    std::vector<int> used;
    std::vector<std::vector<int>> g;

public:
    Graph() {
        int m;
        std::cin >> sz >> m;

        used.resize((size_t)sz);
        g.resize((size_t)sz);

        for (int i = 0; i < m; ++i) {
            int lhs, rhs;
            std::cin >> lhs >> rhs;
            --lhs; --rhs;

            g[lhs].push_back(rhs);
            g[rhs].push_back(lhs);
        }
    }

    void Dfs(int v) {
        if (used[v]) return;
        used[v] = 1;
        ++component_sz;

        for (auto e : g[v]) {
            Bfs(e);
        }
        return;
    }

    void Out() {
        std::cout << component_sz << '\n';
        for (int i = 0; i < sz; ++i) {
            if (used[i]) std::cout << i + 1 << ' ';
        }
    }
};

int main() {
    Graph a;
    a.Dfs(0);
    a.Out();
}

