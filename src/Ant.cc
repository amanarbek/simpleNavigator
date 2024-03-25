#include "Ant.h"

Ant::Ant(const Ant_matrix &ant_matrix, size_t start_vertex,
         std::pair<double, double> alfa_beta)
    : probability_matrix_(ant_matrix.size(), Wish_vector(ant_matrix.size())),
      tabu_list_(ant_matrix.size(), false),
      start_vertex_(start_vertex),
      Alfa_(alfa_beta.first),
      Beta_(alfa_beta.second) {
  size_matrix_ = ant_matrix.size();
  path_.reserve(size_matrix_);
  SetProbabilityMatrix(ant_matrix);
  if (start_vertex_ >= size_matrix_) start_vertex_ %= size_matrix_;
  AddVisitedVertex();
}

void Ant::SetProbabilityMatrix(const Ant_matrix &ant_matrix) {
  for (size_t i = 0; i < size_matrix_; ++i) {
    for (size_t j = 0; j < size_matrix_; ++j) {
      probability_matrix_[i][j].first =
          std::get<1>(ant_matrix[i][j]);  // Видимость
      probability_matrix_[i][j].second =
          std::get<2>(ant_matrix[i][j]);  // Феромон
    }
  }
}

void Ant::AddVisitedVertex() {
  path_.push_back(start_vertex_);
  tabu_list_[start_vertex_] = true;
}

bool Ant::FindPath() {
  if (!FindAccessibleVertexes()) return false;
  while (!accessible_vertexes_.empty()) {
    MoveNextVertex();
  }
  return (path_.size() == probability_matrix_.size() &&
          probability_matrix_[start_vertex_][path_.front()].first > 0.0);
}

void Ant::MoveNextVertex() {
  size_t count_accessible_vertexes = accessible_vertexes_.size();
  std::vector<double> wish_transition(GetWishTransition());
  std::map<double, size_t> transition_probability;
  auto it = accessible_vertexes_.begin();
  for (size_t i = 0; i < count_accessible_vertexes; ++i) {
    transition_probability.insert(
        {wish_transition[i] / wish_transition.back(), *it});
    ++it;
  }
  auto next_vertex = transition_probability.upper_bound(ChoiceDoubleRand());
  if (next_vertex == transition_probability.end()) --next_vertex;
  start_vertex_ = next_vertex->second;
  AddVisitedVertex();
  FindAccessibleVertexes();
  count_accessible_vertexes = accessible_vertexes_.size();
  wish_transition = GetWishTransition();
}

double Ant::ChoiceDoubleRand() {
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<double> random_double(0, 1);
  return random_double(eng);
}

std::vector<double> Ant::GetWishTransition() {
  size_t countAccessibleVertexes = accessible_vertexes_.size();
  std::vector<double> wishTransition(countAccessibleVertexes +
                                     1);  // Последний элемент хранит сумму всех
                                          // желаний для всех доступных вершин
  auto it = accessible_vertexes_.begin();
  for (size_t i = 0; i < countAccessibleVertexes; ++i) {
    wishTransition[i] =
        (pow(probability_matrix_[start_vertex_][*it].first, Alfa_) *
         pow(probability_matrix_[start_vertex_][*it].second, Beta_));
    wishTransition[countAccessibleVertexes] += wishTransition[i];
    ++it;
  }
  return wishTransition;
}

bool Ant::FindAccessibleVertexes() {
  accessible_vertexes_.clear();
  for (size_t i = 0; i < probability_matrix_[start_vertex_].size(); ++i) {
    if (!tabu_list_[i] && probability_matrix_[start_vertex_][i].first > 0.0) {
      accessible_vertexes_.push_back(i);
    }
  }
  return !accessible_vertexes_.empty();
}