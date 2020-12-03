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
  ifstream in("..\\..\\Day03\\src\\Day03.in");
  // ofstream out("..\\..\\Day03\\src\\Day03.out");

  FStreamReader reader(in);
  vector<string> v = reader.ReadVectorOfWords();



  int s0 = 0;
  for (int i = 0, j = 0; i < v.size(); i++, j += 1)
  {

    if (v[i][j % v[0].size()] == '#')
      s0++;
  }

  int s1 = 0;
  for (int i = 0, j = 0; i < v.size(); i++, j += 3)
  {

    if (v[i][j % v[0].size()] == '#')
      s1++;
  }


  int s2 = 0;
  for (int i = 0, j = 0; i < v.size(); i++, j += 5)
  {

    if (v[i][j % v[0].size()] == '#')
      s2++;
  }

  int s3 = 0;
  for (int i = 0, j = 0; i < v.size(); i++, j += 7)
  {

    if (v[i][j % v[0].size()] == '#')
      s3++;
  }

  int s4 = 0;
  for (int i = 0, j = 0; i < v.size(); i+=2, j += 1)
  {

    if (v[i][j % v[0].size()] == '#')
      s4++;
  }

  // sort(begin(v), end(v));

  cout << s0 * s1 * s2 * s3 * s4;

  // out
  // FStreamWriter writer(out);
  // writer.WriteVector(v);

  return 0;
}
