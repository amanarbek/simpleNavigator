#include "graph.h"

bool Graph::LoadGraphFromFile(std::string filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::logic_error("ERROR: Ошибка открытия файла для чтения!\n");
  }
  numVertices_ = 0;
  adjacencyMatrix_.clear();
  file >> numVertices_;
  adjacencyMatrix_.resize(numVertices_, Vec(numVertices_, 0));

  for (size_t i = 0; i < numVertices_; ++i) {
    for (size_t j = 0; j < numVertices_; ++j) {
      file >> adjacencyMatrix_[i][j];
    }
  }
  return true;
}

void Graph::ExportGraphToDot(std::string filename) {
  if ((filename.find(".dot")) == std::string::npos) filename += ".dot";

  std::ofstream file(filename);
  if (!file.is_open()) {
    throw std::logic_error("ERROR: Ошибка открытия файла для записи!\n");
  }

  file << "graph G {" << std::endl;

  for (size_t i = 0; i < numVertices_; ++i) {
    for (size_t j = 0; j < numVertices_; ++j) {
      if (adjacencyMatrix_[i][j]) {
        file << "\t" << i + 1 << " -- " << j + 1
             << " [label=" << adjacencyMatrix_[i][j] << "]" << std::endl;
      }
    }
  }
  file << "}" << std::endl;
}

void Graph::Clean() {
  for (auto &row : adjacencyMatrix_) {
    row.clear();
  }
  adjacencyMatrix_.clear();
  numVertices_ = 0;
}
