#pragma once

/**
 * Advent of code 2020
 * @author : Nicolae Telechi
 */
namespace AOC
{
  class Point;

  long long Abs(long long number);

  long long ManhattenDistance(int x1, int y1, int x2, int y2);
  long long ManhattenDistance(const Point & a, const Point& b);

  long long Cmmdc(long long n, long long m);
  long long Cmmmc(long long n, long long m);
}
