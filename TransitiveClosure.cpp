#include <iostream>
#include <vector>

class Graph {
private:
    size_t sz;
    std::vector<std::vector<bool>> g;
    std::vector<std::vector<bool>> tc;

public:
    Graph() {
        std::cin >> sz;
        g.resize(sz, std::vector<bool>(sz));

        for (int i = 0; i < sz; ++i) {
            for (int j = 0; j < sz; ++j) {
                int  tmp;
                std::cin >> tmp;
                g[i][j] = tmp;
            }
        }
    }

    void TrasitiveClosure()  {
        tc = g;
        for (int k = 0; k < sz; ++k) {
            for (int i = 0; i < sz; ++i) {
                for (int j = 0; j < sz; ++j) {
                    tc[i][j] = tc[i][j] || (tc[i][k] && tc[k][j]);
                }
            }
        }
    }

    void Out() {
        for (int i = 0; i < sz; ++i) {
            for (int j = 0; j < sz; ++j) {
                std::cout << tc[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }
};


int main() {
    Graph a;
    a.TrasitiveClosure();
    a.Out();
}

