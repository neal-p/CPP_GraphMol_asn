#include <iostream>
#include <utility>
#include <vector>
#include "graph_al.h"

int main() {
  std::vector<std::pair<int, int>> edges;
  edges.push_back({0, 1});
  edges.push_back({1, 2});
  edges.push_back({1, 3});

  std::vector<std::string> attributes{"name", "weight"};
  std::vector<std::string> names{"v1", "v2", "v3", "v4"};
  std::vector<float> weights{1.2, 3.5, 5.4, 3.2};

  Graph_AL g(4, edges);

  g.addVertexAttributes("name", names);
  g.addVertexAttributes("weight", weights);

  g.printVertices(attributes);

  for (int v = 0; v < 4; v++) {
    std::cout << "Neighbors of vertex " << v << ":" << std::endl;
    auto neighbors = g.getNeighbors(v);
    for (auto n : neighbors) {
      std::cout << n << " ";
    }

    std::cout << std::endl;
  }

  auto distmat = g.getDistanceMatrix();

  std::cout << std::endl;
  std::cout << "dist matrix " << std::endl;

  for (auto row : distmat) {
    for (auto d : row) {
      std::cout << d << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
