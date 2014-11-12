#include "WiiData.h"

WiiData::WiiData()
{
	wiimote = new Wiimote();
	nunchuck = new Nunchuck();
	controller = new Controller();
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


	// cosas para el piano
	for (int i=0; i<12;i++){
		octaves[i]=i*12;
	}

	cNote = 0;
	cSharpNote = 1;
	dNote = 2;
	dSharpNote = 3;
	eNote = 4;
	fNote = 5;
	fSharpNote = 6;
	gNote = 7;
	gSharpNote = 8;
	aNote = 9;
	aSharpNote = 10;
	bNote = 11;
	octave= 5;

	buttonUpSent = false;
	buttonASent = false;
	buttonBSent = false;
	buttonDownSent = false;
	buttonLeftSent = false;
	buttonRightSent = false;
	buttonRSent = false;
	buttonLSent = false;
	buttonXSent = false;
	buttonYSent = false;
	buttonZLSent = false;
	buttonZRSent = false;

	buttonMinusSent = false;
	buttonPlusSent =false;
}

WiiData::~WiiData()
{
	delete(wiimote);
	delete(nunchuck);
	delete(controller);
}