#include <gtest/gtest.h>

#include "../graph_algorithms.h"

TEST(GraphAlgorithmsTest, GetShortestPathBetweenVertices1) {
  Graph graph;
  graph.LoadGraphFromFile("./examples/example1.txt");

  unsigned original = 60;
  GraphAlgorithms graal;
  unsigned result = graal.GetShortestPathBetweenVertices(graph, 1, 5);

  EXPECT_EQ(original, result);
}

TEST(GraphAlgorithmsTest, GetShortestPathBetweenVertices2) {
  Graph graph;
  graph.LoadGraphFromFile("./examples/example1.txt");

  int original = std::numeric_limits<int>::max();
  GraphAlgorithms graal;
  unsigned result = graal.GetShortestPathBetweenVertices(graph, 4, 1);

  EXPECT_EQ(original, result);
}

TEST(GraphAlgorithmsTest, GetShortestPathsBetweenAllVertices1) {
  Graph graph;
  graph.LoadGraphFromFile("./examples/example2.txt");

  GraphAlgorithms graal;
  auto result = graal.GetShortestPathsBetweenAllVertices(graph);
  std::vector<std::vector<int>> original = {{0, 7, 5}, {3, 0, 8}, {5, 2, 0}};

  for (size_t i = 0; i < result.size(); ++i) {
    for (size_t j = 0; j < result.size(); ++j) {
      EXPECT_EQ(original[i][j], result[i][j]);
    }
  }
}

TEST(GraphAlgorithmsTest, GetShortestPathsBetweenAllVertices2) {
  Graph graph;
  graph.LoadGraphFromFile("./examples/example3.txt");

  GraphAlgorithms graal;
  auto result = graal.GetShortestPathsBetweenAllVertices(graph);
  std::vector<std::vector<int>> original = {
      {0, 28, 21, 28, 12, 27}, {28, 0, 24, 37, 21, 9},  {21, 24, 0, 13, 11, 33},
      {28, 37, 13, 0, 16, 38}, {12, 21, 11, 16, 0, 22}, {27, 9, 33, 38, 22, 0}};

  for (size_t i = 0; i < result.size(); ++i)
    for (size_t j = 0; j < result.size(); ++j)
      EXPECT_EQ(original[i][j], result[i][j]);
}

TEST(GraphAlgorithmsTest, GetLeastSpanningTree1) {
  Graph gera;
  gera.LoadGraphFromFile("./examples/NV_example1.txt");

  GraphAlgorithms gral;
  std::vector<std::vector<int>> res = gral.GetLeastSpanningTree(gera);
  std::vector<std::vector<int>> original = {
      {0, 7, 0, 5, 0, 0, 0}, {7, 0, 0, 0, 7, 0, 0}, {0, 0, 0, 0, 5, 0, 0},
      {5, 0, 0, 0, 0, 6, 0}, {0, 7, 5, 0, 0, 0, 9}, {0, 0, 0, 6, 0, 0, 0},
      {0, 0, 0, 0, 9, 0, 0}};

  for (size_t i = 0; i < original.size(); ++i) {
    for (size_t j = 0; j < original.size(); ++j) {
      EXPECT_EQ(original[i][j], res[i][j]);
    }
  }
}

TEST(GraphAlgorithmsTest, GetLeastSpanningTree2) {
  Graph gera;
  gera.LoadGraphFromFile("./examples/NV_example2.txt");

  GraphAlgorithms gral;
  std::vector<std::vector<int>> res = gral.GetLeastSpanningTree(gera);
  std::vector<std::vector<int>> original = {
      {0, 2, 6, 0, 0, 0, 3, 0, 0}, {2, 0, 0, 3, 0, 4, 0, 0, 0},
      {6, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 3, 0, 0, 5, 0, 0, 0, 0},
      {0, 0, 0, 5, 0, 0, 0, 0, 0}, {0, 4, 0, 0, 0, 0, 0, 0, 4},
      {3, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 1},
      {0, 0, 0, 0, 0, 4, 0, 1, 0}};

  for (size_t i = 0; i < res.size(); ++i)
    for (size_t j = 0; j < res.size(); ++j)
      EXPECT_EQ(original[i][j], res[i][j]);
}

TEST(BreadthFirstSearch, test_1) {
  Graph checking_graph;
  checking_graph.LoadGraphFromFile("./examples/graph_1.txt");

  GraphAlgorithms GA;
  std::vector<int> funcOut = GA.BreadthFirstSearch(checking_graph, 1);

  std::vector<int> reference{1, 2, 3, 4, 5, 6};

  ASSERT_TRUE(funcOut == reference);
}

TEST(BreadthFirstSearch, test_2) {
  Graph checking_graph;
  checking_graph.LoadGraphFromFile("./examples/graph_1.txt");

  GraphAlgorithms GA;
  std::vector<int> funcOut = GA.BreadthFirstSearch(checking_graph, 2);

  std::vector<int> reference{2, 1, 3, 5, 6, 4};

  ASSERT_TRUE(funcOut == reference);
}

TEST(BreadthFirstSearch, test_3) {
  Graph checking_graph;
  checking_graph.LoadGraphFromFile("./examples/graph_1.txt");

  GraphAlgorithms GA;
  std::vector<int> funcOut = GA.BreadthFirstSearch(checking_graph, 3);

  std::vector<int> reference{3, 1, 2, 4, 5, 6};

  ASSERT_TRUE(funcOut == reference);
}

TEST(BreadthFirstSearch, test_4) {
  Graph checking_graph;
  checking_graph.LoadGraphFromFile("./examples/graph_1.txt");

  GraphAlgorithms GA;
  std::vector<int> funcOut = GA.BreadthFirstSearch(checking_graph, 5);

  std::vector<int> reference{5, 1, 2, 3, 4, 6};

  ASSERT_TRUE(funcOut == reference);
}

TEST(BreadthFirstSearch, test_5) {
  Graph checking_graph;
  checking_graph.LoadGraphFromFile("./examples/graph_2.txt");

  GraphAlgorithms GA;
  std::vector<int> funcOut = GA.BreadthFirstSearch(checking_graph, 1);

  std::vector<int> reference{1, 2, 3, 4, 5, 6, 7, 8, 9};

  ASSERT_TRUE(funcOut == reference);
}

TEST(BreadthFirstSearch, test_6) {
  Graph checking_graph;
  checking_graph.LoadGraphFromFile("./examples/graph_2.txt");

  GraphAlgorithms GA;
  std::vector<int> funcOut = GA.BreadthFirstSearch(checking_graph, 3);

  std::vector<int> reference{3, 1, 2, 4, 5, 6, 7, 8, 9};

  ASSERT_TRUE(funcOut == reference);
}

TEST(BreadthFirstSearch, test_7) {
  Graph checking_graph;
  checking_graph.LoadGraphFromFile("./examples/graph_2.txt");

  GraphAlgorithms GA;
  std::vector<int> funcOut = GA.BreadthFirstSearch(checking_graph, 5);

  std::vector<int> reference{5, 1, 2, 3, 4, 6, 7, 8, 9};

  ASSERT_TRUE(funcOut == reference);
}

TEST(BreadthFirstSearch, test_8) {
  Graph checking_graph;
  checking_graph.LoadGraphFromFile("./examples/graph_2.txt");

  GraphAlgorithms GA;
  std::vector<int> funcOut = GA.BreadthFirstSearch(checking_graph, 8);

  std::vector<int> reference{8, 1, 2, 3, 4, 5, 6, 7, 9};

  ASSERT_TRUE(funcOut == reference);
}

TEST(BreadthFirstSearch, test_9) {
  Graph checking_graph;
  checking_graph.LoadGraphFromFile("./examples/graph_3.txt");

  GraphAlgorithms GA;
  std::vector<int> funcOut = GA.BreadthFirstSearch(checking_graph, 1);

  std::vector<int> reference{1, 4, 5, 3, 2};

  ASSERT_TRUE(funcOut == reference);
}

TEST(BreadthFirstSearch, test_10) {
  Graph checking_graph;
  checking_graph.LoadGraphFromFile("./examples/graph_3.txt");

  GraphAlgorithms GA;
  std::vector<int> funcOut = GA.BreadthFirstSearch(checking_graph, 3);

  std::vector<int> reference{3, 2, 4, 5, 1};

  ASSERT_TRUE(funcOut == reference);
}

TEST(BreadthFirstSearch, test_11) {
  Graph checking_graph;
  checking_graph.LoadGraphFromFile("./examples/graph_3.txt");

  GraphAlgorithms GA;
  std::vector<int> funcOut = GA.BreadthFirstSearch(checking_graph, 4);

  std::vector<int> reference{4, 1, 3, 5, 2};

  ASSERT_TRUE(funcOut == reference);
}

TEST(DepthFirstSearch, test_1) {
  Graph checking_graph;
  checking_graph.LoadGraphFromFile("./examples/graph_1.txt");

  GraphAlgorithms GA;
  std::vector<int> funcOut = GA.DepthFirstSearch(checking_graph, 1);

  std::vector<int> reference{1, 2, 3, 4, 5, 6};

  ASSERT_TRUE(funcOut == reference);
}

TEST(DepthFirstSearch, test_2) {
  Graph checking_graph;
  checking_graph.LoadGraphFromFile("./examples/graph_1.txt");

  GraphAlgorithms GA;
  std::vector<int> funcOut = GA.DepthFirstSearch(checking_graph, 3);

  std::vector<int> reference{3, 1, 2, 5, 4, 6};

  ASSERT_TRUE(funcOut == reference);
}

TEST(DepthFirstSearch, test_3) {
  Graph checking_graph;
  checking_graph.LoadGraphFromFile("./examples/graph_1.txt");

  GraphAlgorithms GA;
  std::vector<int> funcOut = GA.DepthFirstSearch(checking_graph, 5);

  std::vector<int> reference{5, 1, 2, 3, 4, 6};

  ASSERT_TRUE(funcOut == reference);
}

TEST(DepthFirstSearch, test_4) {
  Graph checking_graph;
  checking_graph.LoadGraphFromFile("./examples/graph_1.txt");

  GraphAlgorithms GA;
  std::vector<int> funcOut = GA.DepthFirstSearch(checking_graph, 6);

  std::vector<int> reference{6, 1, 2, 3, 4, 5};

  ASSERT_TRUE(funcOut == reference);
}

TEST(DepthFirstSearch, test_5) {
  Graph checking_graph;
  checking_graph.LoadGraphFromFile("./examples/graph_2.txt");

  GraphAlgorithms GA;
  std::vector<int> funcOut = GA.DepthFirstSearch(checking_graph, 1);

  std::vector<int> reference{1, 2, 3, 4, 5, 6, 7, 8, 9};

  ASSERT_TRUE(funcOut == reference);
}

TEST(DepthFirstSearch, test_6) {
  Graph checking_graph;
  checking_graph.LoadGraphFromFile("./examples/graph_2.txt");

  GraphAlgorithms GA;
  std::vector<int> funcOut = GA.DepthFirstSearch(checking_graph, 3);

  std::vector<int> reference{3, 1, 2, 4, 5, 6, 7, 8, 9};

  ASSERT_TRUE(funcOut == reference);
}

TEST(DepthFirstSearch, test_7) {
  Graph checking_graph;
  checking_graph.LoadGraphFromFile("./examples/graph_2.txt");

  GraphAlgorithms GA;
  std::vector<int> funcOut = GA.DepthFirstSearch(checking_graph, 5);

  std::vector<int> reference{5, 1, 2, 3, 4, 6, 7, 8, 9};

  ASSERT_TRUE(funcOut == reference);
}

TEST(DepthFirstSearch, test_8) {
  Graph checking_graph;
  checking_graph.LoadGraphFromFile("./examples/graph_2.txt");

  GraphAlgorithms GA;
  std::vector<int> funcOut = GA.DepthFirstSearch(checking_graph, 8);

  std::vector<int> reference{8, 1, 2, 3, 4, 5, 6, 7, 9};

  ASSERT_TRUE(funcOut == reference);
}

TEST(DepthFirstSearch, test_9) {
  Graph checking_graph;
  checking_graph.LoadGraphFromFile("./examples/graph_3.txt");

  GraphAlgorithms GA;
  std::vector<int> funcOut = GA.DepthFirstSearch(checking_graph, 1);

  std::vector<int> reference{1, 4, 3, 2, 5};

  ASSERT_TRUE(funcOut == reference);
}

TEST(DepthFirstSearch, test_10) {
  Graph checking_graph;
  checking_graph.LoadGraphFromFile("./examples/graph_3.txt");

  GraphAlgorithms GA;
  std::vector<int> funcOut = GA.DepthFirstSearch(checking_graph, 2);

  std::vector<int> reference{2, 3, 4, 1, 5};

  ASSERT_TRUE(funcOut == reference);
}

TEST(DepthFirstSearch, test_11) {
  Graph checking_graph;
  checking_graph.LoadGraphFromFile("./examples/graph_3.txt");

  GraphAlgorithms GA;
  std::vector<int> funcOut = GA.DepthFirstSearch(checking_graph, 4);

  std::vector<int> reference{4, 1, 5, 2, 3};

  ASSERT_TRUE(funcOut == reference);
}

TEST(SolveTravelingSalesmanProblem, test_1) {
  Graph checking_graph;
  checking_graph.LoadGraphFromFile("./examples/sale_1.txt");

  GraphAlgorithms alg;
  const TsmResult res = alg.SolveTravelingSalesmanProblem(checking_graph);

  double answer = 253;
  ASSERT_EQ(answer, res.distance);
}

TEST(SolveTravelingSalesmanProblem, test_2) {
  Graph checking_graph;
  checking_graph.LoadGraphFromFile("./examples/sale_2.txt");

  GraphAlgorithms alg;
  const TsmResult res = alg.SolveTravelingSalesmanProblem(checking_graph);

  double answer = 127;
  ASSERT_EQ(answer, res.distance);
}

TEST(SolveTravelingSalesmanProblem, test_3) {
  Graph checking_graph;
  checking_graph.LoadGraphFromFile("./examples/sale_3_err.txt");

  GraphAlgorithms alg;
  const TsmResult res = alg.SolveTravelingSalesmanProblem(checking_graph);

  double answer = 69;
  ASSERT_EQ(answer, res.distance);
}