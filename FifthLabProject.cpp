#include <iostream>
#include <vector>
using namespace std;

enum EdgeType { TREE, BACK, FORWARD, CROSS };

class Graph {
public:
    int time = 0;
    int v;
    vector<vector<int>> graph_list;
    vector<bool> visited;
    vector<int> start_time;
    vector<int> end_time;

    Graph(int vertices) : v(vertices) {
        graph_list.resize(v);
        visited.resize(v, false);
        start_time.resize(v, 0);
        end_time.resize(v, 0);
    }

    void insert_edge(int u, int v) {
        graph_list[u - 1].push_back(v - 1); 
    }

    void displayGraph() {
        for (int i = 0; i < v; i++) {
            cout << i + 1 << "--->";
            for (int j = 0; j < graph_list[i].size(); j++) {
                cout << graph_list[i][j] + 1 << " "; 
            }
            cout << endl;
        }
        cout << endl;
    }

   void DFS() 
   {
    int start_node = 0; 

    if (!visited[start_node]) {
        traverse_dfs(start_node, -1); 
    }

    for (int node = 1; node < v; ++node) {
        if (!visited[node]) {
            traverse_dfs(node, -1); 
        }
    }
}

void traverse_dfs(int node, int parent) 
{
    visited[node] = true;
    start_time[node] = time;
    time++;

    for (int neighbor : graph_list[node]) {
        if (!visited[neighbor]) {
            cout << "Tree Edge: " << node + 1 << "-->" << neighbor + 1 << endl;
            traverse_dfs(neighbor, node);
        } else {
            if (start_time[node] > start_time[neighbor] && end_time[neighbor] == 0) {
                cout << "Back  Edge: " << node + 1 << "-->" << neighbor + 1 << endl;
            } else if (start_time[node] < start_time[neighbor] && end_time[neighbor] != 0 && neighbor != parent) {
                cout << "Forward Edge " << node + 1 << "-->" << neighbor + 1 << endl;
            } else if (start_time[node] > start_time[neighbor] && end_time[node] < end_time[neighbor]) {
                cout << "Cross Edge: " << node + 1 << "-->" << neighbor + 1 << endl;
            }
        }
    }

    end_time[node] = time;
    time++;
}

};

int main() {
    int v = 9;
    Graph g(v);

    g.insert_edge(1, 2);
    g.insert_edge(1, 5);
    g.insert_edge(2, 3);
    g.insert_edge(2, 4);
    g.insert_edge(5, 6);
    g.insert_edge(5, 7);
    g.insert_edge(5, 9);
    g.insert_edge(6, 4);
    g.insert_edge(7, 8);
    g.insert_edge(7, 9);
    g.insert_edge(8, 5);

    g.displayGraph(); 

    cout << "DFS Edge Classification:" << endl;
    g.DFS();

    return 0;
}
