#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <compare>
#include <set>
#include <boost/algorithm/string.hpp>

using namespace std;

struct Point
{
  int y, x;
  auto operator<=>(const Point &) const = default;
};

int dist(Point *p1, Point *p2)
{
  return abs(p1->x - p2->x) + abs(p1->y - p2->y);
}

int main()
{
  fstream input;
  input.open("input.txt");

  const int row = 2000000; // 10 for test, 2000000 for real

  string line;
  Point sensor, beacon;

  set<int> s, positive_coefs, negative_coefs;
  vector<pair<Point, int>> sensors;
  while (getline(input, line))
  {
    vector<string> v;
    boost::split(v, line, boost::is_any_of(","));

    sensor.x = stoi(v[0]);
    sensor.y = stoi(v[1]);
    beacon.x = stoi(v[2]);
    beacon.y = stoi(v[3]);

    int d = dist(&sensor, &beacon);
    int y_diff = abs(row - sensor.y);

    sensors.emplace_back(sensor, d);

    // Part 1
    for (int x = -d + y_diff; x <= d - y_diff; x++)
    {
      s.emplace(sensor.x + x);
    }

    // Part 2: Every beacon diamond is defined by four line segments
    // Two with positive slope, and two with negative slope.
    positive_coefs.emplace(sensor.y - sensor.x + d + 1);
    positive_coefs.emplace(sensor.y - sensor.x - d - 1);
    negative_coefs.emplace(sensor.x + sensor.y + d + 1);
    negative_coefs.emplace(sensor.x + sensor.y - d - 1);
  }

  cout << "Part 1: " << s.size() - 1 << endl; // minus 1 since 1 beacon in this row

  // Part 2: Find interecting line segments
  // One of these intersecting points must be our point!
  int bound = 4000000;
  for (int a : positive_coefs)
  {
    for (int b : negative_coefs)
    {
      Point p;
      p.x = (b - a) / 2;
      p.y = (a + b) / 2;

      if (0 < p.x && p.x < bound && 0 < p.y && p.y < bound)
      {
        int n = 0;
        for (auto sensor_radius_pair : sensors)
        {
          if (dist(&p, &sensor_radius_pair.first) > sensor_radius_pair.second)
            n++;
        }
        if (n == sensors.size())
          cout << "Part 2: " << 4000000 * (unsigned long)p.x + p.y << endl;
      }
    }
  }
}