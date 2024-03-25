#include <gtest/gtest.h>

#include <sstream>

#include "../graph.h"

TEST(GraphTest, LoadGraphFromFile1) {
  Graph graph;
  ASSERT_TRUE(graph.LoadGraphFromFile("./tests/for_tests/upload_file.txt"));

  Graph::Matrix matrix = graph.GetMatrix();
  EXPECT_EQ(matrix[0][1], 1);
  EXPECT_EQ(matrix[0][3], 2);
  EXPECT_EQ(matrix[1][2], 3);
  EXPECT_EQ(matrix[3][2], 4);
}

TEST(GraphTest, LoadGraphFromFile2) {
  Graph graph;
  EXPECT_ANY_THROW(graph.LoadGraphFromFile("protest.txt"));
}

TEST(GraphTest, ExportGraphToDot1) {
  Graph graph;
  ASSERT_TRUE(graph.LoadGraphFromFile("./tests/for_tests/upload_file.txt"));
  ASSERT_NO_THROW(graph.ExportGraphToDot("./tests/for_tests/export_file.dot"));
}

TEST(GraphTest, ExportGraphToDot2) {
  Graph graph;
  ASSERT_TRUE(graph.LoadGraphFromFile("./tests/for_tests/upload_file.txt"));
  EXPECT_ANY_THROW(graph.ExportGraphToDot("/com.dot"));
}
