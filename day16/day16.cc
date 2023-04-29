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

typedef map<pair<string, string>, int> DistMatrix;

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
    if ((*g)[edge.dest].first == 0 && edge.dest != "AA") // If this edge leads to a node with zero pressure.
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

DistMatrix floyd_warshall(Graph *g)
{
  DistMatrix dm;
  // Initialize all to infinity
  for (auto kv : *g)
  {
    for (auto kv2 : *g)
    {
      dm.emplace(make_pair(kv.first, kv2.first), 99999);
    }
  }
  // Set edge weights
  for (auto kv : *g)
  {
    for (Edge e : kv.second.second)
    {
      dm[make_pair(kv.first, e.dest)] = e.weight;
    }
  }
  // Set self weight to 0
  for (auto kv : *g)
  {
    dm[make_pair(kv.first, kv.first)] = 0;
  }
  // Algorithm
  for (auto k : *g)
  {
    for (auto i : *g)
    {
      for (auto j : *g)
      {
        if (dm[make_pair(i.first, j.first)] > dm[make_pair(i.first, k.first)] + dm[make_pair(k.first, j.first)])
          dm[make_pair(i.first, j.first)] = dm[make_pair(i.first, k.first)] + dm[make_pair(k.first, j.first)];
      }
    }
  }
  return dm;
}

void dfs(Graph *g, string node, set<string> *visited_nodes, int *best, int *current, int *time, DistMatrix *dm)
{
  // cout << *time << ' ' << node << endl;
  (*visited_nodes).insert(node);
  // Add total pressure released
  if (node != "AA")
  {
    (*time) += 1; // Takes 1 second to activate
    if (*time > 30)
      return;
    
    // cout << (*g)[node].first <<  "current " << *current << " " << *time << endl;
    (*current) += ((*g)[node].first * (30-(*time)));
    (*best) = max(*best,*current);
    // cout << "current " << *current << endl;
  }

  // Walk an edge
  for (auto kv : (*g))
  {
    if (kv.first == node || (*dm).find(make_pair(node,kv.first)) == (*dm).end())
      continue;
    int weight = (*dm)[make_pair(node,kv.first)];

    // cout << *time << kv.first << weight << (*visited_nodes).count(kv.first) << endl;
    // if we can get there in time and we havent visited there yet (on this path)
    if (*time + weight < 30 && ((*visited_nodes).count(kv.first) == 0))
    {
      (*time) += weight;
      dfs(g, kv.first, visited_nodes, best, current, time, dm);
      (*time) -= weight;
    }
  }

  // Step back out of this node
  (*current) -= (*g)[node].first * (30-*time);
  (*time) -= 1;
  (*visited_nodes).erase(node);
}

int main()
{
  fstream input;
  input.open("input.txt");
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

  // Remove zero pressure nodes.
  Graph smol_graph;
  for (auto kv : graph)
  {
  if (kv.second.first == 0 && kv.first != "AA")
    continue; // Skip zero pressure nodes.
  set<Edge> es;
  set<string> visited_nodes;
  visited_nodes.insert(kv.first);
  create_edge_set(&visited_nodes, kv.first, &graph, &es, 1);

  smol_graph.emplace(kv.first, make_pair(kv.second.first, es));
  }

  // cout << smol_graph.size() << endl;
  // for (Edge e : smol_graph["AA"].second)
  // {
  //   cout << e.dest << e.weight << endl;
  // }

  // Backtrack from "AA" starting node to find optimal path.
  // i.e. the path that releases the most pressure in 30 time steps.
  set<string> visited_nodes;
  int best = 0;
  int current = 0;
  int time = 0;
  DistMatrix dm = floyd_warshall(&smol_graph);
  dfs(&smol_graph, "AA", &visited_nodes, &best, &current, &time, &dm);
  cout << "Part 1: " << best << endl;
  // cout << "current " << current << endl;

  // for (auto i : smol_graph)
  // {
  //   cout << dm[make_pair("AA", i.first)] << i.first << endl;
  // }
}
