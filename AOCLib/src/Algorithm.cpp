/**
 * Advent of code 2019
 * @author : Nicolae Telechi
 */
#include "pch.h"
#include "Algorithm.h"
#include "Math.h"

long long AOC::Fibonaci(long long n, long long modulo)
{
  if (n == 0)
    return 0;

  auto fibonaciMatrix = detail::FibonaciMatrix(n - 1, modulo);
  return fibonaciMatrix[1][1];
}

std::vector<bool> AOC::Eratosthenes(size_t n)
{
  vector<bool> sieve;
  sieve.resize(n + 1); // + 1 for n

  for (int i = 2; i <= sqrt(n); i++)
  {
    while (sieve[i]) i++;

    for (int j = i * i; j <= n; j += i)
      sieve[j] = true;
  }

  return sieve;
}

pair<vector<vector<int>>, set<int>> AOC::Lee(const vector<Point> & aCoordonates, vector<vector<int>> & aMap)
{
  set<int> infinitePoints;

  vector<vector<int>> distances;
  distances.resize(aMap.size());
  for (auto & line : distances)
    line.resize(aMap[0].size());
  
  queue<Point> unvisited;
  for (const auto & startingPoint : aCoordonates)
    unvisited.push(startingPoint);

  auto isInBoundary = [&](const Point & to)-> bool
  {
    return !(to.x < 0 || to.y < 0 || to.x >= aMap.size() || to.y >= aMap[0].size());
  };

  // run
  while (!unvisited.empty())
  {
    auto from = unvisited.front();
    unvisited.pop();

    if (aMap[from.x][from.y] == -1)
      continue;

    static const int directionX[4] = { -1,  0, 1, 0 };
    static const int directionY[4] = { 0,  1, 0, -1 };

    for (int i = 0; i < 4; ++i)
    {
      Point to;
      to.x = from.x + directionX[i];
      to.y = from.y + directionY[i];

      if (!isInBoundary(to))
      {
        infinitePoints.insert(aMap[from.x][from.y]);
        continue;
      }

      if (aMap[to.x][to.y])
      {
        if(distances[to.x][to.y] == distances[from.x][from.y] + 1 && aMap[from.x][from.y] != aMap[to.x][to.y])
          aMap[to.x][to.y] = -1;

        continue;
      }

      aMap[to.x][to.y] = aMap[from.x][from.y];
      distances[to.x][to.y] = distances[from.x][from.y] + 1;

      unvisited.push(to);
    }
  }

  return { distances, infinitePoints };
}

tuple<int, int, int> AOC::SubsequenceOfLargestSum(const vector<int> & sequence)
{
  assert(sequence.size() > 1);

  // reserve +1 for a dummy element 0 witch will make our live easier, this will make
  // begin and end to point on the correct positions
  vector<int> sums;
  sums.reserve(sequence.size() + 1);
  sums.push_back(0);

  std::partial_sum(sequence.begin(), sequence.end(),
    back_inserter(sums));

  int smax = std::numeric_limits<int>::min();
  int smaxbegin = 0, smaxend = 0;

  for (int beg = 0, end = 1; end < sums.size(); ++end)
  {
    if (sums[end] - sums[beg] > smax)
    {
      smax = sums[end] - sums[beg];
      smaxbegin = beg;
      smaxend = end;
    }

    // longest or shortest <=
    if (sums[end] < sums[beg])
      beg = end;
  }

  return make_tuple(smax, smaxbegin, smaxend);
}

std::vector<std::string> AOC::Explode(const std::string & str, char separator)
{
  std::vector<std::string> result;

  std::istringstream stream(str);
  for (std::string token; std::getline(stream, token, separator); )
  {
    result.push_back(std::move(token));
  }

  return result;
}

int AOC::RegexMatchInt(const string& str, const string& regexStr)
{
  smatch match;
  regex_match(str, match, regex(regexStr));
  assert(match.size() == 1);

  // 0
  return stoi(match[0]);
}

long long AOC::MultiplyModulo(long long a, long long b, long long modulo)
{
	long long res = 0;

	a %= modulo;

	while (b)
	{
		if (b % 2 == 1)
			res = (res + a) % modulo;

		a = (2 * a) % modulo;
		b = b / 2;
	}

	return res;
}

vector<vector<long long>> AOC::MultiplyMatrix(const vector<vector<long long>> & first, const vector<vector<long long>> & second, long long modulo)
{
  assert(first.size() != 0);
  assert(first.size() == second.size());
  assert(first[0].size() == second[0].size());

  for (int i = 0; i < first.size(); ++i)
  {
    assert(first[i].size() == first[0].size());
    assert(second[i].size() == first[0].size());
  }

  //------------------------------------------------------------------------

  size_t matrixSize = first.size();
  vector<vector<long long>> temp;

  temp.resize(matrixSize);
  for (auto & row : temp)
    row.resize(matrixSize);

  for (int i = 0; i < matrixSize; i++)
  {
    for (int j = 0; j < matrixSize; j++)
    {
      for (int k = 0; k < matrixSize; k++)
      {
        temp[i][j] = (MultiplyModulo(first[i][k], second[k][j], modulo) + temp[i][j]) % modulo;
      }
    }
  }

  return temp;
}

namespace AOC::detail
{
  vector<int> GetPartialSums(const vector<int>& sequence)
  {
    vector<int> sums;
    sums.reserve(sequence.size());

    std::partial_sum(sequence.begin(), sequence.end(),
      back_inserter(sums));

    return sums;
  }

  vector<vector<long long>> FibonaciMatrix(long long n, long long modulo)
  {
    static const vector<vector<long long>> kFibonaci{ {0, 1}, {1, 1} };

    if (n == 0)
    {
      return { {1, 0}, {0, 1} };
    }
    else if (n == 1)
    {
      return kFibonaci;
    }

    auto result = FibonaciMatrix(n / 2, modulo);
    if (n % 2 == 0)
    {
      return MultiplyMatrix(result, result, modulo);
    }
    else
    {
      return MultiplyMatrix(MultiplyMatrix(result, result, modulo), kFibonaci, modulo);
    }
  }
}
