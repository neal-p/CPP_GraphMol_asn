#pragma once

#include <algorithm>
#include <fstream>

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
    int edge_id = 0;
    for (auto edge : edges) {
      if (edge.first >= n_vertices_ || edge.second >= n_vertices_) {
        throw std::runtime_error("provided edge outside of vertex range!");
      }

      adj_[edge.first].push_back(edge.second);
      edge_ids_[edge] = edge_id;
      if (!directed_) {
        adj_[edge.second].push_back(edge.first);
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
    adj_[edge.first].push_back(edge.second);
    if (!directed_) {
      adj_[edge.second].push_back(edge.first);
    }
    return n_edges_ - 1;
  }

  int addEdge(int start, int end) {
    return addEdge(std::pair<int, int>(start, end));
  }

  int addVertex() {
    // Add new vertex to count
    n_vertices_++;

    // add empty attribute for each attribute
    for (auto it = v_attr_.begin(); it != v_attr_.end(); it++) {
      // We can clone the first Vertex's attribute
      // which we will create a default value version
      auto first_attr = it->second[0];
      auto cloned = first_attr->clone();
      it->second.push_back(cloned);
    }

    // Add empty adjacency list
    std::vector<int> neighbors;
    adj_.push_back(neighbors);

    return n_vertices_ - 1;
  }

  std::vector<int> getNeighbors(int v) { return adj_[v]; }
};

// Found that we need to clean up the atom types
void cleanString(std::string& atom) {
  // std::cout << "before: " << atom << std::endl;

  // Remove non-alphabetic ASCII characters
  atom.erase(std::remove_if(atom.begin(), atom.end(),
                            [](unsigned char c) { return !std::isalpha(c); }),
             atom.end());

  // std::cout << "after: " << atom << std::endl;
}

Graph_AL make_Graph_AL(const std::string& file) {
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
    cleanString(atom_type);
    f >> n_bonds;
    atom_types[id] = atom_type;
    atom_type.clear();
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

  Graph_AL g = Graph_AL(n_vertices, edges, false);
  g.addVertexAttributes<std::string>("atom_type", atom_types);

  return g;
}
