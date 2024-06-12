#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>
#include <algorithm>
#include <unordered_map>
#include <chrono>
using namespace std;

#define INF 1e9

// A*�㷨����
vector<int> AStar(vector<vector<float>>& graph, int start, int end, vector<vector<float>> estimate) {
    int n = graph.size();

    // ������ʼ�ڵ㵽Ŀ��ڵ�Ĺ��ƴ��ۣ�����򵥵�ʹ�ýڵ��ŵĲ�ֵ��Ϊ���ƴ��ۣ�
    auto heuristic = [&](int node) {
        return estimate[node][end];
    };

    // ʹ�����ȶ���ʵ�ֶ��Ż����洢�ڵ�Ͷ�Ӧ��fֵ��gֵ+���ƴ��ۣ�
    priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> pq;
    pq.push({0, start});

    // ʹ�ù�ϣ���¼ÿ���ڵ�ĸ��ڵ㣬�������ջ��ݵõ����·��
    unordered_map<int, int> parent;
    parent[start] = -1;

    // ��ʼ����������
    vector<float> g(n, INF);
    g[start] = 0;

    // ��ʼ����
    while (!pq.empty()) {
        int f = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // �����ǰ�ڵ���Ŀ��ڵ㣬���������
        if (u == end) {
            break;
        }

        // ������ǰ�ڵ�������ھӽڵ�
        for (int v = 0; v < n; ++v) {
            if (graph[u][v] != INF) {
                // �����ھӽڵ��ʵ�ʴ���
                int cost = graph[u][v];
                int new_g = g[u] + cost;

                // ����ھӽڵ�û�б����ʹ������µ�ʵ�ʴ��۸�С���������Ϣ���������ȶ���
                if (new_g < g[v]) {
                    g[v] = new_g;
                    parent[v] = u;
                    int h = heuristic(v);
                    pq.push({new_g + h, v});
                }
            }
        }
    }

    // ���ݵõ����·��
    vector<int> shortestPath;
    int current = end;
    while (current != -1) {
        shortestPath.push_back(current);
        current = parent[current];
    }
    reverse(shortestPath.begin(), shortestPath.end());

    return shortestPath;
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
    vector<vector<float>> estimate = {
        {0, 143.7, 258.0, 47.3, 86, 78.2, 116.5, 191.4, 108.8, 218.7, 201.2, 199.6, 116.5, 104.2},
        {143.7, 0, 224.5, 93.7, 180.7, 122.8, 203.1, 275.2, 138.7, 134.0, 220, 64.5, 220.6, 74.5},
        {258.0, 224.5, 0, 225.3, 326.4, 303.7, 158.2, 209.9, 150.2, 131.7, 92.4, 265.6, 215.5, 175},
        {47.3, 93.7, 225.3, 0, 107.9, 81.3, 137.8, 201.6, 86.1, 174.4, 184.5, 159.2, 138.6, 57.4},
        {86, 180.7, 326.4, 107.9, 0, 66.9, 205.7, 246.4, 177.6, 278.6, 268.8, 221.8, 175.7, 160.6},
        {78.2, 122.8, 303.7, 81.3, 66.9, 0, 214.7, 270.1, 168.4, 240.8, 265.9, 163.2, 200.9, 131.1},
        {116.5, 203.1, 158.2, 137.8, 205.7, 214.7, 0, 77.5, 61.7, 178.1, 73.4, 268.2, 57.3, 126.3},
        {191.4, 275.2, 209.9, 201.6, 246.4, 270.1, 77.5, 0, 139.6, 252.6, 118.6, 344.4, 70.1, 204.0},
        {108.8, 138.7, 150.2, 86.1, 177.6, 168.4, 61.7, 139.6, 0, 134.9, 96.4, 204.9, 95.5, 66.4},
        {218.7, 134.0, 131.7, 174.4, 278.6, 240.8, 178.1, 252.6, 134.9, 0, 149.2, 165.2, 227.6, 117.5},
        {201.2, 220, 92.4, 184.5, 268.8, 265.9, 73.4, 118.6, 96.4, 149.2, 0, 278.5, 130.4, 149.8},
        {199.6, 64.5, 265.6, 159.2, 221.8, 163.2, 268.2, 344.4, 204.9, 165.2, 278.5, 0, 288.3, 141.5},
        {116.5, 220.6, 215.5, 138.6, 175.7, 200.9, 57.3, 70.1, 95.5, 227.6, 130.4, 288.3, 0, 150.3},
        {104.2, 74.5, 175, 57.4, 160.6, 131.1, 126.3, 204.0, 66.4, 117.5, 149.8, 141.5, 150.3, 0},
    };
    
    int start = 7; // ��ʼ�ڵ���
    int end = 1; // �����ڵ���
    // ����A*�㷨�������·��
    vector<int> shortestPath = AStar(graph, start, end, estimate);
    // ������·��
    cout << "Shortest path from node " << start+1 << " to node " << end+1 << ": ";
    for (int i = 0; i < shortestPath.size() - 1; i++) {
        cout << shortestPath[i]+1 << " -> ";
    }
    cout << shortestPath.back()+1 << endl;

    return 0;
}