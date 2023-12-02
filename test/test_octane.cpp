#include <assert.h>
#include "graph_al.h"

int main() {
  Graph_AL octane = make_Graph_AL("../octane.txt");

  // Check structure basics
  assert(octane.getNVertices() == 26);

  assert(octane.getVertexAttribute<std::string>("atom_type", 0) == "C");
  assert(octane.getVertexAttribute<std::string>("atom_type", 1) == "H");
  assert(octane.getVertexAttribute<std::string>("atom_type", 2) == "H");
  assert(octane.getVertexAttribute<std::string>("atom_type", 3) == "H");
  assert(octane.getVertexAttribute<std::string>("atom_type", 4) == "C");
  assert(octane.getVertexAttribute<std::string>("atom_type", 5) == "H");
  assert(octane.getVertexAttribute<std::string>("atom_type", 6) == "H");
  assert(octane.getVertexAttribute<std::string>("atom_type", 7) == "C");
  assert(octane.getVertexAttribute<std::string>("atom_type", 8) == "H");
  assert(octane.getVertexAttribute<std::string>("atom_type", 9) == "H");
  assert(octane.getVertexAttribute<std::string>("atom_type", 10) == "C");
  assert(octane.getVertexAttribute<std::string>("atom_type", 11) == "H");
  assert(octane.getVertexAttribute<std::string>("atom_type", 12) == "H");
  assert(octane.getVertexAttribute<std::string>("atom_type", 13) == "C");
  assert(octane.getVertexAttribute<std::string>("atom_type", 14) == "H");
  assert(octane.getVertexAttribute<std::string>("atom_type", 15) == "H");
  assert(octane.getVertexAttribute<std::string>("atom_type", 16) == "C");
  assert(octane.getVertexAttribute<std::string>("atom_type", 17) == "H");
  assert(octane.getVertexAttribute<std::string>("atom_type", 18) == "H");
  assert(octane.getVertexAttribute<std::string>("atom_type", 19) == "C");
  assert(octane.getVertexAttribute<std::string>("atom_type", 20) == "H");
  assert(octane.getVertexAttribute<std::string>("atom_type", 21) == "H");
  assert(octane.getVertexAttribute<std::string>("atom_type", 22) == "C");
  assert(octane.getVertexAttribute<std::string>("atom_type", 23) == "H");
  assert(octane.getVertexAttribute<std::string>("atom_type", 24) == "H");
  assert(octane.getVertexAttribute<std::string>("atom_type", 25) == "H");

  assert(octane.getNEdges() == 25);

  assert(octane.getEdgeBetween(0, 1) != -1);
  assert(octane.getEdgeBetween(0, 2) != -1);
  assert(octane.getEdgeBetween(0, 3) != -1);
  assert(octane.getEdgeBetween(0, 4) != -1);
  assert(octane.getEdgeBetween(4, 5) != -1);
  assert(octane.getEdgeBetween(4, 6) != -1);
  assert(octane.getEdgeBetween(4, 7) != -1);
  assert(octane.getEdgeBetween(7, 8) != -1);
  assert(octane.getEdgeBetween(7, 9) != -1);
  assert(octane.getEdgeBetween(7, 10) != -1);
  assert(octane.getEdgeBetween(10, 11) != -1);
  assert(octane.getEdgeBetween(10, 12) != -1);
  assert(octane.getEdgeBetween(10, 13) != -1);
  assert(octane.getEdgeBetween(13, 14) != -1);
  assert(octane.getEdgeBetween(13, 15) != -1);
  assert(octane.getEdgeBetween(13, 16) != -1);
  assert(octane.getEdgeBetween(16, 17) != -1);
  assert(octane.getEdgeBetween(16, 18) != -1);
  assert(octane.getEdgeBetween(16, 19) != -1);
  assert(octane.getEdgeBetween(19, 20) != -1);
  assert(octane.getEdgeBetween(19, 21) != -1);
  assert(octane.getEdgeBetween(19, 22) != -1);
  assert(octane.getEdgeBetween(22, 23) != -1);
  assert(octane.getEdgeBetween(22, 24) != -1);
  assert(octane.getEdgeBetween(22, 25) != -1);

  // Check the distance matrix
  auto distmat = octane.getDistanceMatrix();

  // Used rdkit to get the expected distance matrix in python
  // mol =
  // Chem.MolFromSmiles('C([H])([H])([H])C([H])([H])C([H])([H])C([H])([H])C([H])([H])C([H])([H])C([H])([H])C([H])([H])([H])',
  // sanitize=False)
  //
  // distmat = Chem.GetDistanceMatrix(mol)

  std::vector<int> expected{
      0, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8,
      8, 1, 0, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9,
      9, 9, 1, 2, 0, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8,
      9, 9, 9, 1, 2, 2, 0, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8,
      8, 9, 9, 9, 1, 2, 2, 2, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6,
      6, 6, 7, 7, 7, 2, 3, 3, 3, 1, 0, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6,
      7, 7, 7, 8, 8, 8, 2, 3, 3, 3, 1, 2, 0, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6,
      6, 7, 7, 7, 8, 8, 8, 2, 3, 3, 3, 1, 2, 2, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4,
      4, 4, 5, 5, 5, 6, 6, 6, 3, 4, 4, 4, 2, 3, 3, 1, 0, 2, 2, 3, 3, 3, 4, 4, 4,
      5, 5, 5, 6, 6, 6, 7, 7, 7, 3, 4, 4, 4, 2, 3, 3, 1, 2, 0, 2, 3, 3, 3, 4, 4,
      4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 3, 4, 4, 4, 2, 3, 3, 1, 2, 2, 0, 1, 1, 1, 2,
      2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 4, 5, 5, 5, 3, 4, 4, 2, 3, 3, 1, 0, 2, 2,
      3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 4, 5, 5, 5, 3, 4, 4, 2, 3, 3, 1, 2, 0,
      2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 4, 5, 5, 5, 3, 4, 4, 2, 3, 3, 1, 2,
      2, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 6, 6, 6, 4, 5, 5, 3, 4, 4, 2,
      3, 3, 1, 0, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 4, 5, 5, 3, 4, 4,
      2, 3, 3, 1, 2, 0, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 4, 5, 5, 3, 4,
      4, 2, 3, 3, 1, 2, 2, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 6, 7, 7, 7, 5, 6, 6, 4,
      5, 5, 3, 4, 4, 2, 3, 3, 1, 0, 2, 2, 3, 3, 3, 4, 4, 4, 6, 7, 7, 7, 5, 6, 6,
      4, 5, 5, 3, 4, 4, 2, 3, 3, 1, 2, 0, 2, 3, 3, 3, 4, 4, 4, 6, 7, 7, 7, 5, 6,
      6, 4, 5, 5, 3, 4, 4, 2, 3, 3, 1, 2, 2, 0, 1, 1, 1, 2, 2, 2, 7, 8, 8, 8, 6,
      7, 7, 5, 6, 6, 4, 5, 5, 3, 4, 4, 2, 3, 3, 1, 0, 2, 2, 3, 3, 3, 7, 8, 8, 8,
      6, 7, 7, 5, 6, 6, 4, 5, 5, 3, 4, 4, 2, 3, 3, 1, 2, 0, 2, 3, 3, 3, 7, 8, 8,
      8, 6, 7, 7, 5, 6, 6, 4, 5, 5, 3, 4, 4, 2, 3, 3, 1, 2, 2, 0, 1, 1, 1, 8, 9,
      9, 9, 7, 8, 8, 6, 7, 7, 5, 6, 6, 4, 5, 5, 3, 4, 4, 2, 3, 3, 1, 0, 2, 2, 8,
      9, 9, 9, 7, 8, 8, 6, 7, 7, 5, 6, 6, 4, 5, 5, 3, 4, 4, 2, 3, 3, 1, 2, 0, 2,
      8, 9, 9, 9, 7, 8, 8, 6, 7, 7, 5, 6, 6, 4, 5, 5, 3, 4, 4, 2, 3, 3, 1, 2, 2,
      0};

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
