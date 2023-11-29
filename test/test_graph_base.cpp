#include <assert.h>
#include <algorithm>

#include "graph_al.h"

int main() {
  // Test basic directed graph creation
  int n_vertices = 5;

  std::vector<std::pair<int, int>> edges;
  for (int e = 0; e < n_vertices - 1; e++) {
    edges.push_back(std::make_pair(e, e + 1));
  }

  Graph_AL g(n_vertices, edges, true);

  // Check number of vertices and edges
  assert(g.getNVertices() == n_vertices);
  assert(g.getNEdges() == n_vertices - 1);

  // Each vertex should have a single neighbor
  // which is the next id (except for the last)
  for (int v = 0; v < n_vertices; v++) {
    auto neighbors = g.getNeighbors(v);

    if (v == n_vertices - 1) {
      assert(neighbors.size() == 0);
    } else {
      assert(neighbors.size() == 1);
      assert(neighbors[0] == v + 1);
    }
  }

  // Add a vertex and check that it has no neighbors
  int new_vertex = g.addVertex();
  assert(g.getNeighbors(new_vertex).size() == 0);

  // Check the BFS, should return no other
  // reachable vertices from our new vertex
  auto all_accessible_from_new = g.BFS(new_vertex);
  assert(all_accessible_from_new.size() == 0);

  // Check the reverse, should find all but new
  // vertex when checking the first vertex
  auto all_accessible_from_start = g.BFS(0);
  std::sort(all_accessible_from_start.begin(), all_accessible_from_start.end());
  assert(all_accessible_from_start.size() == g.getNVertices() - 1);
  int expected = 1;
  for (auto accessible : all_accessible_from_start) {
    assert(expected == accessible);
    expected++;
  }

  // Add a new edge from the new vertex to the first vertex
  // and second vertex
  // check that the edge_id is equal to original n_vertices
  int new_edge1 = g.addEdge(new_vertex, 0);
  int new_edge2 = g.addEdge(new_vertex, 1);
  assert(new_edge1 == n_vertices);
  assert(new_edge2 == n_vertices + 1);

  // Check that we can get the proper edge_id
  int retrieved_new_edge_id1 = g.getEdgeBetween(new_vertex, 0);
  int retrieved_new_edge_id2 = g.getEdgeBetween(new_vertex, 1);
  assert(retrieved_new_edge_id1 == new_edge1);
  assert(retrieved_new_edge_id2 == new_edge2);

  // Check the updated neighbors
  auto updated_neighbors = g.getNeighbors(new_vertex);
  assert(updated_neighbors.size() == 2);
  assert(updated_neighbors[0] == 0);
  assert(updated_neighbors[1] == 1);

  // Now all vertices should be accessible with BFS
  auto updated_accessible = g.BFS(0);
  std::sort(updated_accessible.begin(), updated_accessible.end());
  assert(updated_accessible.size() == g.getNVertices());
  expected = 1;
  for (auto accessible : updated_accessible) {
    assert(expected == accessible);
    expected++;
  }

  // Check the final distance matrix

  // 0 - 1 - 2 - 3 - n - newV
  // |   |                | |
  // |   -----------------  |
  //  _____________________ |

  auto distmat = g.getDistanceMatrix();
  int row_id = 0;
  for (auto row : distmat) {
    int item = 0;
    for (auto dist : row) {
      if (item >= row_id) {
        assert((item - row_id) == dist);
      }
      // if vertex is before, then need to
      // wrap around
      else {
        int to_end = g.getNVertices() - row_id;
        int from_start = item - row_id;
        assert((to_end + from_start) == dist);
      }
      item++;
    }
  }

  return 0;
}
