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
  ifstream in("..\\..\\Day01\\src\\Day01.in");
  // ofstream out("..\\..\\Day01\\src\\Day01.out");

  FStreamReader reader(in);
  vector<int> v = reader.ReadDataAs<int>();

  sort(begin(v), end(v));

  int s = 0;
  for(auto & x : v)
  {
    for (auto& y : v)
    {
      for (auto& z : v)
      {
        if (x + y + z == 2020)
          s = x * y * z;
      }
    }
  }

  cout << s;

  // out
  // FStreamWriter writer(out);
  // writer.WriteVector(v);

  return 0;
}
