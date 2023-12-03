#include <math.h>
#include <random>
#include "graph_al.h"
#include "timings.h"

void add_random_edges(Graph_AL& g, int E) {
  int V = g.getNVertices();

  std::vector<std::pair<int, int>> possible_edges;
  possible_edges.reserve(V * V);

  for (int i = 0; i < V; i++) {
    for (int j = 0; j < V; j++) {
      possible_edges.push_back(std::make_pair(i, j));
    }
  }

  // shuffle the order to get random edges
  auto rng = std::default_random_engine{};
  std::shuffle(possible_edges.begin(), possible_edges.end(), rng);

  for (int i = 0; i < E; i++) {
    g.addEdge(possible_edges[i]);
  }
}

Graph_AL generate_graph(int V, int E) {
  Graph_AL g(V, {});

  add_random_edges(g, E);

  return g;
}

int main() {
  std::cout << "V,e,E,time" << std::endl;

  std::vector<int> Vs{10, 20, 30, 40, 50, 100, 500, 1000, 5000};
  std::vector<float> es{1.0, 1.2, 1.4, 1.8, 2.0};

  for (auto V : Vs) {
    for (auto e : es) {
      int E = std::pow(V, e);
      Graph_AL g = generate_graph(V, E);

      auto time = time_function([&g]() { g.getDistanceMatrix(); });

      std::cout << V << "," << e << "," << E << "," << time << std::endl;
    }
  }

  return 0;
}
