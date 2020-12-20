/**
 * Advent of code 2020
 * @author : Nicolae Telechi
 */
#include "pch.h"
#include "FStreamWriter.h"


FStreamWriter::FStreamWriter(ofstream & aOut) 
  : mFileStream(aOut)
{
  assert(mFileStream.good());
}

void FStreamWriter::WriteVector(const vector<int> & aVector)
{
  for (const auto & element : aVector)
  {
    mFileStream << element << endl;
  }
}

void FStreamWriter::WriteMatrix(const vector<vector<int>> & aMatrix)
{
  for (const auto & row : aMatrix)
  {
    for (const auto & element : row)
    {
        mFileStream << element << " ";
    }

    mFileStream << endl;
  }
}

void FStreamWriter::WriteMatrixAsGrid(const vector<vector<int>>& aMatrix)
{
  for (const auto& row : aMatrix)
  {
    for (const auto& element : row)
    {
      mFileStream << (element ? "#" : ".");
    }

    mFileStream << endl;
  }
}
