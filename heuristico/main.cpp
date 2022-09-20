#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>
#include <algorithm>

using namespace std;

struct point
{
    int id;
    double x;
    double y;
};

struct distanceToPoint
{
    int pointId;
    double distance;
};

double calculateDistance(point a, point b)
{
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
};

bool compare(const distanceToPoint &a, const distanceToPoint &b)
{
    return a.distance < b.distance;
};

point getPointById(int id, vector<point> points)
{
    for (int i = 0; i < (points.size()); i++)
    {
        if (id == points[i].id)
        {
            return points[i];
        };
    };

    throw std::invalid_argument("An id is no longer in the list.");
};

void removePointById(int id, vector<point> &points)
{
    for (int i = 0; i < (points.size()); i++)
    {
        if (id == points[i].id)
        {
            points.erase(points.begin() + i);
        };
    };
};

int main()
{
    int cityAmount;
    cin >> cityAmount;
    double totalDistance = 0.0;

    vector<point> points;
    vector<int> outIds;

    for (int i = 0; i < (cityAmount); i++)
    {
        point newPoint;
        newPoint.id = i;
        cin >> newPoint.x;
        cin >> newPoint.y;
        points.push_back(newPoint);
    };

    point initialPoint = points[0];
    point actualPoint = points[0];

    while (points.size())
    {
        vector<distanceToPoint> distances;
        for (int i = 0; i < (points.size()); i++)
        {
            distanceToPoint newDistance;
            newDistance.pointId = points[i].id;
            newDistance.distance = calculateDistance(actualPoint, points[i]);
            distances.push_back(newDistance);
        };

        sort(distances.begin(), distances.end(), compare);
        actualPoint = getPointById(distances[0].pointId, points);
        totalDistance += distances[0].distance;
        outIds.push_back(actualPoint.id);
        removePointById(actualPoint.id, points);
    }
    totalDistance += calculateDistance(initialPoint, actualPoint);
    cout << totalDistance << " "
         << "0"
         << "\n";

    for (int i = 0; i < (outIds.size()); i++)
    {
        cout << outIds[i] << " ";
    };

    cout << endl;
}
