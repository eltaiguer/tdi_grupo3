#include "Wiimote.h"
#include "Nunchuk.h"



class WiiData{
public:
	Wiimote* wiimote;
	Nunchuck* nunchuck;
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

	WiiData();
	~WiiData();

	
private:

};

