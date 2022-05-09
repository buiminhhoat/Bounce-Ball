#ifndef __ENDPOINTOBJECT__
#define __ENDPOINTOBJECT__

#include "BaseObject.h"

using namespace std;

class EndpointObject : public BaseObject {
#define SCORE_ENDPOINT 50
public:
	EndpointObject();
	~EndpointObject();

	bool getIsOpened() { return isOpened; };
	void setIsOpened(const bool& isOpened) { this->isOpened = isOpened; };

	int getScoreEndpoint() { return this->scoreEndpoint; };
	void setScoreEndpoint(const int& scoreEndpoint) { this->scoreEndpoint = scoreEndpoint; };

private:
	bool isOpened;
	int scoreEndpoint;
};

#endif