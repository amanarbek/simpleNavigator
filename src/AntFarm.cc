#include "AntFarm.h"

AntFarm::AntFarm(Graph &graph)
    : antfarm_matrix_(graph.GetNumOfVertices(),
                      Vector_tuple(graph.GetNumOfVertices())),
      pheromones_matrix_(graph.GetNumOfVertices(),
                         std::vector<double>(graph.GetNumOfVertices())) {
  size_matrix_ = static_cast<size_t>(graph.GetNumOfVertices());
  generation_rates_ = 600;
  ant_population_ = size_matrix_;
  Q_ = 1.0;
  P_ = 0.6;
  D_ = 1.0;
  Alfa_ = 1.0;
  Beta_ = 0.5;
  Pheromone_ = 0.2;
  bestResult_.vertices.reserve(size_matrix_);
  bestResult_.distance = 0;
  SetAntFarmMatrix(graph.GetMatrix());
}

bool AntFarm::Run() {
  bool found = false;
  for (size_t i = 0; i < generation_rates_; ++i) {
    for (size_t start = 0; start < ant_population_; ++start) {
      Ant ant(antfarm_matrix_, start, {Alfa_, Beta_});
      if (ant.FindPath()) {
        found = true;
        ant_path_ = ant.GetPath();
        length_path_ = GetRouteLength();
        count_pheromone_ = Q_ / length_path_;
        SprayPheromone();
        UpdateBestResult();
      }
    }
    UpdatePheromone();
  }
  return found;
}

void AntFarm::SetAntFarmMatrix(const Adjacency_matrix &adjacency_matrix) {
  for (size_t i = 0; i < size_matrix_; ++i) {
    for (size_t j = 0; j < size_matrix_; ++j) {
      if (i != j && adjacency_matrix[i][j] > 0.0) {
        std::get<0>(antfarm_matrix_[i][j]) = adjacency_matrix[i][j];
        std::get<1>(antfarm_matrix_[i][j]) =
            D_ / static_cast<double>(adjacency_matrix[i][j]);
        std::get<2>(antfarm_matrix_[i][j]) = Pheromone_;
      }
    }
  }
}

double AntFarm::GetRouteLength() {
  double length_path(0.0);
  for (size_t i = 0, last_path = size_matrix_ - 1; i < size_matrix_; ++i) {
    if (i == last_path) {
      length_path += std::get<0>(antfarm_matrix_[ant_path_[i]][ant_path_[0]]);
    } else {
      length_path +=
          std::get<0>(antfarm_matrix_[ant_path_[i]][ant_path_[i + 1]]);
    }
  }
  return length_path;
}

void AntFarm::SprayPheromone() {
  for (size_t i = 0, last_path = size_matrix_ - 1; i < size_matrix_; ++i) {
    if (i == last_path) {
      pheromones_matrix_[ant_path_[i]][ant_path_[0]] += count_pheromone_;
    } else {
      pheromones_matrix_[ant_path_[i]][ant_path_[i + 1]] += count_pheromone_;
    }
  }
}

void AntFarm::UpdateBestResult() {
  if (bestResult_.distance == 0 || bestResult_.distance > length_path_) {
    bestResult_.vertices.clear();
    for (size_t i = 0; i < size_matrix_; ++i) {
      bestResult_.vertices.push_back(static_cast<int>(ant_path_[i] + 1));
    }
    bestResult_.distance = length_path_;
  }
}

void AntFarm::UpdatePheromone() {
  for (size_t i = 0; i < size_matrix_; ++i) {
    for (size_t j = 0; j < size_matrix_; ++j) {
      if (i != j) {
        std::get<2>(antfarm_matrix_[i][j]) *= P_;
        std::get<2>(antfarm_matrix_[i][j]) += pheromones_matrix_[i][j];
        pheromones_matrix_[i][j] = 0.0;
      }
    }
  }
}