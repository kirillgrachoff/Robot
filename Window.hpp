//
// Created by kirill on 6/24/18.
//

#include <SDL2/SDL.h>
#include "Field.hpp"

//using namespace std;

#ifndef ROBOTPROJECT_WINDOW_H
#define ROBOTPROJECT_WINDOW_H


class Window {
public:
    SDL_Window *window;
    SDL_Renderer *render;
    SDL_Event ev;
    long long cntX;
    long long cntY;

    const long long cellSize = 7;

    //Window();
    Window(Field &field);
    ~Window();

    void drawAll(Field &field);
    void drawElement(char element, long long x, long long y);

    void drawNoPathField(Field &field, unsigned int seconds);

private:
    void drawLines();
    void drawField(Field &field);
};


#endif //ROBOTPROJECT_WINDOW_H
