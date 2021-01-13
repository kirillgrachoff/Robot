#ifndef ROBOTPROJECT_FIELD_HPP
#define ROBOTPROJECT_FIELD_HPP

#include <string>
#include <vector>
#include <set>
#include "Point.hpp"

class Field {
	std::ostream &lout;
	bool existPathCounted = false;
	bool existPathAnswer = false;
public:
    long long cntX;
    long long cntY;

    long long RobotLevel = 7;
    std::vector<Point> robots;
    std::vector<Point> exits;

    bool existPath();

    Field(std::ostream& logstream);
    Field(std::string filename, std::ostream& logstream);
    ~Field();

    std::vector<char>& operator[] (size_t i);

    char& value(const Point& p);
    char value(const Point& p) const;

    long long& dist(const Point& p);
    long long dist(const Point& p) const;

    void step();

protected:
    std::vector<std::vector<char>> values;
    std::vector<std::vector<long long>> distant;

    std::vector<Point> near(Point s, std::set<char>& valid);
    void countPathes();
};


#endif //ROBOTPROJECT_FIELD_HPP
