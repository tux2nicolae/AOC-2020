#pragma once

/**
 * Advent of code 2020
 * @author : Nicolae Telechi
 */
namespace AOC
{
  struct Point
  {
    bool operator==(const Point& second) const;
    bool operator<(const Point& second) const;

    bool IsInBoundary(const Point& from, const Point& to);

    Point GetLeft();
    Point GetRight();
    Point GetTop();
    Point GetBottom();

    Point GetTopLeft();
    Point GetTopRight();
    Point GetBottomLeft();
    Point GetBottomRight();

    Point GetNeighbour(const char direction);
    Point GetNeighbour(const string& direction);

    vector<Point> GetDirectNeighbours();
    vector<Point> GetAllNeighbours();

    long long x{ 0 };
    long long y{ 0 };
    long long z{ 0 };
  };

  template<typename T = long long, typename... Args>
  Point MakePoint(Args... args)
  {
    return Point{ static_cast<T>(args)... };
  };
}
