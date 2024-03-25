#ifndef GRAPH_ALGORITHMS_H_
#define GRAPH_ALGORITHMS_H_

#include <algorithm>

#include "AntFarm.h"
#include "graph.h"
#include "queue.h"
#include "stack.h"

const constexpr int INF = std::numeric_limits<int>::max();

class GraphAlgorithms {
 public:
  std::vector<int> DepthFirstSearch(Graph &graph, int start_vertex);
  std::vector<int> BreadthFirstSearch(Graph &graph, int start_vertex);
  unsigned GetShortestPathBetweenVertices(Graph &graph, int vertex1,
                                          int vertex2);
  std::vector<std::vector<int>> GetShortestPathsBetweenAllVertices(
      const Graph &graph);
  std::vector<std::vector<int>> GetLeastSpanningTree(const Graph &graph);
  TsmResult SolveTravelingSalesmanProblem(Graph &graph);

 private:
  unsigned FindMinWeght(const std::vector<unsigned> &distance,
                        const std::vector<bool> &visit, unsigned &minIndex);
  void FindDistances(std::vector<unsigned> &distance,
                     const Graph::Matrix &adjacencyMatrix, unsigned row,
                     unsigned weight);
  void InitializeShortPathsMatrix(std::vector<std::vector<int>> src,
                                  std::vector<std::vector<int>> &dst);
  void MarkExtraVertices(std::vector<std::vector<int>> &matrix);
};
#endif  // GRAPH_ALGORITHMS_H_