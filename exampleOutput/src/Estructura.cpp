#include "Estructura.h"

Estructura::Estructura()
{
	for (int i=0; i<4; i++){
		data[i] = new WiiData();
	}
}

Estructura::~Estructura()
{
	for (int i=0; i<4; i++){
		delete(data[i]);
	}
}