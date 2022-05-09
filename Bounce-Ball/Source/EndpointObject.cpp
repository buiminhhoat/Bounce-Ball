#include "../Header/EndpointObject.h"

EndpointObject::EndpointObject() {
	isOpened = false;
	scoreEndpoint = 0;
}

EndpointObject::~EndpointObject() {
	cleanUp();
}

