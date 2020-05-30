//
// Created by kirill on 6/24/18.
//

#ifndef ROBOTPROJECT_POINT_HPP
#define ROBOTPROJECT_POINT_HPP


class Point {
public:
    long long x;
    long long y;

    Point();
    Point(long long x, long long y);

    Point copyAndAdd(long long deltaX, long long deltaY);
};


#endif //ROBOTPROJECT_POINT_HPP
