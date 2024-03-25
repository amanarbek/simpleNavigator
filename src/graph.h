#ifndef GRAPH_H_
#define GRAPH_H_

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

class Graph {
 public:
  using Vec = std::vector<int>;
  using Matrix = std::vector<std::vector<int>>;

  Graph() : adjacencyMatrix_{}, numVertices_{0} {};
  ~Graph() = default;
  const Matrix GetMatrix() const { return adjacencyMatrix_; }
  int GetNumOfVertices() const { return numVertices_; }
  bool LoadGraphFromFile(std::string filename);
  void ExportGraphToDot(std::string filename);

 private:
  void Clean();

  Matrix adjacencyMatrix_;
  unsigned numVertices_;
};

#endif  // GRAPH_H_
