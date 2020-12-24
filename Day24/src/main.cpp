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
#include <queue>
#include <deque>

#include <assert.h>

using namespace std;

#include "../../AOCLib/src/AOCLib.h"

struct FlipTile
{
  void GoEast() { 
    position += { -1, 0 };
  };

  void GoWest()
  {
    position += { 1, 0 };
  };

  void GoNorthWest()
  {
    position += { 0, 1 };
  };
  
  void GoNorthEast()
  {
    position += { -1, 1 };
  };
  
  void GoSouthWest() {
    position += { 1, -1 };
  };
  
  void GoSouthEast() 
  {
    position += { 0, -1 };
  };

  vector<AOC::Point> GetNeighbours()
  {
    vector<AOC::Point> neighbours;

    FlipTile temp = *this;
    temp.GoEast();

    neighbours.push_back(temp.position);

    temp = *this;
    temp.GoWest();

    neighbours.push_back(temp.position);

    temp = *this;
    temp.GoNorthEast();

    neighbours.push_back(temp.position);

    temp = *this;
    temp.GoNorthWest();

    neighbours.push_back(temp.position);

    temp = *this;
    temp.GoSouthEast();

    neighbours.push_back(temp.position);

    temp = *this;
    temp.GoSouthWest();

    neighbours.push_back(temp.position);
    return neighbours;
  }

  void Go() {
    for (auto& to : directions)
    {
      if (to == "e")
        GoEast();
      else if (to == "w")
        GoWest();
      else if (to == "nw")
        GoNorthWest();
      else if (to == "ne")
        GoNorthEast();
      else if (to == "sw")
        GoSouthWest();
      else if (to == "se")
        GoSouthEast();
    }
  }

  string tile;
  vector<string> directions;

  AOC::Point position;
};


bool AreEqual(FlipTile & firstTile, FlipTile & secondTile)
{
  AOC::Point origin{ 0, 0 };
  return (origin.GetNeighbour(firstTile.tile) == origin.GetNeighbour(secondTile.tile));
}

int main()
{
  ifstream in("..\\..\\Day24\\src\\_Input.in");
  ofstream out("..\\..\\Day24\\src\\_Output.out");

  FStreamReader reader(in);
  auto lines = reader.ReadLines();

  vector<FlipTile> flipTiles;

  for (auto& line : lines)
  {
    vector<string> flipTile;

    string_view window(line);
    while (!window.empty())
    {
      if (window.starts_with("se") || window.starts_with("sw") ||
        window.starts_with("nw") || window.starts_with("ne"))
      {
        flipTile.push_back(string{ window.substr(0, 2) });
        window.remove_prefix(2);
        continue;
      }

      flipTile.push_back(string{ window.substr(0, 1) });
      window.remove_prefix(1);
    }

    flipTiles.push_back(FlipTile{line, flipTile});
  }


  map<AOC::Point, int> tiles;

  AOC::Point origin{ 0, 0 };
  for (auto& firstTile : flipTiles)
  {
    firstTile.Go();
    tiles[firstTile.position]++;
  }

  set<AOC::Point> floor;

  int s = 0;
  for (auto& [_, nr] : tiles)
  {
    if (nr % 2 == 1)
    {
      floor.insert(_);
      s++;
    }
  }

  cout << s << endl;

  for (int i = 0; i < 100; i++)
  {
    set<AOC::Point> nextFloor;
    
    for (auto tilePosition : floor)
    {
      FlipTile tile;
      tile.position = tilePosition;

      auto compute = [&](const AOC::Point & nextTilePosition) {
        FlipTile nextTile;
        nextTile.position = nextTilePosition;

        auto neighbours = nextTile.GetNeighbours();
        auto blackNeighbours = std::accumulate(begin(neighbours), end(neighbours), 0ULL, [&](size_t acc, AOC::Point point)
          {
            return acc + floor.count(point);
          });

        bool isBlack = floor.count(nextTilePosition);

        if ((isBlack && (blackNeighbours == 1 || blackNeighbours == 2))
          || (!isBlack && blackNeighbours == 2))
        {
          nextFloor.insert(nextTilePosition);
        }
      };

      compute(tilePosition);

      for (auto nextTilePosition : tile.GetNeighbours())
      {
        compute(nextTilePosition);
      }
    }
    
    floor = nextFloor;
  }

  cout << floor.size() << endl;

  return 0;
}
