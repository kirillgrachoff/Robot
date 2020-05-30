//
// Created by kirill on 6/24/18.
//

#include <zconf.h>
#include "Window.hpp"
#include "Constants.hpp"
#include "Field.hpp"

/*Window::Window() {
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Labyrinth", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, cntX * cellSize + 1, cntY * cellSize + 1, 0);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    this->cntX = cntX;
    this->cntY = cntY;
}*/

Window::Window(Field &field) {
    cntX = field.cntX;
    cntY = field.cntY;
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Robot BOBA", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, cntX * cellSize + 1, cntY * cellSize + 1, 0);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Window::~Window() {
    SDL_Quit();
}

void Window::drawElement(char element, long long x, long long y) {
    switch(element) {
        case WALL:
            SDL_SetRenderDrawColor(render, CL_WALL);
            break;
        case EXIT:
            SDL_SetRenderDrawColor(render, CL_EXIT);
            break;
        case ROBOT:
            SDL_SetRenderDrawColor(render, CL_ROBOT);
            break;
        case ROAD:
            SDL_SetRenderDrawColor(render, CL_ROAD);
            break;
        default://case NULLELEMENT:
            SDL_SetRenderDrawColor(render, CL_NULLELEMENT);
            break;
    }
    SDL_Rect *rectangle = new SDL_Rect;
    rectangle->x = x * cellSize + 1;
    rectangle->y = y * cellSize + 1;
    rectangle->h = cellSize - 1;
    rectangle->w = cellSize - 1;
    SDL_RenderFillRect(render, rectangle);
}

void Window::drawLines() {
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    for (long long i = 0; i <= cntX; i++) {
        SDL_RenderDrawLine(render, i * cellSize, 0, i * cellSize, cntY * cellSize);
    }
    for (long long i = 0; i <= cntY; i++) {
        SDL_RenderDrawLine(render, 0, i * cellSize, cntX * cellSize, i * cellSize);
    }
}

void Window::drawField(Field &field) {
    for (long long y = 0; y < cntY; y++) {
        for (long long x = 0; x < cntX; x++) {
            this->drawElement(field[x][y], x, y);
        }
    }
}

void Window::drawAll(Field &field) {
    SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
    SDL_RenderClear(render);
    this->drawLines();
    this->drawField(field);
    SDL_RenderPresent(render);
}

void Window::drawNoPathField(Field &field, unsigned int seconds) {
    drawAll(field);
    sleep(seconds);
}
