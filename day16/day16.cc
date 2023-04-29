#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <compare>
#include <set>
#include <map>
#include <boost/algorithm/string.hpp>

using namespace std;

struct Edge
{
  string dest;
  int weight;
  std::strong_ordering operator<=>(const Edge &) const = default;

  Edge(string d, int w)
  {
    dest = d;
    weight = w;
  }
};

typedef map<string, pair<int, set<Edge>>> Graph;

// Create the final edge set for a node by removing the edges to zero pressure nodes.
// e.g. if AA -> BB -> CC, but BB releases 0 pressure,
// replace AA -> BB edge with an AA -> CC edge with weight 2.
void create_edge_set(set<string> *visited_nodes, string node, Graph *g, set<Edge> *edge_set, int depth)
{
  for (Edge edge : (*g)[node].second)
  {
    if (visited_nodes->contains(edge.dest))
      continue;
    visited_nodes->insert(edge.dest);
    if ((*g)[edge.dest].first == 0) // If this edge leads to a node with zero pressure.
    {
      // Replace this edge with edges leading to this edges dest
      for (Edge e : (*g)[edge.dest].second)
      {
        create_edge_set(visited_nodes, edge.dest, g, edge_set, depth + 1);
      }
    }
    else
    {
      edge_set->emplace(edge.dest, depth);
    }
  }
}

int main()
{
  fstream input;
  input.open("test.txt");
  Graph graph;

  string line;
  while (getline(input, line))
  {
    vector<string> v;
    boost::split(v, line, boost::is_any_of(","));
    set<Edge> edges;
    for (int i = 2; i < v.size(); i++)
      edges.emplace(v[i], 1);

    graph.emplace(v[0], make_pair(stoi(v[1]), edges));
  }

  Graph smol_graph;
  for (auto kv : graph)
  {
    if (kv.second.first == 0)
      continue; //Skip zero pressure nodes.
    set<Edge> es;
    set<string> visited_nodes;
    visited_nodes.insert(kv.first);
    create_edge_set(&visited_nodes, kv.first, &graph, &es, 1);

    smol_graph.emplace(kv.first, make_pair(kv.second.first, es));
  }

}
