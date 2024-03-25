#ifndef ANT_H_
#define ANT_H_

#include <cmath>
#include <map>
#include <random>
#include <tuple>
#include <vector>

#include "list.h"

class Ant {
 public:
  using Ant_matrix =
      std::vector<std::vector<std::tuple<size_t, double, double>>>;
  using Pheromones_matrix = std::vector<std::vector<double>>;
  using Wish_vector = std::vector<std::pair<double, double>>;
  using Probability_matrix = std::vector<Wish_vector>;

  Ant(const Ant_matrix &ant_matrix, size_t start_vertex,
      std::pair<double, double> alfa_beta);
  ~Ant() = default;

  bool FindPath();
  std::vector<size_t> GetPath() const { return path_; }

 private:
  void SetProbabilityMatrix(const Ant_matrix &ant_matrix);
  void AddVisitedVertex();
  double ChoiceDoubleRand();
  std::vector<double> GetWishTransition();
  bool FindAccessibleVertexes();
  void MoveNextVertex();

  Probability_matrix probability_matrix_;
  my::list<size_t> accessible_vertexes_;
  std::vector<size_t> path_;
  std::vector<bool> tabu_list_;
  size_t size_matrix_;
  size_t start_vertex_;
  const double Alfa_;
  const double Beta_;
};

#endif  // ANT_H_