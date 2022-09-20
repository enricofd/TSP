#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdlib>

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

double calculatePartialDistance(vector<point> points)
{
    double partialDistance = 0.0;
    for (int i = 1; i < (points.size()); i++)
    {
        partialDistance += calculateDistance(points[i - 1], points[i]);
    };
    partialDistance += calculateDistance(points[points.size() - 1], points[0]);

    return partialDistance;
};

void printList(vector<point> points, int o)
{
    for (int i = 0; i < (points.size()); i++)
    {
        if (o == 0)
        {
            cerr << points[i].id << " ";
        }
        else
        {
            cout << points[i].id << " ";
        }
    };
};

int main()
{
    int cityAmount;
    cin >> cityAmount;
    double totalDistance = 0.0;

    double distance;
    double partialDistance;
    double newPartialDistance;
    point transitPoint;

    vector<point>
        points;
    vector<point>
        pointsCopy;
    vector<point>
        pointsCopyIteration;
    vector<point>
        pointsOut;

    for (int i = 0; i < (cityAmount); i++)
    {
        point newPoint;
        newPoint.id = i;
        cin >> newPoint.x;
        cin >> newPoint.y;
        points.push_back(newPoint);
    };

    default_random_engine generator(10);

    for (int i = 0; i < (10 * cityAmount); i++)
    {
        pointsCopy = points;
        shuffle(pointsCopy.begin(), pointsCopy.end(), generator);

        partialDistance = calculatePartialDistance(pointsCopy);

        for (int i = 0; i < pointsCopy.size() - 1; i++)
        {
            pointsCopyIteration = pointsCopy;

            transitPoint = pointsCopyIteration[i];
            pointsCopyIteration[i] = pointsCopyIteration[i + 1];
            pointsCopyIteration[i + 1] = transitPoint;

            newPartialDistance = calculatePartialDistance(pointsCopyIteration);

            if (newPartialDistance < partialDistance)
            {
                pointsCopy = pointsCopyIteration;
                partialDistance = newPartialDistance;
                i=0;
                continue;
            }
            
        }

        cerr << "local: " << partialDistance << " ";
        printList(pointsCopy, 0);
        cerr << "\n";

        if (i == 0)
        {
            totalDistance = partialDistance;
            pointsOut = pointsCopy;
        }

        if (partialDistance < totalDistance)
        {
            totalDistance = partialDistance;
            pointsOut = pointsCopy;
        }
    };

    cout << totalDistance << " " << 0 << "\n";
    printList(pointsOut, 1);
}
