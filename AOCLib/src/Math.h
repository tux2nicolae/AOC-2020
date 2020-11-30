#pragma once

/**
 * Advent of code 2019
 * @author : Nicolae Telechi
 */
namespace AOC
{
  struct Point
  {
    int x{ 0 };
    int y{ 0 };

    bool operator==(const Point& second) const
    {
      return tie(x, y) == tie(second.x, second.y);
    };

    bool operator<(const Point& second) const
    {
      return tie(x, y) < tie(second.x, second.y);
    };
  };

  long long Abs(long long number);

  long long ManhattenDistance(int x1, int y1, int x2, int y2);
  long long ManhattenDistance(const Point & a, const Point& b);

  long long Cmmdc(long long n, long long m);
  long long Cmmmc(long long n, long long m);
}
