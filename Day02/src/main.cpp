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

using namespace std;

#include "../../AOCLib/src/Algorithm.h"
#include "../../AOCLib/src/FStreamReader.h"
#include "../../AOCLib/src/FStreamWriter.h"
#include "../../AOCLib/src/Math.h"
#include "../../AOCLib/src/Time.h"


int main()
{
  ifstream in("..\\..\\Day02\\src\\Day02.in");
  // ofstream out("..\\..\\Day02\\src\\Day02.out");

  // FStreamReader reader(in);
  // vector<int> v = reader.ReadVector();

  // sort(begin(v), end(v));

  int min = 0;
  int max = 0;
  char _, c = 0;
  string str;

  int s = 0;
  while (!in.eof())
  {
    unordered_map<char, int> freq;

    in >> min >> _ >> max >> c >> _ >> str;

    for (auto x : str)
      freq[x]++;

    int nr = (str[min - 1] == c) + (str[max - 1] == c);
    if (nr == 1)
      s++;
  }

  cout << s;

  // out
  // FStreamWriter writer(out);
  // writer.WriteVector(v);

  return 0;
}
