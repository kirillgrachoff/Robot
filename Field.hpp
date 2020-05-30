//
// Created by kirill on 6/25/18.
//

#ifndef ROBOTPROJECT_FIELD_HPP
#define ROBOTPROJECT_FIELD_HPP

#include <string>
#include <vector>
#include "Point.hpp"

class Field {
public:
    long long cntX;
    long long cntY;

    long long RobotLevel = 7;
    long long RobotX;
    long long RobotY;
    long long ExitX;
    long long ExitY;
    bool hasPath = true;
    std::vector<Point> RobotPath;//shows next Points of path to exit, include exit

    Field();
    Field(std::string filename);
    ~Field();

    std::vector<char> & operator[] (const long long i);

    void path(Point start, Point end);

protected:
    std::vector<std::vector<char> > values;
    std::vector<std::vector<Point> > parents;

    std::vector<Point> near(Point s);
    void bfs(Point start);
    void find_path_to(Point start, Point end);
};


#endif //ROBOTPROJECT_FIELD_HPP
