CXX = g++
CXXFLAGS = -std=c++20 -Wall -Werror -Wextra
TEST_FLAGS = -lgtest -lgtest_main
SRC_DIR = src
BUILD_DIR = ../build
LIB_GRAPH = graph.a
LIB_GRAPH_ALGO = graph_algorithms.a

.PHONY: all clean test graph.a style

all: graph.a graph_algorithms.a

graph.a:
	$(CXX) -c $(CXXFLAGS) graph.cc -o graph.o
	@mkdir -p $(BUILD_DIR)
	@cd ../build/; ar rcs $(LIB_GRAPH) ../src/graph.o
	@rm -rf graph.o
	ranlib $(BUILD_DIR)/$(LIB_GRAPH)

graph_algorithms.a:
	$(CXX) -c $(CXXFLAGS) graph_algorithms.cc -o graph_algorithms.o
	@mkdir -p $(BUILD_DIR)
	@cd ../build/; ar rcs $(LIB_GRAPH_ALGO) ../src/graph_algorithms.o
	@rm -rf graph_algorithms.o
	ranlib $(BUILD_DIR)/$(LIB_GRAPH_ALGO)

main: graph.a graph_algorithms.a
	$(CXX) -c $(CXXFLAGS) main.cc -o main.o
	$(CXX) -c $(CXXFLAGS) Ant.cc -o ant.o
	$(CXX) -c $(CXXFLAGS) AntFarm.cc -o antFarm.o
	$(CXX) -c $(CXXFLAGS) interface.cc -o interface.o
	$(CXX) $(CXXFLAGS) main.o interface.o ant.o antFarm.o ../build/graph.a ../build/graph_algorithms.a -o myGraph
	@mv myGraph $(BUILD_DIR)/
	@rm -rf *.o
	../build/myGraph

test: graph.a graph_algorithms.a
	$(CXX) ./tests/tests_graph.cc ./tests/tests_graph_algorithms.cc Ant.cc AntFarm.cc $(BUILD_DIR)/* -o test.out $(TEST_FLAGS)
	clear
	@./test.out

clean:
	@rm -rf *.out ../build *.gch *.o

style:
	@clang-format -i --style=google **/*.cc *.cc *.h
	clang-format -n --style=google **/*.cc *.cc *.h

