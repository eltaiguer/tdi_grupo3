#include "Wiimote.h"
#include "Nunchuk.h"



class WiiData{
public:
	Wiimote* wiimote;
	Nunchuck* nunchuck;
	int instrumento;

	//variables para cada instrumento
	bool sel_right; // para cambiar instrumentos

	WiiData();
	~WiiData();

	
private:

};

