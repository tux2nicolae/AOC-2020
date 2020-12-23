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


list<int>::iterator circularNext(list<int> & currentList, list<int>::iterator it)
{
  it++;
  if (it == currentList.end())
    it = begin(currentList);

  return it;
}


int main()
{
  ifstream in("..\\..\\Day23\\src\\_Input.in");
  ofstream out("..\\..\\Day23\\src\\_Output.out");

  FStreamReader reader(in);
  auto line = reader.ReadLineAsDigits();

  list<int> circle;
  vector<list<int>::iterator> previous(1000010, circle.end());

  for (auto& digit : line)
  {
    circle.push_back(digit);
    previous[digit + 1] = prev(circle.end());
  }

  for (int digit = 10; digit <= 1000000; digit++)
  {
    circle.push_back(digit);
    previous[digit + 1] = prev(circle.end());
  }

  // select destination cup
  int minNumber = 1;
  int maxNumber = circle.size();

  auto currentCupIt = circle.begin();
  auto destinationCupIt = circle.end();
  auto previousDestinationCupIt = circle.end();

  for (int iterations = 0; iterations < 10000000; iterations++)
  {
    vector<int> pickedUp;

    // remove next 3
    auto removeIt = circularNext(circle, currentCupIt);
    for (int i = 0; i < 3; i++)
    {
      auto nextRemove = circularNext(circle, removeIt);
      
      pickedUp.push_back(*removeIt);
      circle.erase(removeIt);

      removeIt = nextRemove;
    }

    int destinationCup = *currentCupIt;
    do {
      destinationCup--;
      if (destinationCup < minNumber)
        destinationCup = maxNumber;
    } while (find(begin(pickedUp), end(pickedUp), destinationCup) != end(pickedUp));

    destinationCupIt = previous[destinationCup + 1];
    
    // insert numbers after destination cup
    for (int i = pickedUp.size() - 1; i >= 0; i--)
    {
      auto insertNumber = pickedUp[i];
      auto insertedIt = circle.insert(circularNext(circle, destinationCupIt), insertNumber);
      previous[insertNumber + 1] = insertedIt;
    }

    // move current list
    currentCupIt = circularNext(circle, currentCupIt);
  }


  auto oneCup = find(begin(circle), end(circle), 1);
  // for (auto it = circularNext(circle, oneCup); it != oneCup; it = circularNext(circle, it))
  // {
  //   cout << *it << " ";
  // }

  cout << endl;
  cout << *circularNext(circle, oneCup) << endl;
  cout << *circularNext(circle, circularNext(circle, oneCup)) << endl;

  cout << endl;
  cout << long long(*circularNext(circle, oneCup)) * *circularNext(circle, circularNext(circle, oneCup)) << endl;


  return 0;
}
