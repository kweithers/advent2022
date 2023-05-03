#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <compare>
#include <set>
#include <queue>
#include <boost/algorithm/string.hpp>

using namespace std;

const int N = 25;

struct Point
{
  int x, y, z;
  auto operator<=>(const Point &) const = default;

  Point(int a, int b, int c)
  {
    x = a;
    y = b;
    z = c;
  }
};

set<Point> sides(Point p)
{
  set<Point> s;
  s.emplace(p.x + 1, p.y, p.z);
  s.emplace(p.x - 1, p.y, p.z);
  s.emplace(p.x, p.y + 1, p.z);
  s.emplace(p.x, p.y - 1, p.z);
  s.emplace(p.x, p.y, p.z + 1);
  s.emplace(p.x, p.y, p.z - 1);
  return s;
}

int main()
{
  fstream input;
  input.open("input.txt");

  bool grid[N][N][N] = {false};
  int surface_area = 0;

  set<Point> cubes;
  string line;
  while (getline(input, line))
  {
    vector<string> v;
    boost::split(v, line, boost::is_any_of(","));
    int x = stoi(v[0]) + 1, y = stoi(v[1]) + 1, z = stoi(v[2]) + 1;
    grid[x][y][z] = true;
    cubes.emplace(x, y, z);

    surface_area += 6;
    surface_area -= 2 * (grid[x + 1][y][z] + grid[x - 1][y][z] + grid[x][y + 1][z] + grid[x][y - 1][z] + grid[x][y][z + 1] + grid[x][y][z - 1]);
  }
  cout << "Part 1: " << surface_area << endl;

  // Part 2
  set<Point> seen;
  queue<Point> todo;
  set<Point> todo_set;

  todo.emplace(0, 0, 0);
  todo_set.emplace(0, 0, 0);
  while (todo.size() > 0)
  {
    Point here = todo.front();
    todo.pop();

    set<Point> s = sides(here);
    for (Point cube : cubes)
      s.erase(cube);
    for (Point se : seen)
      s.erase(se);

    for (Point side : s)
    {
      if (side.x >= 0 && side.x <= N && side.y >= 0 && side.y <= N && side.z >= 0 && side.z <= N && todo_set.count(side) == 0)
      {
        todo.push(side);
        todo_set.insert(side);
      }
    }
    seen.insert(here);
  }

  int part2 = 0;
  for (Point c : cubes)
  {
    for (Point s : sides(c))
    {
      if (seen.contains(s))
        part2++;
    }
  }
  cout << "Part 2: " << part2 << endl;
}