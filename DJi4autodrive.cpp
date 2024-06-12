#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <stack>
using namespace std;

#define INF 1e9

// Dijkstra算法函数
void dijkstra(vector<vector<float>>& graph, int start, vector<float>& distances, vector<int>& prenode) {
    int n = graph.size();
    vector<bool> visited(n, false); // 记录节点是否被访问过
    distances.assign(n, INF); // 初始化距离数组
    distances[start] = 0; // 起始节点到自身的距离为0
    prenode.assign(n, -1);
    // 使用优先队列实现堆优化,存储节点编号和距离
    priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> pq;
    pq.push({0, start});
    // 开始迭代
    while (!pq.empty()) {
        float dist_u = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // 如果当前节点的距离已经大于记录的最短距离,则忽略
        if (dist_u > distances[u]) {
            continue;
        }

        // 将该节点标记为已访问
        visited[u] = true;

        // 更新所有未访问节点的距离
        for (int v = 0; v < n; ++v) {
            if (!visited[v] && graph[u][v] != INF) {
                if (distances[u] + graph[u][v] < distances[v]) {
                    distances[v] = distances[u] + graph[u][v];
                    prenode[v] = u;
                    pq.push({distances[v], v}); 
                }
            }
        }
    }
}

int main() {
    // 示例图的邻接矩阵表示
    vector<vector<float>> graph = {
        {0, INF, INF, 55.5, 87.9, 83.6, INF, INF, 148.3, INF, INF, INF, 137.0, INF},
        {INF, 0, INF, 119.8, INF, INF, INF, INF, INF, 174.0, INF, 85.8, INF, INF},
        {INF, INF, 0, INF, INF, INF, INF, INF, INF, 131.7, 122.9, INF, INF, INF},
        {55.5, 119.8, INF, 0, INF, INF, INF, INF, INF, INF, INF, INF, INF, 93.6},
        {87.9, INF, INF, INF, 0, 94.8, INF, INF, INF, INF, INF, INF, INF, INF},
        {83.6, INF, INF, INF, 94.8, 0, INF, INF, INF, INF, INF, INF, INF, INF},
        {INF, INF, INF, INF, INF, INF, 0, 90.7, 76.5, INF, 116.8, INF, INF, INF},
        {INF, INF, INF, INF, INF, INF, 90.7, 0, INF, INF, INF, INF, 88.9, INF},
        {148.3, INF, INF, INF, INF, INF, 76.5, INF, 0, 185.1, INF, INF, INF, 71.5},
        {INF, 174.0, 131.7, INF, INF, INF, INF, INF, 185.1, 0, INF, INF, INF, 146.1},
        {INF, INF, 122.9, INF, INF, INF, 116.8, INF, INF, INF, 0, INF, INF, INF},
        {INF, 85.8, INF, INF, INF, INF, INF, INF, INF, INF, INF, 0, INF, INF},
        {137.0, INF, INF, INF, INF, INF, INF, 88.9, INF, INF, INF, INF, 0, INF},
        {INF, INF, INF, 93.6, INF, INF, INF, INF, 71.5, 146.1, INF, INF, INF, 0},
    };

    int start = 7; // 起始节点编号
    int end = 1; // 结束节点编号
    stack<int> s; // 用于将回溯前驱点倒序
    vector<float> distances; // 存储最短距离的数组
    vector<int> prenode; // 存储每个节点的前驱节点
    // 调用Dijkstra算法计算最短路径
    dijkstra(graph, start, distances, prenode);

    // 输出结果
    cout << "Shortest distances from node " << start << " to other nodes:" << endl;
    for (int i = 0; i < distances.size(); ++i) {
        cout << "To node " << i << ": " << distances[i] << endl;
    }
    int k = end;//回溯路径
    cout << "Shortest route from start to end is: " << endl;
    while (k != -1)
    {
        k = prenode[k]; 
        if(k != -1) s.push(k+1);
    }
    while (!s.empty())
    {
        cout << s.top() << " -> ";
        s.pop();
    }
    cout << end+1;
    return 0;
}
