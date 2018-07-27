#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "Constants.h"
#include "Window.h"
#include "Point.h"
#include "Field.h"

using namespace std;

int main() {

    //Field field("field.robotField");
    cout << "File with field: ";
    string filename;
    getline(cin, filename);
    Field field(filename);
    field.path(Point(field.RobotX, field.RobotY), Point(field.ExitX, field.ExitY));
    cout << "Path Found" << endl;

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
        cout << "size: " << field.RobotPath.size() << " index: " << stepIndex << endl;
        for (int j = 0; j < 1e7; j++) {
            for (int k = 0; k < 5; k++);
        }

        if (done) break;

        //Counting block
        if (field.hasPath) {
            Point nextStep = field.RobotPath[stepIndex];
            cout << "Current: (" << field.RobotX << ", " << field.RobotY << ")" << endl;
            cout << "Next   : (" << nextStep.x << ", " << nextStep.y << ")" << endl;
            field[field.RobotX][field.RobotY] = ROAD;
            field[nextStep.x][nextStep.y] = ROBOT;
            //swap(field[field.RobotX][field.RobotY], field[nextStep.x][nextStep.y]);
            stepIndex++;
            field.RobotX = nextStep.x;
            field.RobotY = nextStep.y;
            if (stepIndex >= field.RobotPath.size()) {
                done = true;
            }
        }
    }
    return 0;
}
