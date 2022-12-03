#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <string>
#include <thrust/sequence.h>
#include <thrust/transform.h>

struct point
{
  long id;
  double x;
  double y;
};

__host__ __device__ double calculateDistance(point a, point b)
{
  return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
};

__host__ __device__ double calculatePartialDistance(point *points, long size)
{
  double partialDistance = 0.0;
  for (long i = 1; i < size; i++)
  {
    partialDistance += calculateDistance(points[i - 1], points[i]);
  };
  partialDistance += calculateDistance(points[size - 1], points[0]);

  return partialDistance;
}

bool compare(const double &a, const double &b)
{
  return a < b;
};

struct calculate
{
  point *combinations;
  point *pointsCopyIteration;
  point transitPoint;
  double newPartialDistance;

  long cityAmount;
  calculate(point *combinations_, long cityAmount_) : combinations(combinations_), cityAmount(cityAmount_){};

  __host__ __device__ double operator()(const long &iterator)
  {
    double partialDistance = calculatePartialDistance(combinations + (cityAmount * iterator), cityAmount);

    for (long i = 0; i < cityAmount - 1; i++)
    {
      pointsCopyIteration = combinations + (cityAmount * iterator);

      transitPoint = combinations[cityAmount * iterator + i];
      pointsCopyIteration[i] = combinations[cityAmount * iterator + i + 1];
      pointsCopyIteration[i + 1] = transitPoint;

      newPartialDistance = calculatePartialDistance(pointsCopyIteration, cityAmount);

      if (newPartialDistance < partialDistance)
      {
        combinations[cityAmount * iterator + i] = pointsCopyIteration[i];
        combinations[cityAmount * iterator + i + 1] = pointsCopyIteration[i + 1];
        partialDistance = newPartialDistance;
      }
    }

    return partialDistance;
  }
};

int main()
{
  long cityAmount;

  std::cin >> cityAmount;
  point points[cityAmount];
  point combinations[10 * cityAmount * cityAmount];
  long iterators[10 * cityAmount];
  double distances[10 * cityAmount];

  thrust::sequence(iterators, iterators + 10 * cityAmount);

  for (long i = 0; i < (cityAmount); i++)
  {
    point newPoint;
    newPoint.id = i;
    std::cin >> newPoint.x;
    std::cin >> newPoint.y;
    points[i] = newPoint;
  };

  std::default_random_engine generator(10);

  for (long i = 0; i < (10 * cityAmount); i++)
  {
    shuffle(points, points + cityAmount, generator);
    for (long element = 0; element < cityAmount; element++)
    {
      combinations[(i * cityAmount) + element] = points[element];
    }
  }

  thrust::transform(iterators, iterators + 10 * cityAmount, distances, calculate(combinations, cityAmount));
  std::sort(distances, distances + 10 * cityAmount, compare);
  std::cout << distances[0] << "\n";
}
