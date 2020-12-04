/**
 * Advent of code 2019
 * @author : Nicolae Telechi
 */
#include "pch.h"
#include "Math.h"

//------------------------------------------------------------

inline AOC::Point::Point()
{
}

inline AOC::Point::Point(int x, int y)
  : x(x), y(y)
{
}

inline AOC::Point::Point(int x, int y, int z)
  : x(x), y(y), z(z)
{
}

bool AOC::Point::operator==(const Point& second) const
{
  return tie(x, y, z) == tie(second.x, second.y, second.z);
};

bool AOC::Point::operator<(const Point& second) const
{
  return tie(x, y, z) < tie(second.x, second.y, second.z);
};

//------------------------------------------------------------

long long AOC::Abs(long long number)
{
  return number > 0 ? number : -number;
}

long long AOC::ManhattenDistance(int x1, int y1, int x2, int y2)
{
  return Abs(x1 - x2) + Abs(y1 - y2);
}

long long AOC::ManhattenDistance(const Point& a, const Point& b)
{
  return AOC::ManhattenDistance(a.x, a.y, b.x, b.y);
}

long long AOC::Cmmdc(long long n, long long m)
{
  if (n == 0)
    return m;

  return Cmmdc(m % n, n);
}

long long AOC::Cmmmc(long long n, long long m)
{
  return (n * m) / Cmmdc(n, m);
}