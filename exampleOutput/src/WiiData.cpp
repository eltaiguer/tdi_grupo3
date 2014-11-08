#include "WiiData.h"

WiiData::WiiData()
{
	wiimote = new Wiimote();
	nunchuck = new Nunchuck();
}

WiiData::~WiiData()
{
	delete(wiimote);
	delete(nunchuck);
}