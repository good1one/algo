#include <iostream>
#include <vector>


void bubble_sort(std::vector<int>& a) {
    int n = (int)a.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - 1; ++j) {
            if (a[j] > a[j + 1])
                std::swap(a[j], a[j + 1]);
        }
    }
}


int main() {
    std::vector<int> a = {4, 2, 3, 1};
    for (int e : a) std::cout << e << ' ';
    std::cout << '\n';
    bubble_sort(a);
    for (int e : a) std::cout << e << ' ';
}

