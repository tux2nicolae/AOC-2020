#pragma once

/**
 * Advent of code 2020
 * @author : Nicolae Telechi
 */
namespace AOC
{
  struct Point
  {
    Point();
    Point(int x, int y);
    Point(int x, int y, int z);

    bool operator==(const Point& second) const;
    bool operator<(const Point& second) const;

    Point GetLeft();
    Point GetRight();
    Point GetTop();
    Point GetBottom();

    Point GetNeighbour(const char direction);
    vector<Point> GetDirectNeighbours();
    vector<Point> GetAllNeighbours();

    int x{ 0 };
    int y{ 0 };
    int z{ 0 };
  };

  long long Abs(long long number);

  long long ManhattenDistance(int x1, int y1, int x2, int y2);
  long long ManhattenDistance(const Point & a, const Point& b);

  long long Cmmdc(long long n, long long m);
  long long Cmmmc(long long n, long long m);
}
