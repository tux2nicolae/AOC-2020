#pragma once

/**
 * Advent of code 2019
 * @author : Nicolae Telechi
 */
namespace AOC
{
  struct Point;

  long long Fibonaci(long long n, long long modulo);
  vector<bool> Eratosthenes(size_t n);

  pair<vector<vector<int>>, set<int>> Lee(const vector<Point> & aCoordonates, vector<vector<int>> & aMap);

  tuple<int, int, int> SubsequenceOfLargestSum(const vector<int> & sequence);

  vector<string> Explode(const string & str, char separator);
  int RegexMatchInt(const string& str, const string& regexStr = "(.*)");

  long long MultiplyModulo(long long a, long long b, long long modulo);
  vector<vector<long long>> MultiplyMatrix(const vector<vector<long long>>& first,
    const vector<vector<long long>>& second, long long modulo);

  //--------------------------------------------------------------------------
  // implementation details

  namespace detail
  {
    vector<int> GetPartialSums(const vector<int> & sequence);

    vector<vector<long long>> FibonaciMatrix(long long n, long long modulo);
  }
}
