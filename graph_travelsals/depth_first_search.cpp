#include <iostream>
#include <vector>

class TGraph {
private:
    std::vector<std::vector<uint32_t>> AdjList;

    void DepthFirstSearch(std::vector<bool> &visited, uint32_t current) const {
        if (visited[current]) {
            return;
        }
        visited[current] = true;
        for (uint32_t neighbor : AdjList[current]) {
            DepthFirstSearch(visited, neighbor);
        }
    }

public:
    explicit TGraph(size_t n) : AdjList(n) {
    }

    void ReadFromStream(std::istream &in) {
        int isPathAvailable;
        for (size_t i = 0; i < AdjList.size(); ++i) {
            for (size_t j = 0; j < AdjList.size(); ++j) {
                in >> isPathAvailable;
                if (isPathAvailable) {
                    AdjList[i].push_back(j);
                }
            }
        }
    }

    uint32_t CountConnectedComponent(uint32_t vertex) const {
        std::vector<bool> visited(AdjList.size(), false);
        DepthFirstSearch(visited, vertex);

        uint32_t count = 0;
        for (bool v : visited) {
            if (v) {
                count++;
            }
        }
        return count;
    }
};

int main() {
    int n, s;
    std::cin >> n >> s;
    TGraph g(n);
    g.ReadFromStream(std::cin);
    std::cout << g.CountConnectedComponent(s - 1) << std::endl;
    return 0;
}