#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

enum VertexColor { 
    White, 
    Gray, 
    Black
};

class TGraph {
public:
    TGraph(int n) : AdjList(n), color(n, White) {}

    void AddEdge(int u, int v) {
        AdjList[u - 1].push_back(v - 1);
    }

    bool TopologicalSort(std::vector<int>& result) {
        for (size_t i = 0; i < AdjList.size(); ++i) {
            if (color[i] == White) {
                if (DepthFirstSearch(i, result)) {
                    return false;
                }
            }
        }

        std::reverse(result.begin(), result.end());
        return true;
    }

private:
    std::vector<std::vector<int>> AdjList;
    std::vector<VertexColor> color;

    bool DepthFirstSearch(int vertex, std::vector<int>& result) {
        color[vertex] = Gray;

        for (int neighbor : AdjList[vertex]) {
            if (color[neighbor] == Gray) {
                return true;
            }
            if (color[neighbor] == White) {
                if (DepthFirstSearch(neighbor, result)) {
                    return true;
                }
            }
        }

        color[vertex] = Black;
        result.push_back(vertex + 1);
        return false;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;

    TGraph graph(n);

    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph.AddEdge(a, b);
    }

    std::vector<int> result;

    if (graph.TopologicalSort(result)) {
        std::cout << "Yes" << std::endl;
        for (int soldier : result) {
            std::cout << soldier << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "No" << std::endl;
    }

    return 0;
}