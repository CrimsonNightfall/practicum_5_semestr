#include <iostream>
#include <vector>
#include <queue>
#include <limits>

const long long INF = std::numeric_limits<long long>::max();

struct Edge {
    int to;
    long long weight;
};

class Graph {
public:
    Graph(int n) : adj(n) {}

    void addEdge(int from, int to, long long weight) {
        adj[from - 1].push_back({to - 1, weight});
        adj[to - 1].push_back({from - 1, weight});
    }

    long long dijkstra(int start, int end) {
        std::vector<long long> dist(adj.size(), INF);
        std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<std::pair<long long, int>>> pq;

        dist[start - 1] = 0;
        pq.push({0, start - 1});

        while (!pq.empty()) {
            long long currentDist = pq.top().first;
            int currentNode = pq.top().second;
            pq.pop();

            if (currentDist > dist[currentNode]) continue;

            for (const Edge& edge : adj[currentNode]) {
                long long newDist = currentDist + edge.weight;
                if (newDist < dist[edge.to]) {
                    dist[edge.to] = newDist;
                    pq.push({newDist, edge.to});
                }
            }
        }

        return dist[end - 1] == INF ? -1 : dist[end - 1];
    }

private:
    std::vector<std::vector<Edge>> adj;
};

int main() {
    int N, K;
    std::cin >> N >> K;

    Graph graph(N);

    for (int i = 0; i < K; ++i) {
        int a, b;
        long long l;
        std::cin >> a >> b >> l;
        graph.addEdge(a, b, l);
    }

    int A, B;
    std::cin >> A >> B;

    long long result = graph.dijkstra(A, B);
    std::cout << result << std::endl;

    return 0;
}