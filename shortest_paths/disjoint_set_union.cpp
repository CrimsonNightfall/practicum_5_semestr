#include <iostream>
#include <vector>

class TDisjointSetUnion {
private:
    mutable std::vector<int> parents;
    std::vector<int> size;
    size_t components;

public:
    TDisjointSetUnion(size_t n) : parents(n), size(n, 1), components(n) {
        for (size_t i = 0; i < n; ++i) {
            parents[i] = i;
        }
    }

    int FindSet(int element) const {
        if (element == parents[element]) {
            return element;
        }
        return parents[element] = FindSet(parents[element]);
    }

    bool UnionSets(int left, int right) {
        left = FindSet(left);
        right = FindSet(right);
        if (left != right) {
            if (size[left] < size[right]) {
                parents[left] = right;
                size[right] += size[left];
            } else {
                parents[right] = left;
                size[left] += size[right];
            }
            --components;
        }
        return components == 1;
    }
};

int main() {
    size_t n, m;
    std::cin >> n >> m;
    TDisjointSetUnion Union(n);
    std::vector<std::pair<int, int>> bridges(m); 
    for (size_t i = 0; i < m; ++i) { 
        std::cin >> bridges[i].first >> bridges[i].second; 
    }
    for (size_t i = 0; i < m; ++i) {
        int a = bridges[i].first; 
        int b = bridges[i].second;
        if (Union.UnionSets(a, b)) {
            std::cout << i + 1 << std::endl;
            return 0;
        }
    }
    return 0;
}