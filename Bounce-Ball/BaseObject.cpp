#include "BaseObject.h"

BaseObject::BaseObject() {
    object = NULL;
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
}

BaseObject::~BaseObject() {
    cleanUp();
}

bool BaseObject::loadImage(std::string path, SDL_Renderer* screen) {
    cleanUp();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        std::cerr << "Unable to load image " << path << " SDL image Error: "
            << IMG_GetError() << '\n';
        return false;
    }
    else {
        newTexture = SDL_CreateTextureFromSurface(screen, loadedSurface);
        if (newTexture == NULL) {
            std::cerr << "Unable to create texture from " << path << " SDL Error: "
                << SDL_GetError() << '\n';
            return false;
        }
        else {
            rect.w = loadedSurface->w;
            rect.h = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }

    object = newTexture;
    return (object != NULL);
}

void BaseObject::render(SDL_Renderer* des, const SDL_Rect* clip) {
    SDL_Rect renderquad = { rect.x, rect.y, rect.w, rect.h };
    SDL_RenderCopy(des, object, clip, &renderquad);
}

void BaseObject::cleanUp() {
    if (object != NULL) {
        SDL_DestroyTexture(object);
        object = NULL;
        rect.w = 0;
        rect.h = 0;
    }
}