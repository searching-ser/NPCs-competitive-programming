// Requires 0 <= start < graph.size(). -1 means unreachable.
// O(V + E) time and O(V) auxiliary memory.
vector<int> bfs_distances(const vector<vector<int>>& graph, int start) {
  vector<int> distance(graph.size(), -1);
  queue<int> pending;
  distance[start] = 0;
  pending.push(start);

  while (!pending.empty()) {
    int node = pending.front();
    pending.pop();
    for (int neighbor : graph[node]) {
      if (distance[neighbor] != -1) continue;
      distance[neighbor] = distance[node] + 1;
      pending.push(neighbor);
    }
  }
  return distance;
}
