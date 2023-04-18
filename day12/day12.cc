#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <compare>
#include <map>

using namespace std;

struct Point
{
  int y, x;
  auto operator<=>(const Point &) const = default;
};

struct Edge
{
  Point dest;
  int weight;

  Edge(int y, int x, int w)
  {
    dest = Point{y, x};
    weight = w;
  }
};

struct Node
{
  Point p;
  vector<Edge> edges;
};

struct Graph
{
  vector<Node> nodes;
  Point source;
  map<Point, int> dist;
  map<Point, Node> point_node_map;

  void dijkstra()
  {
    dist[source] = 0;

    priority_queue<pair<int, Point>, vector<pair<int, Point>>, greater<pair<int, Point>>> pq;

    for (auto n : nodes)
    {
      point_node_map[n.p] = n;
      if (n.p != source)
      {
        dist[n.p] = 99999; // Don't set to INT_MAX or alt = dist[u.p] + v.weight will overflow!
      }

      pq.emplace(dist[n.p], n.p);
    }

    while (!pq.empty())
    {
      auto uu = pq.top();
      pq.pop();
      auto u = point_node_map[uu.second];

      for (auto v : u.edges)
      {
        int alt = dist[u.p] + v.weight;

        if (alt < dist[v.dest])
        {
          dist[v.dest] = alt;
          pq.emplace(alt, v.dest); // Instead of decrease_key just add new copy
        }
      }
    }
  }
};

Graph create_graph(vector<vector<char>> grid, Point source)
{
  Graph g;
  g.source = source;
  vector<Node> nodes;

  for (int j = 0; j < grid.size(); j++)
  {
    for (int i = 0; i < grid[j].size(); i++)
    {
      Node n;
      n.p = Point{j, i};

      // Check up
      if (j != 0)
      {
        if (grid[j - 1][i] + 1 >= grid[j][i])
        {
          n.edges.emplace_back(j - 1, i, 1);
        }
      }
      // Check down
      if (j != grid.size() - 1)
      {
        if (grid[j + 1][i] + 1 >= grid[j][i])
        {
          n.edges.emplace_back(j + 1, i, 1);
        }
      }
      // Check left
      if (i != 0)
      {
        if (grid[j][i - 1] + 1 >= grid[j][i])
        {
          n.edges.emplace_back(j, i - 1, 1);
        }
      }
      // Check right
      if (i != grid[j].size() - 1)
      {
        if (grid[j][i + 1] + 1 >= grid[j][i])
        {
          n.edges.emplace_back(j, i + 1, 1);
        }
      }
      nodes.push_back(n);
    }
  }

  g.nodes = nodes;
  return g;
}

int main()
{
  fstream input;
  input.open("input.txt");
  vector<vector<char>> grid;

  string line;
  while (getline(input, line))
  {
    vector<char> v(line.begin(), line.end());
    grid.push_back(v);
  }

  grid[20][0] = 'a';   // Dest
  grid[20][120] = 'z'; // Source
  Graph g = create_graph(grid, Point{20, 120});

  g.dijkstra();

  cout << "Part 1: " << g.dist[Point{20, 0}] << endl;

  // Find shortest path to any point with elevation 'a'
  auto part2 = INT_MAX;
  for (auto y = 0; y < grid.size(); y++)
  {
    for (auto x = 0; x < grid[y].size(); x++)
    {
      if (grid[y][x] == 'a')
      {
        part2 = min(part2, g.dist[Point{y, x}]);
      }
    }
  }

  cout << "Part 2: " << part2 << endl;
}
