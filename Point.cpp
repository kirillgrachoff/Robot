//
// Created by kirill on 6/25/18.
//

#include "Point.hpp"

Point::Point(long long x, long long y) {
    this->x = x;
    this->y = y;
}

Point::Point() {
    x = -1;
    y = -1;
}

Point Point::copyAndAdd(long long deltaX, long long deltaY) {
    return Point{this->x + deltaX, this->y + deltaY};
}
