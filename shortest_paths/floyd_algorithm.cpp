#include <iostream>
#include <vector>
#include <algorithm>

class TGraph {
public:
    TGraph(int n) : N(n), dist(n, std::vector<int>(n)) {}

    void ReadGraph() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                std::cin >> dist[i][j];
            }
        }
    }

    void FloydWarshall() {
        for (int k = 0; k < N; ++k) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    void PrintShortestPaths() const {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                std::cout << dist[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    int N;
    std::vector<std::vector<int>> dist;
};

int main() {
    int N;
    std::cin >> N;

    TGraph graph(N);
    graph.ReadGraph();
    graph.FloydWarshall();
    std::cout << "\n";
    graph.PrintShortestPaths();

    return 0;
}