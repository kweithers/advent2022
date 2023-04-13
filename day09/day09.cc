#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <compare>
#include <boost/algorithm/string.hpp>
#include <cstdlib>

using namespace std;

struct Point
{
  int y, x;
  auto operator<=>(const Point &) const = default;
};

struct Rope
{
  Point head, tail;
  set<Point> visited_points;
  Rope()
  {
    head = Point();
    tail = Point();
    visited_points.insert(tail);
  }

  bool head_and_tail_touching()
  {
    int x_dist = abs(head.x - tail.x);
    int y_dist = abs(head.y - tail.y);
    return x_dist < 2 && y_dist < 2;
  }

  void move_head(char direction) // R, L, D, U
  {
    if (direction == 'R')
    {
      head.x++;
    }
    else if (direction == 'L')
    {
      head.x--;
    }
    else if (direction == 'U')
    {
      head.y++;
    }
    else if (direction == 'D')
    {
      head.y--;
    }
    else
    {
      printf("bad direction - exiting");
      exit(1);
    }
  }

  void move_tail(char direction) // If necessary!
  {
    if (head_and_tail_touching())
    {
      return;
    }
    if (direction == 'R')
    {
      tail.x = head.x - 1;
      tail.y = head.y;
    }
    else if (direction == 'L')
    {
      tail.x = head.x + 1;
      tail.y = head.y;
    }
    else if (direction == 'U')
    {
      tail.x = head.x;
      tail.y = head.y - 1;
    }
    else if (direction == 'D')
    {
      tail.x = head.x;
      tail.y = head.y + 1;
    }
  }

  void move(char direction)
  {
    move_head(direction);
    move_tail(direction);
    visited_points.insert(tail);
  }
};

int main()
{
  fstream input;
  input.open("input.txt");

  Rope rope;
  printf("Head: %d %d Tail: %d %d\n", rope.head.x, rope.head.y, rope.tail.x, rope.tail.y);

  string line;
  while (getline(input, line))
  {
    vector<string> v;
    boost::split(v, line, boost::is_any_of(" "));
    cout << v[0] << v[1] << endl;
    for (int i = 0; i < stoi(v[1]); i++)
    {
      rope.move(v[0].front());
      printf("Head: %d %d Tail: %d %d\n", rope.head.x, rope.head.y, rope.tail.x, rope.tail.y);
    }
  }
  printf("Part 1: %lu\n", rope.visited_points.size());
}