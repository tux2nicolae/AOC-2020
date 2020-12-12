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

struct Ship
{
  // part 1
  //--------------------------------------------------

  void SetPosition(AOC::Point position)
  {
    this->position = position;
  }

  AOC::Point GetPosition()
  {
    return position;
  }

  void TurnLeft()
  {
    switch (direction)
    {
    case '^':
      direction = '<';
      break;
    case '<':
      direction = 'v';
      break;
    case 'v':
      direction = '>';
      break;
    case '>':
      direction = '^';
      break;
    default:
      break;
    }
  }

  void TurnRight()
  {
    switch (direction)
    {
    case '^':
      direction = '>';
      break;
    case '>':
      direction = 'v';
      break;
    case 'v':
      direction = '<';
      break;
    case '<':
      direction = '^';
      break;
    default:
      break;
    }
  }

  void MoveForward(int step)
  {
    if (direction == '^')
    {
      position.y -= step;
    }
    else if (direction == '>')
    {
      position.x += step;
    }
    else if (direction == 'v')
    {
      position.y += step;
    }
    else if (direction == '<')
    {
      position.x -= step;
    }
  }

  void MoveNorth(int step)
  {
    position.y -= step;
  }

  void MoveSouth(int step)
  {
    position.y += step;
  }

  void MoveEast(int step)
  {
    position.x += step;
  }

  void MoveWest(int step)
  {
    position.x -= step;
  }

  // part 2
  //--------------------------------------------------

  void TurnWaypointRight()
  {
    waypoint.RotateRight();
  }

  void TurnWaypointLeft()
  {
    waypoint.RotateLeft();
  }

  void MoveForwardToWaypoint(int step)
  {
    position.x += step * waypoint.x;
    position.y += step * waypoint.y;
  }

  void MoveWaypointNorth(int step)
  {
    waypoint.y -= step;
  }

  void MoveWaypointSouth(int step)
  {
    waypoint.y += step;
  }

  void MoveWaypointEast(int step)
  {
    waypoint.x += step;
  }

  void MoveWaypointWest(int step)
  {
    waypoint.x -= step;
  }

  char direction{ '>' };

  AOC::Point position{ 0, 0 };
  AOC::Point waypoint{ 10, -1 };
};

int main()
{
  ifstream in("..\\..\\Day12\\src\\_Input.in");
  // ofstream out("..\\..\\Day12\\src\\_Output.out");

  FStreamReader reader(in);
  auto lines = reader.ReadLines();

  Ship part1;
  Ship part2;

  // part 1
  for (auto& line : lines)
  {
    char direction = line[0];
    int value = atoi(line.substr(1).c_str());

    switch (direction)
    {
    case 'N': part1.MoveNorth(value); break;
    case 'S': part1.MoveSouth(value); break;
    case 'E': part1.MoveEast(value); break;
    case 'W': part1.MoveWest(value); break;
    case 'F': part1.MoveForward(value); break;
    case 'L':
      while (value > 0) {
        part1.TurnLeft();
        value -= 90;
      }
      break;
    case 'R':
      while (value) {
        part1.TurnRight();
        value -= 90;
      }
      break;
    }
  };

  // part 2
  for (auto& line : lines)
  {
    char direction = line[0];
    int value = atoi(line.substr(1).c_str());

    switch (direction)
    {
    case 'N': part2.MoveWaypointNorth(value); break;
    case 'S': part2.MoveWaypointSouth(value); break;
    case 'E': part2.MoveWaypointEast(value); break;
    case 'W': part2.MoveWaypointWest(value); break;
    case 'F': part2.MoveForwardToWaypoint(value); break;
    case 'L': 
      while (value > 0) {
        part2.TurnWaypointLeft();
        value -= 90;
      }
      break;
    case 'R': 
      while (value) {
        part2.TurnWaypointRight();
        value -= 90;
      }
      break;
    }
  };

  cout << AOC::ManhattenDistance(AOC::Point{0,0}, part1.GetPosition()) << endl;
  cout << AOC::ManhattenDistance(AOC::Point{0,0}, part2.GetPosition()) << endl;

  return 0;
}
