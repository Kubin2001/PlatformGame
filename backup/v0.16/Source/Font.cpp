#include <iostream>
#include <SDL.h>
#include "Font.h"
SDL_Texture* Font::GetTexture() {
    return texture;
}

void Font::SetTexture(SDL_Texture* temptex) {
    texture = temptex;
}

SDL_Rect* Font::GetRectangle() {
    return &rectangle;
}

void Font::LoadText(int amount,int stepW,int stepH) {
    SDL_Rect temp;
    int xCord = 1;
    int yCord = 1;
    for (int i = 0; i < amount; i++)
    {
        sourceRectangles.push_back(temp);
        sourceRectangles[i].x = xCord;
        sourceRectangles[i].y = yCord;
        sourceRectangles[i].w = stepW;
        sourceRectangles[i].h = stepH;
        xCord += 31;
    }
}

void Font::RenderText(SDL_Renderer* renderer, std::string text, int x, int y, int w, int h, int step) {
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = w;
    rectangle.h = h;
    int temp = rectangle.x;
    for (int i = 0; i < text.length(); i++)
    {
        switch (text[i])
        {
        case 'A':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[0], &rectangle);
            break;
        case 'B':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[1], &rectangle);
            break;
        case 'C':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[2], &rectangle);
            break;
        case 'D':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[3], &rectangle);
            break;
        case 'E':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[4], &rectangle);
            break;
        case 'F':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[5], &rectangle);
            break;
        case 'G':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[6], &rectangle);
            break;
        case 'H':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[7], &rectangle);
            break;
        case 'I':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[8], &rectangle);
            break;
        case 'J':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[9], &rectangle);
            break;
        case 'K':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[10], &rectangle);
            break;
        case 'L':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[11], &rectangle);
            break;
        case 'M':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[12], &rectangle);
            break;
        case 'N':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[13], &rectangle);
            break;
        case 'O':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[14], &rectangle);
            break;
        case 'P':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[15], &rectangle);
            break;
        case 'Q':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[16], &rectangle);
            break;
        case 'R':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[17], &rectangle);
            break;
        case 'S':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[18], &rectangle);
            break;
        case 'T':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[19], &rectangle);
            break;
        case 'U':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[20], &rectangle);
            break;
        case 'V':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[21], &rectangle);
            break;
        case 'W':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[22], &rectangle);
            break;
        case 'X':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[23], &rectangle);
            break;
        case 'Y':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[24], &rectangle);
            break;
        case 'Z':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[25], &rectangle);
            break;
        case '0':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[26], &rectangle);
            break;
        case '1':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[27], &rectangle);
            break;
        case '2':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[28], &rectangle);
            break;
        case '3':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[29], &rectangle);
            break;
        case '4':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[30], &rectangle);
            break;
        case '5':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[31], &rectangle);
            break;
        case '6':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[32], &rectangle);
            break;
        case '7':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[33], &rectangle);
            break;
        case '8':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[34], &rectangle);
            break;
        case '9':
            SDL_RenderCopy(renderer, texture, &sourceRectangles[35], &rectangle);
            break;
        case '/':
            rectangle.y += step;
            rectangle.x = x - step;
           
        default:
            break;

        }
        rectangle.x += step;
    }
    rectangle.x = temp;
}
