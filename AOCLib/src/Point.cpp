/**
 * Advent of code 2020
 * @author : Nicolae Telechi
 */
#include "pch.h"
#include "Point.h"

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

AOC::Point AOC::Point::GetTopLeft()
{
  return GetTop().GetLeft();
}

AOC::Point AOC::Point::GetTopRight()
{
  return GetTop().GetRight();
}

AOC::Point AOC::Point::GetBottomLeft()
{
  return GetBottom().GetLeft();
}

AOC::Point AOC::Point::GetBottomRight()
{
  return GetBottom().GetRight();
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
  case 'U':
  case 'u':
    return GetTop();
  case 'v':
  case  'B':
  case 'b':
  case 'S':
  case 's':
  case 'D':
  case 'd':
    return GetBottom();
  default:
    assert("Invalid direction");
    return {};
  }
};

AOC::Point AOC::Point::GetNeighbour(const string& direction)
{
  auto neighbour = *this;
  for (auto to : direction)
    neighbour = neighbour.GetNeighbour(to);

  return neighbour;
};

vector<AOC::Point> AOC::Point::GetDirectNeighbours()
{
  return { GetTop(), GetRight(), GetBottom(), GetLeft() };
}

vector<AOC::Point> AOC::Point::GetAllNeighbours()
{
  return { GetTop(), GetTopRight(), GetRight(), GetBottomRight(),
    GetBottom(), GetBottomLeft(), GetLeft(), GetTopLeft() };
}

//------------------------------------------------------------