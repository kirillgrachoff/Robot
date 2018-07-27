//
// Created by kirill on 6/24/18.
//

#ifndef ROBOTPROJECT_POINT_H
#define ROBOTPROJECT_POINT_H


class Point {
public:
    long long x;
    long long y;

    Point();
    Point(long long x, long long y);

    Point copy(long long deltaX, long long deltaY);
};


#endif //ROBOTPROJECT_POINT_H
