#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>

class GraphNode {
public:
    bool visited = false;
    int building = -1, map = -1;
    std::vector<std::pair<GraphNode*, bool>> neighbors;

    GraphNode(int b, int m) : building(b), map(m), neighbors() {}
};

class Graph {
private:
    int buildings, maps;
    std::vector<std::vector<GraphNode>> nodes;
    std::vector<std::unordered_set<int>> availableMaps;
    std::vector<int> distances;

    int index(int building, int map) {
        return building * (maps + 1) + map;
    }

    GraphNode& getNode(int building, int map) {
        return nodes[building][map];
    }

public:
    Graph(int n, int k) : buildings(n), maps(k), 
                          nodes(n, std::vector<GraphNode>(k + 1, {-1, -1})), 
                          availableMaps(n), 
                          distances(n * (k + 1), 1'000'000) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= k; ++j) {
                nodes[i][j] = GraphNode(i, j);
            }
        }

        for (int i = 0; i < k; ++i) {
            int q;
            std::cin >> q;
            while (q--) {
                int a, b;
                std::cin >> a >> b;
                availableMaps[a - 1].insert(i);
                availableMaps[b - 1].insert(i);
                nodes[a - 1][i].neighbors.push_back({&nodes[b - 1][i], false});
                nodes[b - 1][i].neighbors.push_back({&nodes[a - 1][i], false});
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int m : availableMaps[i]) {
                nodes[i][m].neighbors.push_back({&nodes[i][k], false});
                nodes[i][k].neighbors.push_back({&nodes[i][m], true});
            }
        }
    }

    int bfs(int destinationBuilding, int destinationMap) {
        std::deque<GraphNode*> q;
        distances[index(0, maps)] = 0;
        q.push_back(&nodes[0][maps]);

        while (!q.empty()) {
            GraphNode* cur = q.front();
            q.pop_front();

            if (cur->visited) continue;
            cur->visited = true;

            for (auto& [neighbor, cost] : cur->neighbors) {
                int newDist = distances[index(cur->building, cur->map)] + cost;
                if (newDist < distances[index(neighbor->building, neighbor->map)]) {
                    distances[index(neighbor->building, neighbor->map)] = newDist;
                    if (cost) q.push_back(neighbor);
                    else q.push_front(neighbor);
                }
            }
        }
        return distances[index(destinationBuilding, destinationMap)] == 1'000'000 ? -1 : distances[index(destinationBuilding, destinationMap)];
    }
};

int main() {
    int n, k;
    std::cin >> n >> k;
    Graph graph(n, k);
    std::cout << graph.bfs(n - 1, k) << std::endl;
    return 0;
}