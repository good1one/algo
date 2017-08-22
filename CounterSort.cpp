#include <iostream>
#include <vector>


void counting_sort(std::vector<int>& a, int max_num) {
    std::vector<int> count_v((size_t)(max_num + 1));
    for (int e : a) ++count_v[e];

    int i = 0;
    for (int j = 0; j < (int)count_v.size(); ++j) {
        int ctr = count_v[j];
        while (ctr > 0) {
            a[i] = j;
            ++i; --ctr;
        }
    }
}


int main() {
    std::vector<int> a = {4, 2, 3, 1};
    for (int e : a) std::cout << e << ' ';
    std::cout << '\n';
    counting_sort(a, 100);
    for (int e : a) std::cout << e << ' ';
}

