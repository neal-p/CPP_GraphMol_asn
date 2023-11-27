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

  auto ethane = make_Graph_AL("../ethane.txt");
  ethane.printVertices();

  for (int v = 0; v < ethane.getNVertices(); v++) {
    std::cout << "Neighbors of vertex " << v << ":" << std::endl;
    auto neighbors = ethane.getNeighbors(v);
    for (auto n : neighbors) {
      std::cout << n << " ";
    }

    std::cout << std::endl;
  }

  distmat = ethane.getDistanceMatrix();

  std::cout << std::endl;
  std::cout << "dist matrix " << std::endl;

  for (auto row : distmat) {
    for (auto d : row) {
      std::cout << d << " ";
    }
    std::cout << std::endl;
  }

  int id = ethane.addVertex();
  std::cout << "id of new added vertex " << id << std::endl;
  std::cout << "default value for new vertex atom type '"
            << ethane.getVertexAttribute<std::string>("atom_type", id) << "'"
            << std::endl;

  ethane.setVertexAttribute<std::string>("atom_type", id, "more than 1 char");
  ethane.setVertexAttribute<std::string>("atom_type", 0, "first atom");

  std::cout << "adding edge" << std::endl;
  ethane.addEdge(id, 0);

  for (int v = 0; v < ethane.getNVertices(); v++) {
    std::cout << "Neighbors of vertex " << v << ":" << std::endl;
    auto neighbors = ethane.getNeighbors(v);
    for (auto n : neighbors) {
      std::cout << n << " ";
    }

    std::cout << std::endl;
  }

  std::cout << "attribute printing" << std::endl;
  ethane.printVertices("atom_type");

  std::cout << "edges" << std::endl;
  ethane.printEdges();

  std::cout << "edge between 0 and 1 is edge id " << ethane.getEdgeBetween(0, 1)
            << std::endl;

  std::cout << "edge between 4 and 6 is edge id " << ethane.getEdgeBetween(6, 4)
            << std::endl;

  std::vector<std::string> bond_types;
  for (int b = 0; b < ethane.getNEdges(); b++) {
    bond_types.push_back("single");
  }

  bond_types[2] = "double";

  ethane.addEdgeAttributes("bond_type", bond_types);

  ethane.printEdges("bond_type");

  return 0;
}
