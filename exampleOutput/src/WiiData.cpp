#include "WiiData.h"

WiiData::WiiData()
{
	wiimote = new Wiimote();
	nunchuck = new Nunchuck();
	instrumento = 1;
	tipo_instrumento = true;
	//1 bateria
	//2 faluta
	//3 maracas
	//4 piano

	//sel_right = false;
	sel_up    = false;
	sel_down  = false;
	sel_home  = false;

	sel_tipo = false;
}

WiiData::~WiiData()
{
	delete(wiimote);
	delete(nunchuck);
}