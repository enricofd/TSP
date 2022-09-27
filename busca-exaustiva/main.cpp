#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

struct point
{
    int id;
    double x;
    double y;
};

double calculateDistance(point a, point b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
};

double calculatePartialDistance(vector<int> ids, vector<point> points)
{
    double partialDistance = 0.0;
    for (int i = 1; i < (points.size()); i++)
    {
        partialDistance += calculateDistance(points[ids[i - 1]], points[ids[i]]);
    };
    partialDistance += calculateDistance(points[ids[points.size() - 1]], points[ids[0]]);

    return partialDistance;
};

void printIds(vector<int> ids)
{
    for (int i = 0; i < (ids.size()); i++)
    {
        cout << ids[i] << " ";
    };
};

long int fact(long int n)
{
    return (n == 0) || (n == 1) ? 1 : n * fact(n - 1);
}

int main()
{
    int cityAmount;
    double partialDistance;
    double bestDistance;

    cin >> cityAmount;

    vector<point>
        points;
    vector<int>
        ids;
    vector<int>
        bestRoute;

    for (int i = 0; i < (cityAmount); i++)
    {
        point newPoint;
        newPoint.id = i;
        cin >> newPoint.x;
        cin >> newPoint.y;
        points.push_back(newPoint);
        ids.push_back(i);
    };

    bestDistance = calculatePartialDistance(ids, points);
    bestRoute = ids;

    long int combinations = fact(cityAmount) / cityAmount;
    long int iteratorLimit = 0;

    sort(ids.begin(), ids.end());

    do
    {
        partialDistance = calculatePartialDistance(ids, points);
        iteratorLimit++;

        if (partialDistance < bestDistance)
        {
            bestDistance = partialDistance;
            bestRoute = ids;
        };
    } while (next_permutation(ids.begin(), ids.end()) and iteratorLimit < combinations);

    cerr << "num_leaf " << combinations << "\n";
    cout << bestDistance << " 1 \n";
    printIds(bestRoute);
}
