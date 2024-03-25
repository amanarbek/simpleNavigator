#ifndef INTERFACE_H_
#define INTERFACE_H_

#include <thread>

#include "graph.h"
#include "graph_algorithms.h"

class Interface {
 public:
  void Show();

 private:
  void SplashScreen();
  char WelcomePage();
  char LoadFile();
  char ExportFile();
  char DepthAlgo();
  char BreadthAlgo();
  char Dijkstra();
  char Warshall();
  char Prima();
  char AntManar();
  void PrintDepthAndBreadthResult(const std::vector<int> &vec, const char c);
  void PrintResultMat(const std::vector<std::vector<int>> &vec);
  void PrintTsmResult(const TsmResult &resStruct);
  const std::string menu_ =
      "\033[92m"
      "\t\t=============\n"
      "\t\t|| M E N U ||\n"
      "\t\t=============\n"
      "\033[39m\n";
  Graph *graph_;
  GraphAlgorithms *graal_;
};
#endif  // INTERFACE_H_
