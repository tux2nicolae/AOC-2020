/**
 * Advent of code 2020
 * @author : Nicolae Telechi
 */
#include "pch.h"
#include "Math.h"

//------------------------------------------------------------

AOC::Point::Point()
{
}

AOC::Point::Point(int x, int y)
  : x(x), y(y)
{
}

AOC::Point::Point(int x, int y, int z)
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

AOC::Point AOC::Point::GetLeft() 
{
  return { x - 1, y, z };
}

AOC::Point AOC::Point::GetRight() 
{
  return { x + 1, y, z };
}

AOC::Point AOC::Point::GetTop() 
{
  return { x, y - 1, z };
}

AOC::Point AOC::Point::GetBottom() 
{
  return { x, y + 1, z };
}

AOC::Point AOC::Point::GetNeighbour(const char direction) {
  switch (direction)
  {
  case '<':
  case  'L':
  case 'l':
  case 'W':
  case 'w':
    return GetLeft();
  case '>':
  case  'R':
  case 'r':
  case 'E':
  case 'e':
    return GetRight();
  case '^':
  case  'T':
  case 't':
  case 'N':
  case 'n':
    return GetTop();
  case 'v':
  case  'B':
  case 'b':
  case 'S':
  case 's':
    return GetBottom();
  default:
    assert("Invalid direction");
    return {};
  }
};

vector<AOC::Point> AOC::Point::GetDirectNeighbours() 
{
  return { GetTop(), GetRight(), GetBottom(), GetLeft() };
}

vector<AOC::Point> AOC::Point::GetAllNeighbours()
{
  return { GetTop(), GetTop().GetRight(), GetRight(), GetBottom().GetRight(), 
    GetBottom(), GetBottom().GetLeft(), GetLeft(), GetTop().GetLeft()};
}

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