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

int main()
{
  ifstream in("..\\..\\Day25\\src\\_Input.in");
  ofstream out("..\\..\\Day25\\src\\_Output.out");

  FStreamReader reader(in);
  auto lines = reader.ReadLines();

  int cardPublicKey = 8184785;
  int doorPublicKey = 5293040;
  int mod = 20201227;

  auto transformSubject = [=](long long subject, long long loopSize)
  {
    return AOC::PowModulo(subject, loopSize, mod);
  };

  int cardLoopSize = 0;
  while (transformSubject(7, ++cardLoopSize) != cardPublicKey);
  
  int doorLoopSize = 0;
  while (transformSubject(7, ++doorLoopSize) != doorPublicKey);

  long long encriptionKey1 = transformSubject(cardPublicKey, doorLoopSize);
  long long encriptionKey2 = transformSubject(doorPublicKey, cardLoopSize);

  if (encriptionKey1 == encriptionKey2)
    cout << encriptionKey1;

  return 0;
}
