//
// Created by kirill on 6/25/18.
//

#include "Point.h"

Point::Point(long long x, long long y) {
    this->x = x;
    this->y = y;
}

Point::Point() {
    x = -1;
    y = -1;
}

Point Point::copy(long long deltaX, long long deltaY) {
    return Point{this->x + deltaX, this->y + deltaY};
}
