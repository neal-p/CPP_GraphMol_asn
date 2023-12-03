#pragma once

#include <fstream>

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
    int edge_id = 0;
    for (auto edge : edges) {
      if (edge.first >= n_vertices_ || edge.second >= n_vertices_) {
        throw std::runtime_error("provided edge outside of vertex range!");
      }

      adj_[edge.first][edge.second] = 1;
      edge_ids_[edge] = edge_id;
      if (!directed_) {
        adj_[edge.second][edge.first] = 1;
        edge_ids_[std::pair<int, int>(edge.second, edge.first)] = edge_id;
      }
      edge_id++;
    }
  }

  int addEdge(std::pair<int, int> edge) {
    edges_.push_back(edge);

    edge_ids_[edge] = n_edges_;
    if (!directed_) {
      edge_ids_[std::pair<int, int>(edge.second, edge.first)] = n_edges_;
    }

    n_edges_++;
    adj_[edge.first][edge.second] = 1;
    if (!directed_) {
      adj_[edge.second][edge.first] = 1;
    }

    return n_edges_ - 1;
  }

  int addEdge(int start, int end) {
    return addEdge(std::pair<int, int>(start, end));
  }

  int addVertex() {
    //  Add new vertex to count
    n_vertices_++;

    // add empty attribute for each attribute
    // add empty attribute for each attribute
    for (auto it = v_attr_.begin(); it != v_attr_.end(); it++) {
      // We can clone the first Vertex's attribute
      // which we will create a default value version
      auto first_attr = it->second[0];
      auto cloned = first_attr->clone();
      it->second.push_back(cloned);
    }

    // Add to adjecency matrix
    for (auto& row : adj_) {
      row.push_back(0);
    }

    std::vector<int> empty(n_vertices_, 0);
    adj_.push_back(empty);

    return n_vertices_ - 1;
  }

  std::vector<int> getNeighbors(int v) {
    // search in the matrix along that row
    // for non-zero values

    std::vector<int> neighbors;

    for (int n = 0; n < n_vertices_; n++) {
      if (adj_[v][n] != 0) {
        neighbors.push_back(n);
      }
    }
    return neighbors;
  }

  void printAM() {
    for (auto row : adj_) {
      for (auto edge : row) {
        std::cout << edge << " ";
      }
      std::cout << std::endl;
    }
  }
};

Graph_AM make_Graph_AM(const std::string& file) {
  int n_vertices;
  int id;
  int n_bonds;
  int total_bonds;
  int source;
  int dest;
  std::string atom_type;
  std::ifstream f(file);
  if (!f) {
    std::cout << "Error opening file! " << file << std::endl;
    throw std::runtime_error("Couldnt read file");
  }

  // Get number of atoms as first line
  f >> n_vertices;
  std::vector<std::string> atom_types(n_vertices);

  for (int l = 0; l < n_vertices; l++) {
    f >> id;
    f >> atom_type;
    // need to remove quotes
    atom_type.erase(0, 1);
    atom_type.erase(atom_type.size() - 1);
    f >> n_bonds;
    atom_types[id] = atom_type;
  }

  // Number of bonds
  f >> total_bonds;
  std::vector<std::pair<int, int>> edges;
  edges.reserve(total_bonds);

  for (int b = 0; b < total_bonds; b++) {
    f >> source;
    f >> dest;
    edges.push_back({source, dest});
  }

  return Graph_AM(n_vertices, edges, false);
}
