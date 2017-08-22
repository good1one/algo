#include <algorithm>
#include <iostream>
#include <vector>


struct Graph {
    std::vector<std::pair<int, std::pair<int, int>>> g;
    size_t sz, m;

    Graph() {
        std::cin >> sz >> m;
        g.resize(sz);

        for (int k = 0; k < m; ++k) {
            int i, j, weight;
            std::cin >> i >> j >> weight;
            g[k] = std::make_pair(weight, std::make_pair(i - 1, j - 1));
        }
    }

    void KruskalsAlgorithm() {
        long sum = 0;

        std::sort(g.begin(), g.end());
        std::vector<int> tree_id(sz);

        for (int i = 0; i < sz; ++i) {
            tree_id[i] = i;
        }

        for (int i = 0; i < m; ++i) {
            int a = g[i].second.first, b = g[i].second.second, weight = g[i].first;
            if (tree_id[a] != tree_id[b]) {
                sum += weight;
                int old_id = tree_id[b], new_id = tree_id[a];
                for (int j = 0; j < sz;  ++j) {
                    if (tree_id[j] == old_id) {
                        tree_id[j] = new_id;
                    }
                }
            }
        }

        std::cout << sum;
    }
};


int main() {
    Graph a;
    a.KruskalsAlgorithm();
}

