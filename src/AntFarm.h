#ifndef ANTFARM_H_
#define ANTFARM_H_

#include <vector>

#include "Ant.h"
#include "graph.h"

struct TsmResult {
  std::vector<int> vertices;
  double distance;
};

class AntFarm {
 public:
  using Adjacency_matrix = std::vector<std::vector<int>>;
  using Vector_tuple = std::vector<std::tuple<size_t, double, double>>;
  using Antfarm_matrix = std::vector<Vector_tuple>;
  using Pheromones_matrix = std::vector<std::vector<double>>;

  AntFarm(Graph &graph);
  ~AntFarm() = default;

  bool Run();
  TsmResult GetTsmResult() { return bestResult_; }

 private:
  void SetAntFarmMatrix(const Adjacency_matrix &adjacency_matrix);
  double GetRouteLength();
  void SprayPheromone();
  void UpdateBestResult();
  void UpdatePheromone();

  size_t size_matrix_;
  size_t generation_rates_;
  size_t ant_population_;
  double Q_;  // Конст для распыления феромона
  double P_;  // Кэф испарение
  double D_;  // Конст для видимости
  double Alfa_;
  double Beta_;
  double Pheromone_;

  TsmResult bestResult_;
  Antfarm_matrix antfarm_matrix_;
  Pheromones_matrix pheromones_matrix_;
  std::vector<size_t> ant_path_;
  double count_pheromone_;
  double length_path_;
};

#endif  // ANTFARM_H_