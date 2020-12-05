/**
 * Advent of code 2020
 * @author : Nicolae Telechi
 */
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>
#include <set>
#include <unordered_map>
#include <optional>
#include <numeric>
#include <regex>

using namespace std;

#include "../../AOCLib/src/AOCLib.h"


int BinarySearch(const string str, int left, int right)
{
  if (str.size() == 1)
  {
    if (str[0] == 'F' || str[0] == 'L')
      return left;

    return right;
  }

  int mid = (left + right) / 2;

  if (str[0] == 'F' || str[0] == 'L')
  {
    return BinarySearch(str.substr(1), left, mid);
  }
  else
  {
    return BinarySearch(str.substr(1), mid + 1, right);
  }

}

int main()
{
  ifstream in("..\\..\\Day05\\src\\Day05.in");
  // ofstream out("..\\..\\Day05\\src\\Day05.out");

  FStreamReader reader(in);
  vector<string> v = reader.ReadLines();

  map<int, bool> seats;

  int maxPass = 0;
  for (const auto& line : v)
  {
    int row = BinarySearch(line.substr(0, 7), 0, 127);
    int column = BinarySearch(line.substr(7, 3), 0, 7);
    maxPass = std::max(row * 8 + column, maxPass); 

    seats[row * 8 + column] = true;
  }

  // for (const auto& seat : seats)
  // {
  //   cout << seat.first << " " << seat.second << endl;
  // }

  for (int i = 53; i <= 1000; i++)
  {
    if (seats.count(i) == 0)
    {
      cout << i << endl;
      break;
    }
  }

  cout << endl << maxPass;

  return 0;
}
