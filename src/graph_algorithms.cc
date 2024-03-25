#include "graph_algorithms.h"

std::vector<int> GraphAlgorithms::DepthFirstSearch(Graph &graph,
                                                   int start_vertex) {
  int size = (int)graph.GetNumOfVertices();
  std::vector<bool> visited(size, false);
  std::vector<int> result;
  my::stack<int> stack;

  result.reserve(100);
  --start_vertex;
  if (start_vertex < 0 || start_vertex > size) {
    throw std::out_of_range("start_vertex out of range");
  }

  stack.push(start_vertex);

  while (!stack.empty()) {
    int current_vertex = stack.top();
    stack.pop();
    if (!visited[current_vertex]) {
      visited[current_vertex] = true;
      result.push_back(current_vertex + 1);
    }
    for (int neighbor = size - 1; neighbor >= 0; --neighbor) {
      if (graph.GetMatrix()[current_vertex][neighbor] != 0 &&
          !visited[neighbor]) {
        stack.push(neighbor);
      }
    }
  }
  result.shrink_to_fit();
  return result;
}

std::vector<int> GraphAlgorithms::BreadthFirstSearch(Graph &graph,
                                                     int start_vertex) {
  int size = (int)graph.GetNumOfVertices();
  std::vector<bool> visited(size, false);
  std::vector<int> result;
  my::queue<int> queue;

  result.reserve(100);
  --start_vertex;
  if (start_vertex < 0 || start_vertex > size) {
    throw std::out_of_range("start_vertex out of range");
  }

  queue.push(start_vertex);
  visited[start_vertex] = true;

  while (!queue.empty()) {
    int current_vertex = queue.front();
    result.push_back(current_vertex + 1);
    queue.pop();

    for (int neighbor = 0; neighbor < size; ++neighbor) {
      if (graph.GetMatrix()[current_vertex][neighbor] != 0 &&
          !visited[neighbor]) {
        queue.push(neighbor);
        visited[neighbor] = true;
      }
    }
  }
  result.shrink_to_fit();
  return result;
}

unsigned GraphAlgorithms::GetShortestPathBetweenVertices(Graph &graph,
                                                         int vertex1,
                                                         int vertex2) {
  const auto &adjacencyMatrix = graph.GetMatrix();
  unsigned int numVertices = graph.GetNumOfVertices();
  std::vector<bool> visit(numVertices, false);
  std::vector<unsigned> distance(numVertices, INF);
  unsigned minIndex = 0;

  distance[vertex1 - 1] = 0;
  do {
    unsigned minWeight = FindMinWeght(distance, visit, minIndex);

    if (minIndex != INF) {
      FindDistances(distance, adjacencyMatrix, minIndex, minWeight);
      visit[minIndex] = true;
    }
  } while (minIndex < INF);

  return distance[vertex2 - 1];
}

std::vector<std::vector<int>>
GraphAlgorithms::GetShortestPathsBetweenAllVertices(const Graph &graph) {
  unsigned size = graph.GetNumOfVertices();
  std::vector<std::vector<int>> shortPaths(size, std::vector<int>(size, INF));
  InitializeShortPathsMatrix(graph.GetMatrix(), shortPaths);

  for (size_t k = 0; k < size; ++k) {
    for (size_t i = 0; i < size; ++i) {
      for (size_t j = 0; j < size; ++j) {
        if (shortPaths[i][k] < INF && shortPaths[k][j] < INF) {
          shortPaths[i][j] =
              std::min(shortPaths[i][j], shortPaths[i][k] + shortPaths[k][j]);
        }
      }
    }
  }
  return shortPaths;
}

std::vector<std::vector<int>> GraphAlgorithms::GetLeastSpanningTree(
    const Graph &graph) {
  unsigned size = graph.GetNumOfVertices();
  auto adjacencyMatrix = graph.GetMatrix();
  std::vector<std::vector<int>> spanningTree(size, std::vector<int>(size));
  std::vector<bool> visit(size, false);
  std::vector<int> minWeght(size, INF);
  std::vector<int> parent(size, -1);

  MarkExtraVertices(adjacencyMatrix);
  minWeght[0] = 0;

  for (size_t i = 0; i < size - 1; ++i) {
    int minWeiVer = -1;
    for (size_t j = 0; j < size; ++j)
      if (!visit[j] && (minWeiVer == -1 || minWeght[j] < minWeght[minWeiVer]))
        minWeiVer = j;

    visit[minWeiVer] = true;

    for (size_t j = 0; j < size; ++j)
      if (!visit[j] && adjacencyMatrix[minWeiVer][j] < minWeght[j]) {
        minWeght[j] = adjacencyMatrix[minWeiVer][j];
        parent[j] = minWeiVer;
      }
  }

  for (size_t i = 1; i < size; ++i) {
    spanningTree[i][parent[i]] = minWeght[i];
    spanningTree[parent[i]][i] = minWeght[i];
  }

  return spanningTree;
}

TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(Graph &graph) {
  AntFarm antfarm(graph);
  if (!antfarm.Run()) throw "Route not found!";
  return antfarm.GetTsmResult();
}

unsigned GraphAlgorithms::FindMinWeght(const std::vector<unsigned> &distance,
                                       const std::vector<bool> &visit,
                                       unsigned &minIndex) {
  unsigned minWeight = minIndex = INF;

  for (size_t i = 0; i < distance.size(); ++i)
    if (!visit[i] && distance[i] < INF) {
      minIndex = i;
      minWeight = distance[i];
    }

  return minWeight;
}

void GraphAlgorithms::FindDistances(std::vector<unsigned> &distance,
                                    const Graph::Matrix &adjacencyMatrix,
                                    unsigned row, unsigned weight) {
  auto compare = [&](unsigned v1, unsigned v2) { return std::min(v1, v2); };
  for (size_t i = 0; i < distance.size(); ++i) {
    if (adjacencyMatrix[row][i]) {
      distance[i] = compare(distance[i], weight + adjacencyMatrix[row][i]);
    }
  }
}

void GraphAlgorithms::InitializeShortPathsMatrix(
    std::vector<std::vector<int>> src, std::vector<std::vector<int>> &dst) {
  for (size_t i = 0; i < src.size(); ++i) {
    for (size_t j = 0; j < src.size(); ++j) {
      if (i == j) {
        dst[i][j] = 0;
      } else if (src[i][j]) {
        dst[i][j] = src[i][j];
      }
    }
  }
}

void GraphAlgorithms::MarkExtraVertices(std::vector<std::vector<int>> &matrix) {
  for (size_t i = 0; i < matrix.size(); ++i)
    for (size_t j = 0; j < matrix.size(); ++j)
      if (i != j && !matrix[i][j]) matrix[i][j] = INF;
}
