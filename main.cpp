#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <unistd.h>
#include "Constants.hpp"
#include "Window.hpp"
#include "Point.hpp"
#include "Field.hpp"

using namespace std;

int main() {
	std::ofstream lout("RobotProject.log");
    cout << "File with field: ";
    string filename;
    getline(cin, filename);
    Field field(filename, lout);
    if (field.existPath()) cout << "Path Found" << endl;
    else {
    	cout << "No Path Found" << endl;
    	return 0;
    }

    Window window(field);

    bool done = false;
    while (true) {
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
        usleep(50000);
        if (done) break;
        //Counting block
        if (field.existPath()) {
            field.step();
        }
    }
    return 0;
}
