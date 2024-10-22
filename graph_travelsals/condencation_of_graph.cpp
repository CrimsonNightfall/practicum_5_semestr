#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

class TGraph {
public:
    TGraph(int n, int m) : N(n), M(m), adj(n + 1), adj_rev(n + 1), 
        visited(n + 1, false), component(n + 1, 0), s() {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj_rev[v].push_back(u);
    }

    void findStronglyConnectedComponents() {
        for (int i = 1; i <= N; ++i) {
            if (!visited[i]) {
                DepthFirstSearch(i);
            }
        }

        std::fill(visited.begin(), visited.end(), false);
        int component_count = 0;

        while (!s.empty()) {
            int v = s.top();
            s.pop();
            if (!visited[v]) {
                ++component_count;
                DepthFirstSearchReverse(v, component_count);
            }
        }

        std::vector<int> order(component_count + 1);
        for (int i = 1; i <= N; ++i) {
            order[component[i]]++;
        }

        std::cout << component_count << std::endl;
        for (int i = 1; i <= N; ++i) {
            std::cout << component[i] << " ";
        }
        std::cout << std::endl;
    }

private:
    int N, M;
    std::vector<std::vector<int>> adj, adj_rev;
    std::vector<bool> visited;
    std::vector<int> component;
    std::stack<int> s;

    void DepthFirstSearch(int v) {
        visited[v] = true;
        for (int u : adj[v]) {
            if (!visited[u]) {
                DepthFirstSearch(u);
            }
        }
        s.push(v);
    }

    void DepthFirstSearchReverse(int v, int comp_num) {
        visited[v] = true;
        component[v] = comp_num;
        for (int u : adj_rev[v]) {
            if (!visited[u]) {
                DepthFirstSearchReverse(u, comp_num);
            }
        }
    }
};

int main() {
    int N, M;
    std::cin >> N >> M;
    TGraph graph(N, M);
    for (int i = 0; i < M; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph.addEdge(u, v);
    }
    
    graph.findStronglyConnectedComponents();
    
    return 0;
}