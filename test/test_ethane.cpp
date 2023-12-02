#include <assert.h>
#include "graph_al.h"

int main() {
  Graph_AL ethane = make_Graph_AL("../ethane.txt");

  // Check structure basics
  assert(ethane.getNVertices() == 8);

  assert(ethane.getVertexAttribute<std::string>("atom_type", 0) == "C");
  assert(ethane.getVertexAttribute<std::string>("atom_type", 1) == "H");
  assert(ethane.getVertexAttribute<std::string>("atom_type", 2) == "H");
  assert(ethane.getVertexAttribute<std::string>("atom_type", 3) == "H");
  assert(ethane.getVertexAttribute<std::string>("atom_type", 4) == "C");
  assert(ethane.getVertexAttribute<std::string>("atom_type", 5) == "H");
  assert(ethane.getVertexAttribute<std::string>("atom_type", 6) == "H");
  assert(ethane.getVertexAttribute<std::string>("atom_type", 7) == "H");

  assert(ethane.getNEdges() == 7);

  assert(ethane.getEdgeBetween(0, 1) != -1);
  assert(ethane.getEdgeBetween(0, 2) != -1);
  assert(ethane.getEdgeBetween(0, 3) != -1);
  assert(ethane.getEdgeBetween(4, 5) != -1);
  assert(ethane.getEdgeBetween(4, 6) != -1);
  assert(ethane.getEdgeBetween(4, 7) != -1);

  assert(ethane.getEdgeBetween(1, 0) != -1);
  assert(ethane.getEdgeBetween(2, 0) != -1);
  assert(ethane.getEdgeBetween(3, 0) != -1);
  assert(ethane.getEdgeBetween(5, 4) != -1);
  assert(ethane.getEdgeBetween(6, 4) != -1);
  assert(ethane.getEdgeBetween(7, 4) != -1);

  // Check the distance matrix
  auto distmat = ethane.getDistanceMatrix();

  std::vector<int> expected{
      // NOLINT
      0, 1, 1, 1, 1, 2, 2, 2,  // NOLINT
      1, 0, 2, 2, 2, 3, 3, 3,  // NOLINT
      1, 2, 0, 2, 2, 3, 3, 3,  // NOLINT
      1, 2, 2, 0, 2, 3, 3, 3,  // NOLINT
      1, 2, 2, 2, 0, 1, 1, 1,  // NOLINT
      2, 3, 3, 3, 1, 0, 2, 2,  // NOLINT
      2, 3, 3, 3, 1, 2, 0, 2,  // NOLINT
      2, 3, 3, 3, 1, 2, 2, 0   // NOLINT
  };                           // NOLINT

  auto it = expected.begin();

  for (auto row : distmat) {
    for (auto dist : row) {
      assert(dist == *it);
      it++;
    }
  }

  std::cout << "ALL TESTS PASSED" << std::endl;

  return 0;
}
