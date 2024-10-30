#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cmath>

struct Point {
    int x, y;

    bool operator<(const Point& other) const {
        return y < other.y || (y == other.y && x > other.x);
    }
};

bool CrossProduct(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x) > 0;
}

std::vector<Point> BuildConvexHull(std::vector<Point>& points) {
    size_t size = points.size();
    if (size < 3) {
        return points;
    }
    std::vector<Point> hull(2 * size);
    size_t k = 0;
    for (size_t i = 0; i < size; ++i) {
        while (k > 1 && !CrossProduct(hull[k - 2], hull[k - 1], points[i])) {
            --k;
        }
        hull[k++] = points[i];
    }
    for (size_t i = size - 1, p = k + 1; i != 0; hull[k++] = points[i-- - 1]) {
        while (k >= p && !CrossProduct(hull[k - 2], hull[k - 1], points[i - 1])) {
            --k;
        }
    }
    hull.resize(k - 1);
    return hull;

}

int main() {
    int n;
    std::cin >> n;

    std::set<Point> pointsSet;
    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        pointsSet.insert({x, y});
    }

    std::vector<Point> points(pointsSet.size());
    size_t j = 0;
    for (auto it = pointsSet.begin(); it != pointsSet.end(); ++it) {
        points[j++] = *it;
    }

    std::vector<Point> hull = BuildConvexHull(points);
    std::cout << hull.size() << '\n';
    if (n & 1) {
        for (auto it = hull.rbegin(); it != hull.rend(); ++it) {
            std::cout << it->x << ' ' <<it->y << '\n';
        }
    } else {
        for (const Point &it : hull) {
            std::cout << it.x << ' ' <<it.y << '\n';
        }
    }


    return 0;
}