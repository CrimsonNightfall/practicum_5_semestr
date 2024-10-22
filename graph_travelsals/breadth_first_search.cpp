#include <iostream>
#include <vector>
#include <queue>
#include <limits>

class TGraph {
public:
    TGraph(uint32_t n) : AdjList(n) {}

    void AddEdge(uint32_t u, uint32_t v) {
        AdjList[u - 1].push_back(v - 1);
        AdjList[v - 1].push_back(u - 1);
    }

    std::vector<uint32_t> BreadthFirstSearch(const std::vector<uint32_t>& startVertices) const {
        std::vector<uint32_t> distances(AdjList.size(), std::numeric_limits<uint32_t>::max());
        std::queue<uint32_t> bfsQueue;

        for (uint32_t start : startVertices) {
            distances[start - 1] = 0;
            bfsQueue.push(start - 1);
        }

        while (!bfsQueue.empty()) {
            uint32_t current = bfsQueue.front();
            bfsQueue.pop();

            for (uint32_t neighbor : AdjList[current]) {
                if (distances[neighbor] == std::numeric_limits<uint32_t>::max()) {
                    distances[neighbor] = distances[current] + 1;
                    bfsQueue.push(neighbor);
                }
            }
        }

        return distances;
    }

private:
    std::vector<std::vector<uint32_t>> AdjList;
};

std::vector<uint32_t> ReadExits(std::istream& stream, uint32_t k) {
    std::vector<uint32_t> exits(k);
    for (uint32_t i = 0; i < k; ++i) {
        stream >> exits[i];
    }
    return exits;
}

TGraph ReadGraph(std::istream& stream, uint32_t n, uint32_t m) {
    TGraph graph(n);
    for (uint32_t i = 0; i < m; ++i) {
        uint32_t u, v;
        stream >> u >> v;
        graph.AddEdge(u, v);
    }
    return graph;
}

int main() {
    uint32_t n, k;
    std::cin >> n >> k;
    
    std::vector<uint32_t> exits = ReadExits(std::cin, k);
    
    uint32_t m;
    std::cin >> m;
    
    TGraph graph = ReadGraph(std::cin, n, m);
    
    std::vector<uint32_t> distances = graph.BreadthFirstSearch(exits);
    
    for (const auto& distance : distances) {
        std::cout << distance << " ";
    }

    std::cout << std::endl;
    
    return 0;
}