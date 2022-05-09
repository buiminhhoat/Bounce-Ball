#include "../Header/BaseObject.h"
#include "../Header/LTexture.h"

LTexture::LTexture() {
	/* RGB WHITE */
	textColor.r = 255;
	textColor.g = 255;
	textColor.b = 255;
	texture = NULL;
	textVal = "";
	width = 0;
	height = 0;
}

LTexture::~LTexture() {
	cleanUp();
}

bool LTexture::loadFromRenderText(TTF_Font* font, SDL_Renderer* screen) {
	cleanUp();
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, textVal.c_str(), textColor);
	if (text_surface != NULL) {
		texture = SDL_CreateTextureFromSurface(screen, text_surface);
		width = text_surface->w;
		height = text_surface->h;
		SDL_FreeSurface(text_surface);
	}
	else {
		printf("Unable to create texture from %s! SDL Error: %s\n", textVal.c_str(), SDL_GetError());
	}
	return (text_surface != NULL);
}

void LTexture::cleanUp() {
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
	textColor.r = red;
	textColor.g = green;
	textColor.b = blue;
}

void LTexture::setColor(int type) {
	if (type == RED_COLOR) {
		/* RGB RED */
		SDL_Color color = { 255, 0, 0 };
		textColor = color;
	}
	if (type == ORANGE_COLOR) {
		/* RGB ORANGE */
		SDL_Color color = { 255, 165, 0 };
		textColor = color;
	}
	if (type == YELLOW_COLOR) {
		/* RGB YELLOW */
		SDL_Color color = { 255, 255, 0 };
		textColor = color;
	}
	if (type == GREEN_COLOR) {
		/* RGB GREEN */
		SDL_Color color = { 0, 255, 0 };
		textColor = color;
	}
	if (type == BLUE_COLOR) {
		/* RGB BLUE */
		SDL_Color color = { 0, 0, 255 };
		textColor = color;
	}
	if (type == INDIGO_COLOR) {
		/* RGB INDIGO */
		SDL_Color color = { 75, 0, 130 };
		textColor = color;
	}
	if (type == PURPLE_COLOR) {
		/* RGB PURPLE */
		SDL_Color color = { 128, 0, 128 };
		textColor = color;
	}
	if (type == WHITE_COLOR) {
		/* RGB WHITE */
		SDL_Color color = { 255, 255, 255 };
		textColor = color;
	}
	if (type == BLACK_COLOR) {
		/* RGB BLACK */
		SDL_Color color = { 0, 0, 0 };
		textColor = color;
	}
}

void LTexture::showText(SDL_Renderer* screen,
	double xPosText, double yPosText,
	SDL_Rect* clip /* = NULL */,
	double angle /* = 0.0 */,
	SDL_Point* center /* = NULL */,
	SDL_RendererFlip flip /* = SDL_FLIP_NONE */) {
	SDL_Rect renderQuad = { xPosText, yPosText, width, height };
	if (clip != NULL) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(screen, texture, clip, &renderQuad, angle, center, flip);
	cleanUp();
}