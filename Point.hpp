#ifndef ROBOTPROJECT_POINT_HPP
#define ROBOTPROJECT_POINT_HPP

class Point {
public:
    long long x;
    long long y;

    Point();
    Point(long long x, long long y);

    Point copyAndAdd(long long deltaX, long long deltaY);

    bool operator<(const Point& that) const {
        if (x == that.x) return y < that.y;
        return x < that.x;
    }

    bool operator==(const Point& that) const {
        return x == that.x && y == that.y;
    }
};

#endif // ROBOTPROJECT_POINT_HPP
