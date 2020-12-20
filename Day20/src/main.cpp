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

struct Border
{
  string border;
};

struct Tile
{
  int id;
  vector<string> image;



  void Flip()
  {
    vector<string> reverseImage;

    for (const auto& line : image)
      reverseImage.push_back({ rbegin(line), rend(line) });

    image = reverseImage;
  };

  void Rotate()
  {
    vector<string> rotatedImage = image;

    for (int i = 0; i < image.size(); i++)
    {
      for (int j = 0; j < image.size(); j++)
      {
        rotatedImage[j][image.size() - 1 - i] = image[i][j];
      }
    }

    image = rotatedImage;
  };

  void RemoveBorders()
  {
    image.erase(image.begin());
    image.pop_back();

    for (auto& line : image)
    {
      line.erase(0, 1);
      line.pop_back();
    }
  }

  string GetRighBorder()
  {
    // right
    string rightColumn;
    for (int i = 0; i < image.size(); i++)
    {
      rightColumn += image[i][image.size() - 1];
    }

    return rightColumn;
  };

  string GetLeftBorder()
  {
    // left
    // string leftColumn;
    // for (int i = image.size() - 1; i >= 0; i--)
    // {
    //   leftColumn += image[i][0];
    // }

    string leftColumn;
    for (int i = 0; i < image.size(); i++)
    {
      leftColumn += image[i][0];
    }

    return leftColumn;
  };


  string GetTopBorder()
  {
    // top
    return image.front();
  };

  string GetBottomBorder()
  {
    // bottom
    // string bottomColumn;
    // for (int i = image.size() - 1; i >= 0; i--)
    // {
    //   bottomColumn += image[image.size() - 1][i];
    // }

    return image.back();
  };

  vector<string> GetBorders() 
  {
    return { GetTopBorder(), GetRighBorder(), GetBottomBorder(), GetLeftBorder() };
  };

  vector<string> GetReverseBorders()
  {
    vector<string> reverseBorders;

    for (const auto& border : GetBorders())
      reverseBorders.push_back({rbegin(border), rend(border)});

    return reverseBorders;
  }
};

int CountMatchingBorders(const vector<string>& firstBorders, const vector<string>& secondBorders)
{
  int s = 0;
  for (auto& firstBorder : firstBorders)
  {
    for (auto& secondBorderd : secondBorders)
    {
      if (firstBorder == secondBorderd)
      {
        s++;
      }
    }
  }

  return s;
}

int main()
{
  ifstream in("..\\..\\Day20\\src\\_Input.in");
  ofstream out("..\\..\\Day20\\src\\_Output.out");

  FStreamReader reader(in);
  auto lines = reader.ReadLines();

  vector<Tile> tiles;
  unordered_map<int, Tile> tilesById;

  size_t lineIndex = 0;
  Tile tile;

  // parse rules
  while (lineIndex < lines.size())
  {
    auto& line = lines[lineIndex++];
    if (line.empty())
    {
      tiles.push_back(tile);
      tilesById[tile.id] = tile;
      tile = {};
      continue;
    }


    if (line.find("Tile") != string::npos)
    {
      auto maches = AOC::ExtractMatches(line, "Tile ([0-9]*):");
      assert(maches.size() == 2);

      tile.id = stoi(maches[1]);
    }
    else
    {
      tile.image.push_back(line);
    }
  }

  vector<int> corners;

  struct Node
  {
    int priority{ 0 };
    vector<int> neighbours;
  };

  unordered_map<int, Node> initialGraph;
  unordered_map<int, int> machingLines;

  for (int i = 0; i < tiles.size(); i++)
  {
    for (int j = 0; j < tiles.size(); j++)
    {
      if (i == j)
        continue;

      auto& first = tiles[i];
      auto& second = tiles[j];

      // mach borders
      int matchBorders = CountMatchingBorders(first.GetBorders(), second.GetBorders());
      matchBorders += CountMatchingBorders(first.GetBorders(), second.GetReverseBorders());
      assert(matchBorders <= 1);

      int matchReverseBorders = CountMatchingBorders(first.GetReverseBorders(), second.GetBorders());
      matchReverseBorders += CountMatchingBorders(first.GetReverseBorders(), second.GetReverseBorders());
      assert(matchReverseBorders <= 1);

      // only in one direction
      assert(matchBorders + matchReverseBorders == 2 || matchBorders + matchReverseBorders == 0);

      bool isNeighbour = (matchBorders + matchReverseBorders == 2);

      // create graph
      if (isNeighbour)
      {
        machingLines[first.id]++;
        initialGraph[first.id].neighbours.push_back(second.id);
      }
    }
  }

  for (auto [matchingId, matchingCount] : machingLines)
  {
    if (matchingCount == 2)
      corners.push_back(matchingId);
  }

  auto transformCirularIndex = [](const int index, const int maxSize) -> pair<int, int>
  {
    // forward
    if ((index / maxSize) % 2 == 0)
    {
      return make_pair(index / maxSize, index % maxSize);
    }
    // backward
    else
    {
      return make_pair(index / maxSize, maxSize - (index % maxSize) - 1);
    }
  };

  // 3359
  // 2833
  // 1367
  // 2239

  auto graph = initialGraph;
  auto nodeId = 2833; // corners.front();

  int traversIndex = 0;
  vector<vector<int>> orderedImageTiles(sqrt(tiles.size()), vector<int>(sqrt(tiles.size()), 0));

  while (true)
  {
    auto position = transformCirularIndex(traversIndex++, sqrt(tiles.size()));
    orderedImageTiles[position.first][position.second] = nodeId;

    // stop condition
    auto& nodeRef = graph[nodeId];
    if (nodeRef.neighbours.empty())
      break;

    // erase ourselves from our neighbours
    for (auto& neighbourId : nodeRef.neighbours)
    {
      auto& neigbourRef = graph[neighbourId];
      neigbourRef.neighbours.erase(
        find(neigbourRef.neighbours.begin(), neigbourRef.neighbours.end(), nodeId));
    }

    // get the next neigbour with the minimum number of neigbours
    auto nextNodeIdIt = min_element(begin(nodeRef.neighbours), end(nodeRef.neighbours),
      [&](int firstId, int secondId)
      {
        auto first = graph[firstId];
        auto second = graph[secondId];

        if (first.priority == second.priority)
          return first.neighbours.size() < second.neighbours.size();

        // greater priority for the leftmost element
        return first.priority > second.priority;
      });

    // set neigbours priority
    for (auto& neighbourId : nodeRef.neighbours)
    {
      auto& neigbourRef = graph[neighbourId];
      neigbourRef.priority = 1;
    }

    assert(nextNodeIdIt != end(nodeRef.neighbours));
    nodeId = *nextNodeIdIt;
  }

  tilesById;
  orderedImageTiles;

  // fliped and rotated tiles
  auto processedTiles = tilesById;

  auto& firstCorner = processedTiles[orderedImageTiles[0][0]];

  //
  //
  // firstCorner.Flip();
  // firstCorner.Rotate();
  // firstCorner.Rotate();


  // flip and rotate first row
  for (int i = 1; i < sqrt(tiles.size()); i++)
  {
    auto& previousTileRef = processedTiles[orderedImageTiles[0][i - 1]];
    auto& currentTileRef = processedTiles[orderedImageTiles[0][i]];

    int maxRotations = 3;
    while (maxRotations-- && previousTileRef.GetRighBorder() != currentTileRef.GetLeftBorder())
      currentTileRef.Rotate();

    if (previousTileRef.GetRighBorder() != currentTileRef.GetLeftBorder())
    {
      currentTileRef.Flip();

      int maxRotations = 3;
      while (maxRotations-- && previousTileRef.GetRighBorder() != currentTileRef.GetLeftBorder())
        currentTileRef.Rotate();

      assert(previousTileRef.GetRighBorder() == currentTileRef.GetLeftBorder());
    }
  }

  // flip next rows
  for (int i = 1; i < sqrt(tiles.size()); i++)
  {
    for (int j = 0; j < sqrt(tiles.size()); j++)
    {
      auto& topTileRef = processedTiles[orderedImageTiles[i - 1][j]];
      auto& currentTileRef = processedTiles[orderedImageTiles[i][j]];

      int maxRotations = 5;
      while (maxRotations-- && topTileRef.GetBottomBorder() != currentTileRef.GetTopBorder())
        currentTileRef.Rotate();

      if (topTileRef.GetBottomBorder() != currentTileRef.GetTopBorder())
      {
        currentTileRef.Flip();

        int maxRotations = 5;
        while (maxRotations-- && topTileRef.GetBottomBorder() != currentTileRef.GetTopBorder())
          currentTileRef.Rotate();

        assert(topTileRef.GetBottomBorder() == currentTileRef.GetTopBorder());
      }
    }
  }

  // remove borders and order
  vector<vector<Tile>> finalTiles;
  for (int i = 0; i < orderedImageTiles.size(); i++)
  {
    vector<Tile> tileRow;
    for (int j = 0; j < orderedImageTiles.size(); j++)
    {
      auto& orderedTile = processedTiles[orderedImageTiles[i][j]];

      tileRow.push_back(orderedTile);
      tileRow.back().RemoveBorders();
    }

    finalTiles.push_back(tileRow);
  }

  Tile finalMap;

  for (int i = 0; i < finalTiles.size(); i++)
  {
    for (int k = 0; k < finalTiles[0][0].image.size(); k++)
    {
      string row;
      for (int j = 0; j < finalTiles.size(); j++)
      {
        const auto& tile = finalTiles[i][j];
        row += tile.image[k];
      }

      finalMap.image.push_back(row);
    }
  }

  vector<string> seaMonster{
    "                  # ",
    "#    ##    ##    ###",
    " #  #  #  #  #  #   "
  };

  vector<pair<int, int>> digitalMonster{
   { 0, 18 },
   { 1, 0 },
   { 1, 5 },
   { 1, 6 },
   { 1, 11 },
   { 1, 12 },
   { 1, 17 },
   { 1, 18 },
   { 1, 19 },
   { 2, 1 },
   { 2, 4 },
   { 2, 7 },
   { 2, 10 },
   { 2, 13 },
   { 2, 16 },
  };

  finalMap.Flip();

  int monsters = 0;
  for (int i = 0; i < (finalMap.image.size() - seaMonster.size()); i++)
  {
    for (int j = 0; j < (finalMap.image.size() - seaMonster[0].size()); j++)
    {
      int sum = 0;
      for (auto [di, dj] : digitalMonster)
      {
        if (finalMap.image[i + di][j + dj] == '#')
          sum++;
      }

      if (sum == digitalMonster.size())
        monsters++;
    }
  }

  // print
  int total = 0;
  for (int i = 0; i < finalMap.image.size(); i++)
  {
    out << finalMap.image[i];

    for (int j = 0; j < finalMap.image[i].size(); j++)
    {
      if (finalMap.image[i][j] == '#')
        total++;
    }

    out << endl;
  }

  cout << endl << total - 15 * digitalMonster.size() << endl;

  out << endl;

  FStreamWriter writter(out);
  writter.WriteMatrix(orderedImageTiles);

  auto result = std::accumulate(begin(corners), end(corners), 1LL, std::multiplies<long long>());
  cout << result;

  return 0;
}
