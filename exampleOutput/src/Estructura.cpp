#include "Estructura.h"

Estructura::Estructura()
{
	for (int i=1; i<5; i++){
		data[i] = new WiiData();
	}
}

Estructura::~Estructura()
{
	for (int i=1; i<5; i++){
		delete(data[i]);
	}
}