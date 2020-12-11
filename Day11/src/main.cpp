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

using namespace std;

#include "../../AOCLib/src/AOCLib.h"

bool CountSeat(const vector<string> & lines, AOC::Point neighbour, int& countL, int & countH)
{
  if (neighbour.x < 0 || neighbour.y < 0 || neighbour.x >= lines[0].size() || neighbour.y >= lines.size())
    return false;

  if (lines[neighbour.y][neighbour.x] == 'L')
  {
    countL++;
    return false;
  }

  if (lines[neighbour.y][neighbour.x] == '#')
  {
    countH++;
    return false;  
  }

  return true;
}

pair<int, int> CountAllNeighbours(const vector<string>& lines, AOC::Point current)
{
  int countL = 0;
  int countH = 0;

  // left
  auto left = current.GetLeft();
  while (CountSeat(lines, left, countL, countH))
    left = left.GetLeft();

  // righ
  auto right = current.GetRight();
  while (CountSeat(lines, right, countL, countH))
    right = right.GetRight();

  // up
  auto up = current.GetTop();
  while (CountSeat(lines, up, countL, countH))
    up = up.GetTop();

  // down
  auto down = current.GetBottom();
  while (CountSeat(lines, down, countL, countH))
    down = down.GetBottom();

  //-------------

  // up left
  auto upLeft = current.GetTop().GetLeft();
  while (CountSeat(lines, upLeft, countL, countH))
    upLeft = upLeft.GetTop().GetLeft();

  // up right
  auto upRight = current.GetTop().GetRight();
  while (CountSeat(lines, upRight, countL, countH))
    upRight = upRight.GetTop().GetRight();

  // down left
  auto downLeft = current.GetBottom().GetLeft();
  while (CountSeat(lines, downLeft, countL, countH))
    downLeft = downLeft.GetBottom().GetLeft();

  // down right
  auto downRight = current.GetBottom().GetRight();
  while (CountSeat(lines, downRight, countL, countH))
    downRight = downRight.GetBottom().GetRight();

  return make_pair(countL, countH);
}

int main()
{
  ifstream in("..\\..\\Day11\\src\\_Input.in");
  // ofstream out("..\\..\\Day11\\src\\_Output.out");

  FStreamReader reader(in);
  auto lines = reader.ReadLines();

  auto nextLines = lines;
  for(int simulation = 0; simulation <= 100; simulation++)
  {
    for (int y = 0; y < lines.size(); ++y)
    {
      for (int x = 0; x < lines[0].size(); ++x)
      {
        auto [countL, countH] = CountAllNeighbours(lines, AOC::Point{x, y});

        if (lines[y][x] == 'L' && countH == 0)
          nextLines[y][x] = '#';

        if (lines[y][x] == '#' && countH >= 5)
          nextLines[y][x] = 'L';
      }
    }

    lines = nextLines;
  }


  int count = accumulate(begin(lines), end(lines), 0, [](int acc, const string& line)->int {
    return acc + accumulate(begin(line), end(line), 0, [](int acc, const char c) {return acc + (c == '#'); });
  });

  cout << endl << count;
  return 0;
}
