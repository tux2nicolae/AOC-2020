/**
 * Advent of code 2020
 * @author : Nicolae Telechi
 */
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <algorithm>
#include <array>
#include <vector>
#include <sstream>
#include <fstream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <optional>
#include <numeric>
#include <regex>

#include <assert.h>

using namespace std;

#include "../../AOCLib/src/AOCLib.h"

long long GetActiveNeighboursCount(const map<AOC::Point, bool> & space, const AOC::Point & point)
{
  int activeNeighbours = 0;
  
  // part 1
  // for (const auto& neighbour : point.GetAll3DNeighbours())

  for (const auto & neighbour : point.GetAll4DNeighbours())
  {
    auto it = space.find(neighbour);
    if (it != end(space) && it->second)
      activeNeighbours++;
  }

  return activeNeighbours;
}

int main()
{
  ifstream in("..\\..\\Day17\\src\\_Input.in");
  // ofstream out("..\\..\\Day17\\src\\_Output.out");

  FStreamReader reader(in);
  auto lines = reader.ReadLines();

  map<AOC::Point, bool> space;

  for (int y = 0; y < lines.size(); y++)
  {
    for (int x = 0; x < lines[0].size(); x++)
    {
      space[AOC::Point{ x, y }] = (lines[y][x] == '#');
    }
  }

  map<AOC::Point, bool> nextSpace = space;
  for (int i = 0; i < 6; i++)
  {
    // add all neighbours for next iteration
    for (auto& [point, active] : space)
    {
      // part 1
      // for (const auto& neighbour : point.GetAll3DNeighbours())

      for (auto& neighbour : point.GetAll4DNeighbours())
      {
        if (nextSpace.find(neighbour) == end(nextSpace))
          nextSpace[neighbour] = false;
      }
    }

    // compute data
    for (auto& [nextPoint, nextActive] : nextSpace)
    {
      long long activeNeighbours = GetActiveNeighboursCount(space, nextPoint);
      if (nextActive)
      {
        nextSpace[nextPoint] = activeNeighbours == 2 || activeNeighbours == 3;
      }
      else
      {
        nextSpace[nextPoint] = activeNeighbours == 3;
      }
    }

    space = nextSpace;

    long long activePoints = accumulate(begin(space), end(space), 0LL, [](int acc, auto& pair) {
      return acc + pair.second;
    });

    cout << activePoints << endl;
  }
 

  return 0;
}
