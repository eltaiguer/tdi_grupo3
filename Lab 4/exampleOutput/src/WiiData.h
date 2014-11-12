#include "Wiimote.h"
#include "Nunchuk.h"
#include "Controller.h"


class WiiData{
public:
	Wiimote* wiimote;
	Nunchuck* nunchuck;
	Controller* controller;
	int instrumento;
	bool tipo_instrumento;

	//variables para cada instrumento
	//bool sel_right; // para cambiar instrumentos
	bool sel_up;
	bool sel_down;
	bool sel_home;

	bool sel_tipo;

	bool hit_wiimote1;
	bool hit_wiimote2;
	bool hit_wiimote3;
	bool hit_wiimote4;
	bool hit_wiimote5;



	//piano
	// arreglo de notas de escala
	int octaves[12];
	int cNote ;
	int cSharpNote;
	int dNote;
	int dSharpNote;
	int eNote;
	int fNote;
	int fSharpNote;
	int gNote;
	int gSharpNote;
	int aNote;
	int aSharpNote;
	int bNote;
	int octave;

	bool buttonUpSent;
	bool buttonASent;
	bool buttonBSent;
	bool buttonDownSent;
	bool buttonLeftSent;
	bool buttonRightSent;
	bool buttonRSent;
	bool buttonLSent;
	bool buttonXSent;
	bool buttonYSent;
	bool buttonZLSent;
	bool buttonZRSent;

	bool buttonMinusSent;
	bool buttonPlusSent;

	WiiData();
	~WiiData();

	
private:

};

