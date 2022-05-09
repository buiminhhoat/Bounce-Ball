#ifndef __LTEXTURE__
#define __LTEXTURE__

using namespace std;

class LTexture {
public:
	LTexture();
	~LTexture();

	enum COLOR {
		RED_COLOR,
		ORANGE_COLOR,
		YELLOW_COLOR,
		GREEN_COLOR,
		BLUE_COLOR,
		INDIGO_COLOR,
		PURPLE_COLOR,
		WHITE_COLOR,
		BLACK_COLOR,
	};

	bool loadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
	void cleanUp();
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setColor(int type);
	void showText(SDL_Renderer* screen,
		double xPosText, double yPosText,
		SDL_Rect* clip = NULL,
		double angle = 0.0,
		SDL_Point* center = NULL,
		SDL_RendererFlip flip = SDL_FLIP_NONE);

	void setPosX(double posX) { this->posX = posX; };
	void setPosY(double posY) { this->posY = posY; };

	double getPosX() { return this->posX; };
	double getPosY() { return this->posY; };

	double getWidth() { return this->width; };
	double getHeight() { return this->height; };

	void setWidth(double width) { this->width = width; };
	void setHeight(double height) { this->height = height; };
	void setText(const std::string& textVal) { this->textVal = textVal; };
	std::string getText() const { return this->textVal; };

private:
	std::string textVal;
	SDL_Color textColor;
	SDL_Texture* texture;

	double width;
	double height;
	double posX;
	double posY;
};

#endif