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

struct Food
{
  set<string> alergens;
  set<string> ingredients;
};

int main()
{
  ifstream in("..\\..\\Day21\\src\\_Input.in");
  ofstream out("..\\..\\Day21\\src\\_Output.out");

  FStreamReader reader(in);
  auto lines = reader.ReadLines();


  vector<Food> foods;
  for (auto& line : lines)
  {
    auto foodInput = AOC::ExtractMatches(line, "(.*) \\(contains (.*)\\)");
    assert(foodInput.size() == 3);

    Food food;
    auto ingredientsInputVector = AOC::Explode(foodInput[1], ' ');
    food.ingredients = set<string>(begin(ingredientsInputVector), end(ingredientsInputVector));

    auto alergensInput = foodInput[2];

    alergensInput.erase(std::remove_if(alergensInput.begin(), alergensInput.end(),
      [](unsigned char x)
      {
        return std::isspace(x);
      }), end(alergensInput));

    auto alergensInputVector = AOC::Explode(alergensInput, ',');
    food.alergens = set<string>(begin(alergensInputVector), end(alergensInputVector));

    foods.push_back(food);
  }

  unordered_map<string, set<string>> alergens;

  for (auto& food : foods)
  {
    for (auto& alergen : food.alergens)
    {
      auto & currentAlergenIngredients = alergens[alergen];
      if (currentAlergenIngredients.empty())
      {
        currentAlergenIngredients = food.ingredients;
      }
      else
      {
        set<string> intersect;

        std::set_intersection(currentAlergenIngredients.begin(), currentAlergenIngredients.end(),
          food.ingredients.begin(), food.ingredients.end(),
          std::inserter(intersect, intersect.begin()));

        currentAlergenIngredients = intersect;
      }
    }
  }

  set<string> alergicIngredients;
  for (auto& [alergen, ingredients] : alergens)
  {
    for (auto& ingredient : ingredients)
      alergicIngredients.insert(ingredient);
  }

  int sum = 0;
  for (auto& food : foods)
  {
    int notAlergicIngredients = 
      count_if(begin(food.ingredients), end(food.ingredients), [&](const string& ingredient)
      {
        return alergicIngredients.find(ingredient) == end(alergicIngredients);
      });

    sum += notAlergicIngredients;
  }

  cout << "part 1:" << endl;
  cout << sum << endl << endl;

  // nuts: fvk rhvbn
  // wheat : fvk rhvbn zrb
  // sesame : lbmt zrb
  // fish : kjf zrb
  // eggs : fvk jgtb mmcpg rhvbn
  // shellfish : fvk jgtb
  // dairy : rhvbn
  // soy : fvk hcbdb mmcpg
  //
  // rhvbn,mmcpg,kjf,fvk,lbmt,jgtb,hcbdb,zrb

  cout << "part 2:" << endl;
  for (auto& [alergen, ingredients] : alergens)
  {
    string ingredientsstr;
    for (auto& ingredient : ingredients)
      ingredientsstr += ingredient + " ";

    cout << alergen << " -> " << ingredientsstr << endl;
  }

  return 0;
}
