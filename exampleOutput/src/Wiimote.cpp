#include "Wiimote.h"

Wiimote::Wiimote()
{
	Button_Up = 0;
	Button_Right = 0;
	Button_Down = 0;
	Button_Left = 0;
	Button_A = 0;
	Button_Minus = 0;
	Button_Home = 0;
	Button_Plus = 0;
	Button_One = 0;
	Button_Two = 0;

	Accel_X = 0;
	Accel_Y = 0;
	Accel_Z = 0;
	Accel_Roll = 0;
	Accel_Pitch = 0;

	SwingUp = 0;
	SwingRight = 0;
	SwingDown = 0;
	SwingLeft = 0;
}

Wiimote::~Wiimote()
{
}