//
// Created by kirill on 6/25/18.
//

#include <iostream>
#include "Field.hpp"
#include "Constants.hpp"
#include <fstream>
#include <deque>
#include <cmath>
#include <random>

using namespace std;

Field::Field() {
    values.resize(cntX, vector<char>(cntY));
    parents.resize(cntX, vector<Point>(cntY));
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
    RobotX = rand() % cntX;
    RobotY = rand() % cntY;
    ExitX = rand() % cntY;
    ExitY = rand() % cntY;
    values[RobotX][RobotY] = ROBOT;
    values[ExitX][ExitY] = EXIT;
}

//TODO fill field from file and fill random
Field::Field(string filename) {
	std::random_device rand;
    if (filename == "") {
        ifstream in("defaultField.robotField");
        in >> cntX >> cntY;
        values.resize(cntX, vector<char>(cntY));
        parents.resize(cntX, vector<Point>(cntY));
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
        RobotX = rand() % std::min(cntX, 20LL);
        RobotY = rand() % std::min(cntY, 20LL);
        ExitX = cntX - 1 - (rand() % std::min(cntX, 20LL));
        ExitY = cntY - 1 - (rand() % std::min(cntY, 20LL));
        values[RobotX][RobotY] = ROBOT;
        values[ExitX][ExitY] = EXIT;
    } else {
        ifstream in(filename);
        in >> cntX >> cntY;
        parents.resize(cntX, vector<Point>(cntY));
        values.resize(cntX, vector<char>(cntY, NULLELEMENT));
        for (long long y = 0; y < cntY; y++) {
            for (long long x = 0; x < cntX; x++) {
                char element;
                in >> element;
                if (element == EXIT) {
                    ExitX = x;
                    ExitY = y;
                }
                if (element == ROBOT) {
                    RobotX = x;
                    RobotY = y;
                }
                values[x][y] = element;
            }
        }
    }
}

Field::~Field() {}

std::vector<char>& Field::operator[] (long long i) {
    return values[i];
}

void Field::path(Point start, Point end) {
    cout << "Robot: (" << RobotX << ", " << RobotY << ")\nExit: (" << ExitX << ", " << ExitY << ")" << endl;
    this->bfs(start);
    cout << "Exit bfs()" << endl;
    RobotPath.reserve(1000);
    find_path_to(start, end);
    cout << "Exit find_path_to()" << endl;
    if (RobotPath.size() == 0) hasPath = false;
}

void Field::bfs(Point start) {
    deque<Point> q;
    q.push_back(start);
    while (!q.empty()) {
        for (auto &point: near(q.front())) {
            if (parents[point.x][point.y].x != -1) continue;
            parents[point.x][point.y] = q.front();
            q.push_back(point);
            if (point.x == ExitX && point.y == ExitY) cout << "Exit Found" << endl;
        }
        q.pop_front();
    }
    parents[RobotX][RobotY] = Point(-1, -1);
}

void Field::find_path_to(Point start, Point end) {
    if (parents[end.x][end.y].x == -1 && parents[end.x][end.y].y == -1) {
        if (end.x != start.x) hasPath = false;
        return;
    } //There must be ==, but... I wrote !=, so check it
    cout << "In find_path_to({Point}(" << end.x << ", " << end.y << "))" << endl;
    find_path_to(start, parents[end.x][end.y]);
    this->RobotPath.push_back(end);
}

vector<Point> Field::near(Point s) {
    vector<Point> res;
    if (s.y + 1 < cntY  && values[s.x][s.y + 1] != WALL)    res.push_back(s.copyAndAdd(0, 1));
    if (s.x + 1 < cntX  && values[s.x + 1][s.y] != WALL)    res.push_back(s.copyAndAdd(1, 0));
    if (s.x - 1 >= 0    && values[s.x - 1][s.y] != WALL)    res.push_back(s.copyAndAdd(-1, 0));
    if (s.y - 1 >= 0    && values[s.x][s.y - 1] != WALL)    res.push_back(s.copyAndAdd(0, -1));
    //if (s.x + 1 < cntX && s.y + 1 < cntY && values[s.x + 1][s.y + 1] != WALL) res.push_back(s.copyAndAdd(1, 1));
    return res;
}
