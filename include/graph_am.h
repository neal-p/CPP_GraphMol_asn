#include "graph_base.h"

class Graph_AM : public GraphBase {
 public:
  std::vector<std::vector<int>> adj_;

  Graph_AM(int n_vertices,
           std::vector<std::pair<int, int>> edges,
           bool directed = false)
      : GraphBase(n_vertices, edges, directed) {
    /******************************************
     * Construct adj matrix from the given edges *
     ******************************************/

    // first, need to make the matrix
    // fill values with 0 (ie no edge)
    for (int v = 0; v < n_vertices; v++) {
      std::vector<int> row(n_vertices_, 0);
      adj_.push_back(row);
    }

    // fill in the edges from the passed in pairs
    for (auto edge : edges) {
      if (edge.first >= n_vertices_ || edge.second >= n_vertices_) {
        throw std::runtime_error("provided edge outside of vertex range!");
      }

      adj_[edge.first][edge.second] = 1;
      if (!directed_) {
        adj_[edge.second][edge.first] = 1;
      }
    }
  }
  std::vector<int> getNeighbors(int v) {
    // search in the matrix along that row
    // for non-zero values
    
    std::vector<int> neighbors;

    for (int n=0; n < n_vertices_; n++){
            if (adj_[v][n] != 0){
                neighbors.push_back(n);
            }
        }
    return neighbors;
  }
};
