#include <iostream>
#include <vector>


void quick_sort(std::vector<int>& a, int l, int r) {
    int i = l, j = r;
    int pivot = a[i + rand() % (j + 1 - i)];

    while (i <= j) {
        while (a[i] < pivot) i++;
        while (a[j] > pivot) j--;

        if (i <= j) {
            std::swap(a[i], a[j]);
            i++; j--;
        }
    }

    if (i < r) quick_sort(a, i, r);
    if (l < j) quick_sort(a, l, j);
}


int main() {
    std::vector<int> a = {4, 2, 3, 1};
    for (int e : a) std::cout << e << ' ';
    std::cout << '\n';
    quick_sort(a, 0, int(a.size() - 1));
    for (int e : a) std::cout << e << ' ';
}

