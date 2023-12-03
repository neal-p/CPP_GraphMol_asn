#include <math.h>
#include "graph_al.h"
#include "timings.h"

void add_random_edge(Graph_AL& g) {
  int V = g.getNVertices();
  int v1 = rand() % V;
  int v2 = rand() % V;

  while (g.getEdgeBetween(v1, v2) != -1) {
    v1 = rand() % V;
    v2 = rand() % V;
  }

  g.addEdge(v1, v2);
}

Graph_AL generate_graph(int V, int E) {
  Graph_AL g(V, {});

  for (int i = 0; i < E; i++) {
    add_random_edge(g);
  }

  return g;
}

int main() {
  std::cout << "V,E,time" << std::endl;

  std::vector<int> Vs{10, 100, 1000, 10000, 100000};
  std::vector<float> Es{1.0, 1.2, 1.4};

  for (auto V : Vs) {
    for (auto E : Es) {
      int e = std::pow(V, E);
      Graph_AL g = generate_graph(V, e);

      auto time = time_function([&g]() { g.getDistanceMatrix(); });

      std::cout << V << "," << e << "," << time << std::endl;
    }
  }

  return 0;
}
