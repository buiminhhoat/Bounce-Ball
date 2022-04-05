#include "BaseObject.h"

BaseObject::BaseObject() {
	Object_ = NULL;
	Rect_.x = 0;
	Rect_.y = 0;
	Rect_.w = 0;
	Rect_.h = 0;
}

BaseObject::~BaseObject() {
    CleanUp();
}

bool BaseObject::LoadImage(std::string path, SDL_Renderer* Screen) {
    CleanUp();
	SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        std::cerr << "Unable to load image " << path << " SDL image Error: "
            << IMG_GetError() << '\n';
        return false;
    }
    else {
        newTexture = SDL_CreateTextureFromSurface(Screen, loadedSurface);
        if (newTexture == NULL) {
            std::cerr << "Unable to create texture from " << path << " SDL Error: "
                << SDL_GetError() << '\n';
            return false;
        }
        else {
            Rect_.w = loadedSurface->w;
            Rect_.h = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }

    Object_ = newTexture;
    return (Object_ != NULL);
}

void BaseObject::Render(SDL_Renderer* des, const SDL_Rect* clip) {
    SDL_Rect renderquad = { Rect_.x, Rect_.y, Rect_.w, Rect_.h };
    SDL_RenderCopy(des, Object_, clip, &renderquad);
}

void BaseObject::CleanUp() {
    if (Object_ != NULL) {
        SDL_DestroyTexture(Object_);
        Object_ = NULL;
        Rect_.w = 0;
        Rect_.h = 0;
    }
}