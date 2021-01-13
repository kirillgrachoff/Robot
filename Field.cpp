#ifndef ROBOTPROJECT_FIELD_CPP
#define ROBOTPROJECT_FIELD_CPP

#include <iostream>
#include "Field.hpp"
#include "Constants.hpp"
#include <fstream>
#include <deque>
#include <cmath>
#include <random>
#include <algorithm>
#include <set>

using namespace std;

char Field::value(const Point& p) const {
    return values[p.x][p.y];
}

char& Field::value(const Point& p) {
    return values[p.x][p.y];
}

long long Field::dist(const Point& p) const {
    return distant[p.x][p.y];
}

long long& Field::dist(const Point& p) {
    return distant[p.x][p.y];
}

// fill field from file OR fill random
Field::Field(string filename, std::ostream& logfile): lout(logfile) {
	static std::random_device rand;
    if (filename == "") {
        RobotLevel = 6;
		cntX = rand() % 20 + 200;
		cntY = rand() % 10 + 100;
        values.resize(cntX, vector<char>(cntY));
        distant.resize(cntX, vector<long long>(cntY, -1));
        for (auto &vc: values) {
            for (auto &val: vc) {
                long long k = rand() % 20;
                if (k < std::min(10LL, RobotLevel)) {
                    val = WALL;
                } else {
                    val = ROAD;
                }
            }
        }
        int robotCnt = rand() % 3 + 1;
        robots.resize(robotCnt);
        for (auto& it : robots) {
            it = Point{rand() % std::min(cntX, 20LL), rand() % std::min(cntY, 20LL)};
            value(it) = ROBOT;
        }
        std::sort(robots.begin(), robots.end());
        robots.erase(std::unique(robots.begin(), robots.end()), robots.end());
        int exitCnt = rand() % 3 + 1;
        exits.resize(exitCnt);
        for (auto& it : exits) {
            it = Point{cntX - 1 - (rand() % std::min(cntX, 20LL)), cntY - 1 - (rand() % std::min(cntY, 20LL))};
            value(it) = EXIT;
        }
        std::sort(exits.begin(), exits.end());
        exits.erase(std::unique(exits.begin(), exits.end()), exits.end());
    } else {
        ifstream in(filename);
        in >> cntX >> cntY;
        distant.resize(cntX, vector<long long>(cntY, -1));
        values.resize(cntX, vector<char>(cntY, NULLELEMENT));
        for (long long y = 0; y < cntY; y++) {
            for (long long x = 0; x < cntX; x++) {
                char element;
                in >> element;
                if (element == EXIT) {
                    exits.emplace_back(Point(x, y));
                }
                if (element == ROBOT) {
                    robots.emplace_back(Point(x, y));
                }
                values[x][y] = element;
            }
        }
    }
}

Field::~Field() {}

std::vector<char>& Field::operator[] (size_t i) {
    return values[i];
}

void Field::countPathes() {
    deque<Point> q;
    set<char> valid{ROAD, ROBOT, EXIT};
    for (auto& it : exits) {
        q.push_back(it);
        dist(it) = 0;
    }
    while (!q.empty()) {
        for (auto& next : near(q.front(), valid)) {
            if (dist(next) >= 0) continue;
            dist(next) = dist(q.front()) + 1;
            q.push_back(next);
        }
        q.pop_front();
    }
}

vector<Point> Field::near(Point s, set<char>& valid) {
    vector<Point> res;
    if (s.y + 1 < cntY  && valid.count(values[s.x][s.y + 1])) res.push_back(s.copyAndAdd(0, 1));
    if (s.x + 1 < cntX  && valid.count(values[s.x + 1][s.y])) res.push_back(s.copyAndAdd(1, 0));
    if (s.x - 1 >= 0    && valid.count(values[s.x - 1][s.y])) res.push_back(s.copyAndAdd(-1, 0));
    if (s.y - 1 >= 0    && valid.count(values[s.x][s.y - 1])) res.push_back(s.copyAndAdd(0, -1));
    return res;
}

bool Field::existPath() {
    if (existPathCounted) return existPathAnswer;
    existPathCounted = true;
    countPathes();
    for (auto& it : robots) {
        existPathAnswer |= dist(it) >= 0;
    }
    return existPathAnswer;
}

void Field::step() {
    static std::random_device rand;
    std::sort(robots.begin(), robots.end(), [=](const Point& a, const Point& b) {
        return dist(a) < dist(b);
    });
    set<char> valid{ROAD, EXIT};
    for (auto& it : robots) {
        if (dist(it) <= 0) continue;
        auto next = near(it, valid);
        std::shuffle(next.begin(), next.end(), rand);
        for (auto& nxt : next) {
            if (dist(nxt) >= dist(it)) continue;
            if (value(nxt) == EXIT) {
                value(it) = ROAD;
                it = nxt;
                break;
            }
            std::swap(value(it), value(nxt));
            it = nxt;
            break;
        }
    }
}

#endif // ROBOTPROJECT_FIELD_CPP
