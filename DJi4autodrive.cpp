#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <stack>
using namespace std;

#define INF 1e9

// Dijkstra�㷨����
void dijkstra(vector<vector<float>>& graph, int start, vector<float>& distances, vector<int>& prenode) {
    int n = graph.size();
    vector<bool> visited(n, false); // ��¼�ڵ��Ƿ񱻷��ʹ�
    distances.assign(n, INF); // ��ʼ����������
    distances[start] = 0; // ��ʼ�ڵ㵽����ľ���Ϊ0
    prenode.assign(n, -1);
    // ʹ�����ȶ���ʵ�ֶ��Ż�,�洢�ڵ��ź;���
    priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> pq;
    pq.push({0, start});
    // ��ʼ����
    while (!pq.empty()) {
        float dist_u = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // �����ǰ�ڵ�ľ����Ѿ����ڼ�¼����̾���,�����
        if (dist_u > distances[u]) {
            continue;
        }

        // ���ýڵ���Ϊ�ѷ���
        visited[u] = true;

        // ��������δ���ʽڵ�ľ���
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
    // ʾ��ͼ���ڽӾ����ʾ
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

    int start = 7; // ��ʼ�ڵ���
    int end = 1; // �����ڵ���
    stack<int> s; // ���ڽ�����ǰ���㵹��
    vector<float> distances; // �洢��̾��������
    vector<int> prenode; // �洢ÿ���ڵ��ǰ���ڵ�
    // ����Dijkstra�㷨�������·��
    dijkstra(graph, start, distances, prenode);

    // ������
    cout << "Shortest distances from node " << start << " to other nodes:" << endl;
    for (int i = 0; i < distances.size(); ++i) {
        cout << "To node " << i << ": " << distances[i] << endl;
    }
    int k = end;//����·��
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
