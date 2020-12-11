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

    Point GetTopLeft();
    Point GetTopRight();
    Point GetBottomLeft();
    Point GetBottomRight();

    Point GetNeighbour(const char direction);
    Point GetNeighbour(const string& direction);

    vector<Point> GetDirectNeighbours();
    vector<Point> GetAllNeighbours();

    int x{ 0 };
    int y{ 0 };
    int z{ 0 };
  };
}
