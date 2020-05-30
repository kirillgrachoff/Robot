#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <fstream>
#include "Constants.hpp"
#include "Window.hpp"
#include "Point.hpp"
#include "Field.hpp"

using namespace std;

int main() {

    //Field field("field.robotField");
    cout << "File with field: ";
    string filename;
    getline(cin, filename);
    Field field(filename);
    field.path(Point(field.RobotX, field.RobotY), Point(field.ExitX, field.ExitY));
    if (field.hasPath) cout << "Path Found" << endl;
    else {
    	cout << "No Path Found" << endl;
    	return 0;
    }

    Window window(field);


    long long stepIndex = 0;//shows next step of robot

    bool done = false;
    while (true) {

        //SDL_Event ev;
        while (SDL_PollEvent(&window.ev)) {
            switch (window.ev.type) {
                case SDL_QUIT:
                    done = true;
                    break;
                default:
                    
                    break;
            }
        }

        //Draw block
        window.drawAll(field);
        if (field.hasPath) lout() << "size: " << field.RobotPath.size() << " index: " << stepIndex << endl;
        for (int j = 0; j < 1e7; j++) {
            for (int k = 0; k < 5; k++);
        }

        if (done) break;

        //Counting block
        if (field.hasPath) {
            Point nextStep = field.RobotPath[stepIndex];
            lout() << "Current: (" << field.RobotX << ", " << field.RobotY << ")" << endl;
            lout() << "Next   : (" << nextStep.x << ", " << nextStep.y << ")" << endl;
            field[field.RobotX][field.RobotY] = ROAD;
            field[nextStep.x][nextStep.y] = ROBOT;
            //swap(field[field.RobotX][field.RobotY], field[nextStep.x][nextStep.y]);
            stepIndex++;
            field.RobotX = nextStep.x;
            field.RobotY = nextStep.y;
            if (stepIndex >= field.RobotPath.size()) {
                field.hasPath = false;
                lout() << "ended path" << endl;
                cout << "Path Founded\nExit The Window" << endl;
            }
        }
    }
    return 0;
}
