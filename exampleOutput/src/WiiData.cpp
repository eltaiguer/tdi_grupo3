#include "WiiData.h"

WiiData::WiiData()
{
	wiimote = new Wiimote();
	nunchuck = new Nunchuck();
	instrumento = 0;
}

WiiData::~WiiData()
{
	delete(wiimote);
	delete(nunchuck);
}