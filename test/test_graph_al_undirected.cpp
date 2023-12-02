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

  Graph_AL g(n_vertices, edges, false);

  // Check number of vertices and edges
  assert(g.getNVertices() == n_vertices);
  assert(g.getNEdges() == n_vertices - 1);

  // First vertex and last vertex have
  // single neighbor, all others have two neighbors
  for (int v = 0; v < n_vertices; v++) {
    auto neighbors = g.getNeighbors(v);

    if (v == 0) {
      assert(neighbors.size() == 1);
      assert(neighbors[0] == 1);

    } else if (v == n_vertices - 1) {
      assert(neighbors.size() == 1);
      assert(neighbors[0] == n_vertices - 2);

    } else {
      assert(neighbors.size() == 2);
      assert(neighbors[0] == v - 1);
      assert(neighbors[1] == v + 1);
    }
  }

  // Add a vertex and check that it has no neighbors
  int new_vertex = g.addVertex();
  assert(g.getNeighbors(new_vertex).size() == 0);

  // Check the BFS, should return no other
  // reachable vertices from our new vertex
  auto all_accessible_from_new = g.BFS(new_vertex);
  assert(all_accessible_from_new.size() == 1);

  // Check the reverse, should find all but new
  // vertex when checking the first vertex
  auto all_accessible_from_start = g.BFS(0);
  std::sort(all_accessible_from_start.begin(), all_accessible_from_start.end());
  assert(all_accessible_from_start.size() == g.getNVertices() - 1);
  int expected = 0;
  for (auto accessible : all_accessible_from_start) {
    assert(expected == accessible);
    expected++;
  }

  // Add a new edge from the new vertex to the first vertex
  // and second vertex
  // check that the edge_id is equal to original n_vertices
  int new_edge1 = g.addEdge(new_vertex, 0);
  int new_edge2 = g.addEdge(new_vertex, 1);
  int new_edge3 = g.addEdge(n_vertices - 1, new_vertex);
  assert(new_edge1 == n_vertices - 1);
  assert(new_edge2 == n_vertices);
  assert(new_edge3 == n_vertices + 1);

  // Check that we can get the proper edge_id
  int retrieved_new_edge_id1 = g.getEdgeBetween(new_vertex, 0);
  int retrieved_new_edge_id2 = g.getEdgeBetween(new_vertex, 1);
  int retrieved_new_edge_id3 = g.getEdgeBetween(n_vertices - 1, new_vertex);
  assert(retrieved_new_edge_id1 == new_edge1);
  assert(retrieved_new_edge_id2 == new_edge2);
  assert(retrieved_new_edge_id3 == new_edge3);

  // Check the updated neighbors
  auto updated_neighbors = g.getNeighbors(new_vertex);
  assert(updated_neighbors.size() == 3);
  assert(updated_neighbors[0] == 0);
  assert(updated_neighbors[1] == 1);
  assert(updated_neighbors[2] == n_vertices - 1);

  // Now all vertices should be accessible with BFS
  auto updated_accessible = g.BFS(0);
  std::sort(updated_accessible.begin(), updated_accessible.end());
  assert(updated_accessible.size() == g.getNVertices());
  expected = 0;
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
    int vertex_id = 0;
    for (auto dist : row) {
      // niave distance
      int straight_forward = abs(row_id - vertex_id);

      // how far is this node from our 'jump' nodes
      int to_vertex0 = abs(row_id - 0) + 1;
      int to_vertex1 = abs(row_id - 1) + 1;
      int to_new_vertex = abs(row_id - new_vertex) + 1;

      // how far is destination from jump
      int vertex0_todest = abs(new_vertex - vertex_id);
      int vertex1_todest = abs(new_vertex - vertex_id);
      int new_vertex_todest1 = abs(0 - vertex_id);
      int new_vertex_todest2 = abs(1 - vertex_id);

      // total distance for jump
      int first_jump = to_vertex0 + vertex0_todest;
      int second_jump = to_vertex1 + vertex1_todest;
      int third_jump = to_new_vertex + new_vertex_todest1;
      int fourth_jump = to_new_vertex + new_vertex_todest2;

      // final distance
      int final_distance = std::min(
          {straight_forward, first_jump, second_jump, third_jump, fourth_jump});

      assert(final_distance == dist);

      vertex_id++;
    }
    row_id++;
  }

  std::cout << "ALL TESTS PASSED" << std::endl;

  return 0;
}
