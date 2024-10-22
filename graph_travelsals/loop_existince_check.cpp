#include <iostream>
#include <vector>

enum VertexColor { 
    White, 
    Gray, 
    Black
};

class TGraph {
public:
    TGraph(uint32_t n) : AdjMatrix(n, std::vector<uint32_t>(n)), color(n, White) {}

    void SetEdge(uint32_t u, uint32_t v) {
        AdjMatrix[u][v] = 1;
    }

    bool HasCycle() {
        for (uint32_t i = 0; i < AdjMatrix.size(); ++i) {
            if (color[i] == White) {
                if (DepthFirstSearch(i)) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    std::vector<std::vector<uint32_t>> AdjMatrix;
    std::vector<VertexColor> color;

    bool DepthFirstSearch(uint32_t vertex) {
        color[vertex] = Gray;

        for (uint32_t neighbor = 0; neighbor < AdjMatrix.size(); ++neighbor) {
            if (AdjMatrix[vertex][neighbor] == 1) {
                if (color[neighbor] == Gray) {
                    return true;
                }
                if (color[neighbor] == White) {
                    if (DepthFirstSearch(neighbor)) {
                        return true;
                    }
                }
            }
        }

        color[vertex] = Black;
        return false;
    }
};

int main() {
    uint32_t n;
    std::cin >> n;

    TGraph graph(n);

    for (uint32_t i = 0; i < n; ++i) {
        for (uint32_t j = 0; j < n; ++j) {
            uint32_t edge;
            std::cin >> edge;
            if (edge == 1) {
                graph.SetEdge(i, j);
            }
        }
    }

    std::cout << (graph.HasCycle() ? 1 : 0) << std::endl;

    return 0;
}