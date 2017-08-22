#include <iostream>
#include <queue>
#include <vector>


class Graph {
private:
    size_t sz;
    std::vector<int> used;
    std::vector<int> distance;
    std::vector<int> previous;
    std::vector<std::vector<int>> g;

public:
    Graph() {
        std::cin >> sz;
        Resize(sz);

        for (int i = 0; i < sz; ++i) {
            for (int j = 0; j < sz; ++j) {
                int IsBound;
                std::cin >> IsBound;
                if (IsBound) {
                    g[i].push_back(j);
                }
            }
        }
    }

    void Resize(size_t sz) {
        used.resize(sz);
        distance.resize(sz);
        previous.resize(sz);
        g.resize(sz);
    }

    bool IsEndMarked = false;
    void Bfs(int start, int end) {
        std::queue<int> queue;
        queue.push(start);

        previous[start] = -1;
        used[start] = 1;

        while (!queue.empty()) {
            int v = queue.front();
            if (v == end) IsEndMarked = true;

            queue.pop();
            for (auto to : g[v]) {
                if (!used[to]) {
                    used[to] = true;
                    queue.push(to);
                    distance[to] = distance[v] + 1;
                    previous[to] = v;
                }
            }
        }

        if (IsEndMarked) std::cout << distance[end] << '\n';
    }

    void Out(int v) {
        if (!IsEndMarked) {
            std::cout << -1;
            return;
        }

        if (v != -1) {
            Out(previous[v]);
            std::cout << v + 1 << ' ';
        }
    }
};


int main() {
    Graph a;

    int start, end;
    std::cin >> start >> end;
    --start; --end;

    a.Bfs(start, end);
    a.Out(end);
}

