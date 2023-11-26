#include "graph_base.h"

class Graph_AL : public GraphBase {
 public:
  std::vector<std::vector<int>> adj_;

  Graph_AL(int n_vertices,
           std::vector<std::pair<int, int>> edges,
           bool directed = false)
      : GraphBase(n_vertices, edges, directed) {
    /******************************************
     * Construct adj list from the given edges *
     ******************************************/

    // first, need to make a list for each vertex
    for (int v = 0; v < n_vertices; v++) {
      std::vector<int> neighbors;
      adj_.push_back(neighbors);
    }

    // fill in the edges from the passed in pairs
    for (auto edge : edges) {
      if (edge.first >= n_vertices_ || edge.second >= n_vertices_) {
        throw std::runtime_error("provided edge outside of vertex range!");
      }

      adj_[edge.first].push_back(edge.second);
      if (!directed_) {
        adj_[edge.second].push_back(edge.first);
      }
    }
  }
  std::vector<int> getNeighbors(int v) { return adj_[v]; }
};
