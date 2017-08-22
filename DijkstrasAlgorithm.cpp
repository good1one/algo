#include <iostream>
#include <set>
#include <vector>


#define inf 1e12


class Graph {
private:
    size_t sz;
    std::vector<long int> dist;
    std::vector<std::vector<std::pair<long int, long int>>> g;

public:
    Graph() {
        int m;
        std::cin >> sz >> m;

        g.resize(sz);
        for (long int i = 0; i < m; ++i) {
            long int from, to, dist;
            std::cin >> from >> to >> dist;

            g[from - 1].push_back(std::make_pair(dist, to - 1));
            g[to - 1].push_back(std::make_pair(dist, from - 1));
        }
    }

    void dijkstra_algorihm(long int start, long int end) {
        size_t n = g.size();

        dist.resize(n, (long int)inf);
        dist[start] = 0;

        std::set<std::pair<long int, long int>> queue;
        queue.insert(std::make_pair(dist[start], start));

        while (!queue.empty()) {
            long int v = queue.begin()->second;
            queue.erase(queue.begin());

            for (auto next : g[v]) {
                long int to = next.second, len = next.first;

                if (dist[v] + len < dist[to]) {
                    queue.erase(std::make_pair(dist[to], to));
                    dist[to] = dist[v] + len;
                    queue.insert(std::make_pair(dist[to], to));
                }
            }
        }

        if (dist[end] != inf) {
            std::cout << dist[end];
        } else {
            std::cout << -1;
        }
    }


};



int main() {
    Graph a;

    long int start, end;
    std::cin >> start >> end;
    a.dijkstra_algorihm(start - 1, end - 1);
}

