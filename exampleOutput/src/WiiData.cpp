#include "WiiData.h"

WiiData::WiiData()
{
	wiimote = new Wiimote();
	nunchuck = new Nunchuck();
	instrumento = 1;
	//1 bateria
	//2 faluta
	//3 maracas
	//4 piano

	sel_right = false;

}

WiiData::~WiiData()
{
	delete(wiimote);
	delete(nunchuck);
}