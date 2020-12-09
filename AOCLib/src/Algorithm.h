#pragma once

/**
 * Advent of code 2020
 * @author : Nicolae Telechi
 */
namespace AOC
{
  struct Point;

  long long Fibonaci(long long n, long long modulo);
  vector<bool> Eratosthenes(size_t n);

  /**
   * @returns length, begin index, end index
   */
  tuple<int, int, int> SubsequenceOfLargestSum(const vector<int> & sequence);
  vector<long long> GetPartialSums(const vector<long long>& sequence);

  pair<vector<vector<int>>, set<int>> Lee(const vector<Point>& aCoordonates, vector<vector<int>>& aMap);

  /**
   * Huge numbers multiplication
   */
  long long MultiplyModulo(long long a, long long b, long long modulo);
  vector<vector<long long>> MultiplyMatrix(const vector<vector<long long>>& first,
    const vector<vector<long long>>& second, long long modulo);

  //----------------------------------------------------

  namespace detail
  { 
    template<size_t k>
    void GenerateCombinationsRecursive(vector<array<size_t, k>>& combinations,
      array<size_t, k>& temp,
      size_t n,
      size_t from,
      size_t depth)
    {
      if (depth == k) {
        combinations.push_back(temp);
        return;
      }

      for (size_t i = from; i < n; ++i) {
        temp[depth] = i;
        GenerateCombinationsRecursive(combinations, temp, n, i + 1, depth + 1);
      }
    }
  }

  template<size_t k = 1>
  vector<std::array<size_t, k>> GenerateIndexCombinations(size_t n)
  {
    vector<std::array<size_t, k>> combinations;

    array<size_t, k> temp;
    detail::GenerateCombinationsRecursive<k>(combinations, temp, n, 0, 0);

    return combinations;
  }
}
