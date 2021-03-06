/*
* Copyright (c) 2013 Dan Wilcox <danomatika@gmail.com>
*
* BSD Simplified License.
* For information on usage and redistribution, and for a DISCLAIMER OF ALL
* WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*
* See https://github.com/danomatika/ofxMidi for documentation
*
*/
#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup() {

	ofSetVerticalSync(true);
	ofBackground(0);
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetFrameRate(200);

	// connect

	midiOutW1.openPort("live_W1"); // by name
	midiOutW2.openPort("live_W2"); // by name
	midiOutW3.openPort("live_W3"); // by name
	midiOutW4.openPort("live_W4"); // by name

	// Revisar variables
	channel = 2;
	currentPgm = 0;
	note = 0;
	velocity = 64;
	pan = 0;
	bend = 0;
	touch = 0;
	polytouch = 0;

	sonar = false;
	
	//// cosas para el piano
	//for (int i=0; i<12;i++){
	//	octaves[i]=i*12;
	//}

	//cNote = 0;
	//cSharpNote = 1;
	//dNote = 2;
	//dSharpNote = 3;
	//eNote = 4;
	//fNote = 5;
	//fSharpNote = 6;
	//gNote = 7;
	//gSharpNote = 8;
	//aNote = 9;
	//aSharpNote = 10;
	//bNote = 11;
	//octave= 5;

	//buttonUpSent = false;
	//buttonASent = false;
	//buttonBSent = false;
	//buttonDownSent = false;
	//buttonLeftSent = false;
	//buttonRightSent = false;
	//buttonRSent = false;
	//buttonLSent = false;
	//buttonXSent = false;
	//buttonYSent = false;
	//buttonZLSent = false;
	//buttonZRSent = false;

	//buttonMinusSent = false;
	//buttonPlusSent =false;
	
	
	
	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);

	e = new Estructura();
	
	//Titulos
	wiimoteI.loadImage("wiimote1.png");
	wiimoteII.loadImage("wiimote2.png");
	wiimoteIII.loadImage("wiimote3.png");
	wiimoteIV.loadImage("wiimote4.png");

	//Imagenes
	piano.loadImage("piano.png");
	piano_selected.loadImage("piano_selected.png");
	maracas.loadImage("maracas.png");
	maracas_selected.loadImage("maracas_selected.png");
	bateria.loadImage("bateria.png");
	bateria_selected.loadImage("bateria_selected.png");
	flauta.loadImage("flauta.png");
	flauta_selected.loadImage("flauta_selected.png");
	piccolo.loadImage("piccolo.png");
	piccolo_selected.loadImage("piccolo_selected.png");

	// Instrucciones
	sel_inst.loadImage("seleccionar-instrumento.png");
	camb_inst.loadImage("cambiar-instrumento.png");
	conf_inst.loadImage("confirmar-instrumento.png");
}

//--------------------------------------------------------------
void testApp::update() {
	
	// CAPTURA DE DATOS DE LOS MENSAJES OSC

	// check for waiting messages
	while(receiver.hasWaitingMessages()){

		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);

		// Recorro las direcciones para saber de donde es el mensaje
		bool dirEncontrada = false;
		int indice_remote = 1;
		string str_indice_remote;
		while(!dirEncontrada){
			
			char numstr[21]; // enough to hold all numbers up to 64-bits
			str_indice_remote = itoa(indice_remote, numstr, 10);

			if (m.getAddress()=="/Brian/"+str_indice_remote+"/Nunchuk/Buttons"){
				e->data[indice_remote]->nunchuck->Button_C = m.getArgAsInt32(0);
				e->data[indice_remote]->nunchuck->Button_Z = m.getArgAsInt32(1);
				e->data[indice_remote]->nunchuck->Button_X = m.getArgAsFloat(2);
				e->data[indice_remote]->nunchuck->Button_Y = m.getArgAsFloat(3);
				dirEncontrada = true;
			}
			if (m.getAddress()=="/Brian/"+str_indice_remote+"/Nunchuk/Accel"){
				e->data[indice_remote]->nunchuck->Accel_X = m.getArgAsFloat(0);
				e->data[indice_remote]->nunchuck->Accel_Y = m.getArgAsFloat(1);
				e->data[indice_remote]->nunchuck->Accel_Z = m.getArgAsFloat(2);
				e->data[indice_remote]->nunchuck->Accel_Roll = m.getArgAsFloat(3);
				e->data[indice_remote]->nunchuck->Accel_Pitch = m.getArgAsFloat(4);
				dirEncontrada = true;
			}
			if (m.getAddress()=="/Brian/"+str_indice_remote+"/Nunchuk/Gestures"){
				e->data[indice_remote]->nunchuck->SwingUp = m.getArgAsInt32(0);
				e->data[indice_remote]->nunchuck->SwingRight = m.getArgAsInt32(1);
				e->data[indice_remote]->nunchuck->SwingDown = m.getArgAsInt32(2);
				e->data[indice_remote]->nunchuck->SwingLeft = m.getArgAsInt32(3);
				dirEncontrada = true;
			}
			if (m.getAddress()=="/Brian/"+str_indice_remote+"/Wiimote/Buttons"){
				e->data[indice_remote]->wiimote->Button_Up = m.getArgAsInt32(0);
				e->data[indice_remote]->wiimote->Button_Right = m.getArgAsInt32(1);				
				e->data[indice_remote]->wiimote->Button_Down = m.getArgAsInt32(2);
				e->data[indice_remote]->wiimote->Button_Left = m.getArgAsInt32(3);
				e->data[indice_remote]->wiimote->Button_A = m.getArgAsInt32(4);
				e->data[indice_remote]->wiimote->Button_Minus = m.getArgAsInt32(5);
				e->data[indice_remote]->wiimote->Button_Home = m.getArgAsInt32(6);
				e->data[indice_remote]->wiimote->Button_Plus = m.getArgAsInt32(7);
				e->data[indice_remote]->wiimote->Button_One = m.getArgAsInt32(8);
				e->data[indice_remote]->wiimote->Button_Two = m.getArgAsInt32(9);
				e->data[indice_remote]->wiimote->Button_B = m.getArgAsInt32(10);
				dirEncontrada = true;
			}
			if (m.getAddress()=="/Brian/"+str_indice_remote+"/Wiimote/Accel"){
				e->data[indice_remote]->wiimote->Accel_X = m.getArgAsFloat(0);
				e->data[indice_remote]->wiimote->Accel_Y = m.getArgAsFloat(1);
				e->data[indice_remote]->wiimote->Accel_Z = m.getArgAsFloat(2);
				e->data[indice_remote]->wiimote->Accel_Roll = m.getArgAsFloat(3);
				e->data[indice_remote]->wiimote->Accel_Pitch = m.getArgAsFloat(4);
				dirEncontrada = true;
			}
			if (m.getAddress()=="/Brian/"+str_indice_remote+"/Wiimote/Gestures"){
				e->data[indice_remote]->wiimote->SwingUp = m.getArgAsInt32(0);
				e->data[indice_remote]->wiimote->SwingRight = m.getArgAsInt32(1);
				e->data[indice_remote]->wiimote->SwingDown = m.getArgAsInt32(2);
				e->data[indice_remote]->wiimote->SwingLeft = m.getArgAsInt32(3);
				dirEncontrada = true;
			}

			if (m.getAddress()=="/Brian/"+str_indice_remote+"/Controller/Buttons"){
				e->data[indice_remote]->controller->Button_Up = m.getArgAsInt32(0);
				e->data[indice_remote]->controller->Button_Right = m.getArgAsInt32(1);
				e->data[indice_remote]->controller->Button_Down = m.getArgAsInt32(2);
				e->data[indice_remote]->controller->Button_Left = m.getArgAsInt32(3);
				e->data[indice_remote]->controller->Button_Minus = m.getArgAsInt32(4);
				e->data[indice_remote]->controller->Button_Home = m.getArgAsInt32(5);
				e->data[indice_remote]->controller->Button_Plus = m.getArgAsInt32(6);
				e->data[indice_remote]->controller->Button_X = m.getArgAsInt32(7);
				e->data[indice_remote]->controller->Button_A = m.getArgAsInt32(8);
				e->data[indice_remote]->controller->Button_B = m.getArgAsInt32(9);
				e->data[indice_remote]->controller->Button_Y = m.getArgAsInt32(10);
				e->data[indice_remote]->controller->Button_L = m.getArgAsInt32(11);
				e->data[indice_remote]->controller->Button_ZL = m.getArgAsInt32(12);
				e->data[indice_remote]->controller->Button_R = m.getArgAsInt32(13);
				e->data[indice_remote]->controller->Button_ZR = m.getArgAsInt32(14);

				dirEncontrada = true;
			}
			
			indice_remote++;
		}
	}

	
	// FIN CAPUTRA

	
	for (int i=1; i<5; i++){
	
		//Envio datos si no estoy en modo home
		if (!e->data[i]->sel_home){

			if (e->data[i]->instrumento == 1){ // Bater�a seleccionada

				if (!e->data[i]->hit_wiimote1 && e->data[i]->wiimote->SwingDown == 1 && e->data[i]->wiimote->Button_B == 0 && e->data[i]->wiimote->Button_A == 0){ // HIHAT
					note = ofMap('W', 48, 122, 0, 127);
					midiOutW1.sendNoteOn(1, note,  velocity);
					e->data[i]->hit_wiimote1 = true;
					e->data[i]->wiimote->SwingDown = 0;
				} else if (e->data[i]->wiimote->SwingDown == 0 && e->data[i]->wiimote->Button_B == 0 && e->data[i]->wiimote->Button_A == 0){
					e->data[i]->hit_wiimote1 = false;
				}

				if (!e->data[i]->hit_wiimote2 && e->data[i]->wiimote->SwingDown == 1 && e->data[i]->wiimote->Button_B == 1 && e->data[i]->wiimote->Button_A == 0){ // OTRO PLATILLO
					note = ofMap('W', 48, 122, 0, 127);
					midiOutW1.sendNoteOn(2, note,  velocity);
					e->data[i]->hit_wiimote2 = true;
					e->data[i]->wiimote->SwingDown = 0;
				} else if (e->data[i]->wiimote->SwingDown == 0 && e->data[i]->wiimote->Button_B == 1 && e->data[i]->wiimote->Button_A == 0){
					e->data[i]->hit_wiimote2 = false;
				}

				if (!e->data[i]->hit_wiimote3 && e->data[i]->nunchuck->SwingDown == 1 && e->data[i]->nunchuck->Button_Z == 0){ // REDOBLANTE
					note = ofMap('W', 48, 122, 0, 127);
					midiOutW1.sendNoteOn(3, note,  velocity);
					e->data[i]->hit_wiimote3 = true;
					e->data[i]->nunchuck->SwingDown = 0;
				} else if (e->data[i]->nunchuck->SwingDown == 0 && e->data[i]->nunchuck->Button_Z == 0){
					e->data[i]->hit_wiimote3 = false;
				}

				if (!e->data[i]->hit_wiimote4 && e->data[i]->nunchuck->SwingDown == 1 && e->data[i]->nunchuck->Button_Z == 1){ // OTRO REDOBLANTE
					note = ofMap('W', 48, 122, 0, 127);
					midiOutW1.sendNoteOn(4, note,  velocity);
					e->data[i]->hit_wiimote4 = true;
					e->data[i]->nunchuck->SwingDown = 0;
				} else if (e->data[i]->nunchuck->SwingDown == 0 && e->data[i]->nunchuck->Button_Z == 1){
					e->data[i]->hit_wiimote4 = false;
				}
				
				if (!e->data[i]->hit_wiimote5 && e->data[i]->wiimote->SwingDown == 1 && e->data[i]->wiimote->Button_A == 1 && e->data[i]->wiimote->Button_B == 0){ // Wiimote REDOBLANTE
					note = ofMap('W', 48, 122, 0, 127);
					midiOutW1.sendNoteOn(3, note,  velocity);
					e->data[i]->hit_wiimote5 = true;
					e->data[i]->wiimote->SwingDown = 0;
				} else if (e->data[i]->wiimote->SwingDown == 0 && e->data[i]->wiimote->Button_A == 1 && e->data[i]->wiimote->Button_B == 0){
					e->data[i]->hit_wiimote5 = false;
				}
			}

			if (e->data[i]->instrumento == 2){ // Instrumento Viento seleccionada

				int canal = 1;
				if (e->data[i]->tipo_instrumento){
					note = 50;
					canal = 1;
				}else{
					note = 70;
					canal = 2;
				}

				if (!e->data[i]->hit_wiimote1 && e->data[i]->wiimote->Button_Up == 1){
					midiOutW2.sendNoteOn(canal, note,  velocity);
					e->data[i]->hit_wiimote1 = true;
				} else if (e->data[i]->hit_wiimote1 && e->data[i]->wiimote->Button_Up == 0){
					e->data[i]->hit_wiimote1 = false;
					midiOutW2 << NoteOff(canal, note, velocity);
				}

				if (e->data[i]->tipo_instrumento){
					note = 55;
					canal = 1;
				}else{
					note = 75;
					canal = 2;
				}
				if (!e->data[i]->hit_wiimote2 && e->data[i]->wiimote->Button_Down == 1){
					midiOutW2.sendNoteOn(canal, note,  velocity);
					e->data[i]->hit_wiimote2 = true;
				} else if (e->data[i]->hit_wiimote2 && e->data[i]->wiimote->Button_Down == 0){
					e->data[i]->hit_wiimote2 = false;
					midiOutW2 << NoteOff(canal, note, velocity);
				}
		
				if (e->data[i]->tipo_instrumento){
					note = 60;
					canal = 1;
				}else{
					note = 80;
					canal = 2;
				}
				if (!e->data[i]->hit_wiimote3 && e->data[i]->wiimote->Button_A == 1){
					midiOutW2.sendNoteOn(canal, note,  velocity);
					e->data[i]->hit_wiimote3 = true;
				} else if (e->data[i]->hit_wiimote3 && e->data[i]->wiimote->Button_A == 0){
					e->data[i]->hit_wiimote3 = false;
					midiOutW2 << NoteOff(canal, note, velocity);
				}
		
				if (e->data[i]->tipo_instrumento){
					note = 65;
					canal = 1;
				}else{
					note = 85;
					canal = 2;
				}
				if (!e->data[i]->hit_wiimote4 && e->data[i]->wiimote->Button_One == 1){
					midiOutW2.sendNoteOn(canal, note,  velocity);
					e->data[i]->hit_wiimote4 = true;
				} else if (e->data[i]->hit_wiimote4 && e->data[i]->wiimote->Button_One == 0){
					e->data[i]->hit_wiimote4 = false;
					midiOutW2 << NoteOff(canal, note, velocity);
				}

				if (e->data[i]->tipo_instrumento){
					note = 70;
					canal = 1;
				}else{
					note = 90;
					canal = 2;
				}
				if (!e->data[i]->hit_wiimote5 && e->data[i]->wiimote->Button_Two == 1){
					midiOutW2.sendNoteOn(canal, note,  velocity);
					e->data[i]->hit_wiimote5 = true;
				} else if (e->data[i]->hit_wiimote5 && e->data[i]->wiimote->Button_Two == 0){
					e->data[i]->hit_wiimote5 = false;
					midiOutW2 << NoteOff(canal, note, velocity);
				}

			}

			// **** MARACAS ****
			if (e->data[i]->instrumento == 4){
			
				if (!e->data[i]->hit_wiimote1 && e->data[i]->wiimote->SwingDown == 1){ // MARACA HACIA ABAJO
					note = ofMap('W', 48, 122, 0, 127);
					midiOutW4.sendNoteOn(1, note,  velocity);
					e->data[i]->hit_wiimote1 = true;
					e->data[i]->wiimote->SwingDown = 0;
				} else if (e->data[i]->wiimote->SwingDown == 0){
					e->data[i]->hit_wiimote1 = false;
				}
				if (!e->data[i]->hit_wiimote2 && e->data[i]->wiimote->SwingUp == 1){ // MARACA HACIA ARRIBA
					note = ofMap('W', 48, 122, 0, 127);
					midiOutW4.sendNoteOn(1, note,  velocity);
					e->data[i]->hit_wiimote2 = true;
					e->data[i]->wiimote->SwingUp = 0;
				} else if (e->data[i]->wiimote->SwingUp == 0){
					e->data[i]->hit_wiimote2 = false;
				}
				if (!e->data[i]->hit_wiimote1 && e->data[i]->nunchuck->SwingDown == 1){ // MARACA HACIA ABAJO
					note = ofMap('W', 48, 122, 0, 127);
					midiOutW4.sendNoteOn(2, note,  velocity);
					e->data[i]->hit_wiimote1 = true;
					e->data[i]->nunchuck->SwingDown = 0;
				} else if (e->data[i]->nunchuck->SwingDown == 0){
					e->data[i]->hit_wiimote1 = false;
				}
				if (!e->data[i]->hit_wiimote2 && e->data[i]->nunchuck->SwingUp == 1){ // MARACA HACIA ARRIBA
					note = ofMap('W', 48, 122, 0, 127);
					midiOutW4.sendNoteOn(2, note,  velocity);
					e->data[i]->hit_wiimote2 = true;
					e->data[i]->nunchuck->SwingUp = 0;
				} else if (e->data[i]->nunchuck->SwingUp == 0){
					e->data[i]->hit_wiimote2 = false;
				}

			}
			
			
			// TECLADO
			if (e->data[i]->instrumento == 3){

				if (!e->data[i]->buttonUpSent && e->data[i]->controller->Button_Up == 1){
					printf("UP %d\n", e->data[i]->octaves[e->data[i]->octave] + e->data[i]->dSharpNote);
					note = ofMap(e->data[i]->octaves[e->data[i]->octave] + e->data[i]->dSharpNote,48,122,0,127);
					midiOutW3.sendNoteOn(1,note,velocity);
					e->data[i]->buttonUpSent=true;
				}
				else if(e->data[i]->buttonUpSent && e->data[i]->controller->Button_Up == 0){
					printf("UP OFF %d\n", e->data[i]->octaves[e->data[i]->octave] + e->data[i]->dSharpNote);
					note = ofMap(e->data[i]->octaves[e->data[i]->octave] + e->data[i]->dSharpNote,48,122,0,127);
					midiOutW3.sendNoteOff(1,note,velocity);
					e->data[i]->buttonUpSent = false;
				}

				if (!e->data[i]->buttonRightSent && e->data[i]->controller->Button_Right == 1){
					printf("RIGHT %d\n", e->data[i]->octaves[e->data[i]->octave] + e->data[i]->cNote);
					note = ofMap(e->data[i]->octaves[e->data[i]->octave] + e->data[i]->cNote,48,122,0,127);
					midiOutW3.sendNoteOn(1,note,velocity);
					e->data[i]->buttonRightSent = true;
				}
				else if(e->data[i]->buttonRightSent && e->data[i]->controller->Button_Right == 0){
					printf("RIGHT OFF %d\n", e->data[i]->octaves[e->data[i]->octave] + e->data[i]->cNote);
					note = ofMap(e->data[i]->octaves[e->data[i]->octave] + e->data[i]->cNote,48,122,0,127);
					midiOutW3.sendNoteOff(1,note,velocity);
					e->data[i]->buttonRightSent = false;
				}

				if (!e->data[i]->buttonDownSent && e->data[i]->controller->Button_Down == 1){
					printf("DOWN %d\n", e->data[i]->octaves[e->data[i]->octave] + e->data[i]->cSharpNote);
					note = ofMap(e->data[i]->octaves[e->data[i]->octave] + e->data[i]->cSharpNote,48,122,0,127);
					midiOutW3.sendNoteOn(1,note,velocity);
					e->data[i]->buttonDownSent = true;
				}
				else if(e->data[i]->buttonDownSent && e->data[i]->controller->Button_Down == 0){
					printf("DOWN OFF %d\n", e->data[i]->octaves[e->data[i]->octave] + e->data[i]->cSharpNote);
					note = ofMap(e->data[i]->octaves[e->data[i]->octave] + e->data[i]->cSharpNote,48,122,0,127);
					midiOutW3.sendNoteOff(1,note,velocity);
					e->data[i]->buttonDownSent = false;
				}

				if (!e->data[i]->buttonLeftSent && e->data[i]->controller->Button_Left == 1){
					printf("LEFT %d\n", e->data[i]->octaves[e->data[i]->octave] + e->data[i]->dNote);
					note = ofMap(e->data[i]->octaves[e->data[i]->octave] + e->data[i]->dNote,48,122,0,127);
					midiOutW3.sendNoteOn(1,note,velocity);
					e->data[i]->buttonLeftSent = true;
				}
				else if(e->data[i]->buttonLeftSent && e->data[i]->controller->Button_Left == 0){
					printf("LEFT  OFF %d\n", e->data[i]->octaves[e->data[i]->octave] + e->data[i]->dNote);
					note = ofMap(e->data[i]->octaves[e->data[i]->octave] + e->data[i]->dNote,48,122,0,127);
					midiOutW3.sendNoteOff(1,note,velocity);
					e->data[i]->buttonLeftSent = false;
				}

				if (!e->data[i]->buttonLSent && e->data[i]->controller->Button_L == 1){
					printf("L %d\n", e->data[i]->octaves[e->data[i]->octave] + e->data[i]->eNote);
					note = ofMap(e->data[i]->octaves[e->data[i]->octave] + e->data[i]->eNote,48,122,0,127);
					midiOutW3.sendNoteOn(2,note,velocity);
					e->data[i]->buttonLSent = true;
				}
				else if(e->data[i]->buttonLSent && e->data[i]->controller->Button_L == 0){
					note = ofMap(e->data[i]->octaves[e->data[i]->octave] + e->data[i]->eNote,48,122,0,127);
					midiOutW3.sendNoteOff(2,note,velocity);
					e->data[i]->buttonLSent = false;
				}

				if (!e->data[i]->buttonZLSent && e->data[i]->controller->Button_ZL == 1){
					printf("ZL %d\n", e->data[i]->octaves[e->data[i]->octave] + e->data[i]->fNote);
					note = ofMap(e->data[i]->octaves[e->data[i]->octave] + e->data[i]->fNote,48,122,0,127);
					midiOutW3.sendNoteOn(2,note,velocity);
					e->data[i]->buttonZLSent = true;
				}
				else if(e->data[i]->buttonZLSent && e->data[i]->controller->Button_ZL == 0){
					note = ofMap(e->data[i]->octaves[e->data[i]->octave] + e->data[i]->fNote,48,122,0,127);
					midiOutW3.sendNoteOff(2,note,velocity);
					e->data[i]->buttonZLSent = false;
				}

				if (!e->data[i]->buttonZRSent && e->data[i]->controller->Button_ZR == 1){
					printf("ZR %d\n", e->data[i]->octaves[e->data[i]->octave] + e->data[i]->fSharpNote);
					note = ofMap(e->data[i]->octaves[e->data[i]->octave] + e->data[i]->fSharpNote,48,122,0,127);
					midiOutW3.sendNoteOn(2,note,velocity);
					e->data[i]->buttonZRSent = true;
				}
				else if(e->data[i]->buttonZRSent && e->data[i]->controller->Button_ZR == 0){
					note = ofMap(e->data[i]->octaves[e->data[i]->octave] + e->data[i]->fSharpNote,48,122,0,127);
					midiOutW3.sendNoteOff(2,note,velocity);
					e->data[i]->buttonZRSent = false;
				}

				if (!e->data[i]->buttonRSent && e->data[i]->controller->Button_R == 1){
					printf("R %d\n", e->data[i]->octaves[e->data[i]->octave] + e->data[i]->gNote);
					note = ofMap(e->data[i]->octaves[e->data[i]->octave] + e->data[i]->gNote,48,122,0,127);
					midiOutW3.sendNoteOn(2,note,velocity);
					e->data[i]->buttonRSent=true;
				}
				else if(e->data[i]->buttonRSent && e->data[i]->controller->Button_R == 0){
					note = ofMap(e->data[i]->octaves[e->data[i]->octave] + e->data[i]->gNote,48,122,0,127);
					midiOutW3.sendNoteOff(2,note,velocity);
					e->data[i]->buttonRSent = false;
				}

				if (!e->data[i]->buttonXSent && e->data[i]->controller->Button_X == 1){
					printf("X %d\n", e->data[i]->octaves[e->data[i]->octave] + e->data[i]->gSharpNote);
					note = ofMap(e->data[i]->octaves[e->data[i]->octave] + e->data[i]->gSharpNote,48,122,0,127);
					midiOutW3.sendNoteOn(3,note,velocity);
					e->data[i]->buttonXSent = true;
				}
				else if(e->data[i]->buttonXSent && e->data[i]->controller->Button_X == 0){
					note = ofMap(e->data[i]->octaves[e->data[i]->octave] + e->data[i]->gSharpNote,48,122,0,127);
					midiOutW3.sendNoteOff(3,note,velocity);
					e->data[i]->buttonXSent = false;
				}

				if (!e->data[i]->buttonASent && e->data[i]->controller->Button_A == 1){
					printf("A %d\n", e->data[i]->octaves[e->data[i]->octave] + e->data[i]->aNote);
					note = ofMap(e->data[i]->octaves[e->data[i]->octave] + e->data[i]->aNote,48,122,0,127);
					midiOutW3.sendNoteOn(3,note,velocity);
					e->data[i]->buttonASent = true;
				}
				else if(e->data[i]->buttonASent && e->data[i]->controller->Button_A == 0){
					note = ofMap(e->data[i]->octaves[e->data[i]->octave] + e->data[i]->aNote,48,122,0,127);
					midiOutW3.sendNoteOff(3,note,velocity);
					e->data[i]->buttonASent = false;
				}

				if (!e->data[i]->buttonBSent && e->data[i]->controller->Button_B == 1){
					printf("B %d\n", e->data[i]->octaves[e->data[i]->octave] + e->data[i]->aSharpNote);
					note = ofMap(e->data[i]->octaves[e->data[i]->octave] + e->data[i]->aSharpNote,48,122,0,127);
					midiOutW3.sendNoteOn(3,note,velocity);
					e->data[i]->buttonBSent = true;
				}
				else if(e->data[i]->buttonBSent && e->data[i]->controller->Button_B == 0){
					note = ofMap(e->data[i]->octaves[e->data[i]->octave] + e->data[i]->aSharpNote,48,122,0,127);
					midiOutW3.sendNoteOff(3,note,velocity);
					e->data[i]->buttonBSent = false;
				}

				if (!e->data[i]->buttonYSent && e->data[i]->controller->Button_Y == 1){
					printf("Y %d\n", e->data[i]->octaves[e->data[i]->octave] + e->data[i]->bNote);
					note = ofMap(e->data[i]->octaves[e->data[i]->octave] + e->data[i]->bNote,48,122,0,127);
					midiOutW3.sendNoteOn(3,note,velocity);
					e->data[i]->buttonYSent = true;
				}
				else if(e->data[i]->buttonYSent && e->data[i]->controller->Button_Y == 0){
					note = ofMap(e->data[i]->octaves[e->data[i]->octave] + e->data[i]->bNote,48,122,0,127);
					midiOutW3.sendNoteOff(3,note,velocity);
					e->data[i]->buttonYSent = false;
				}

				if (!e->data[i]->buttonPlusSent && e->data[i]->controller->Button_Plus){
					if (e->data[i]->octave<9){
						e->data[i]->octave++;
						printf("OCTAVA %d \n", e->data[i]->octave);

					}
					e->data[i]->buttonPlusSent = true;
				}
				else if(e->data[i]->buttonPlusSent && !e->data[i]->controller->Button_Plus){
					e->data[i]->buttonPlusSent = false;
				}

				if (!e->data[i]->buttonMinusSent && e->data[i]->controller->Button_Minus){
					if (e->data[i]->octave>4){
						e->data[i]->octave--;
						printf("OCTAVA %d\n", e->data[i]->octave);
					}
					e->data[i]->buttonMinusSent = true;
				}
				else if(e->data[i]->buttonMinusSent && !e->data[i]->controller->Button_Minus){
					e->data[i]->buttonMinusSent = false;
				}
			}
			
		}
	}

	//Seleccionamos los instrumentos
	for (int i =1; i <= 4; i++){
		
		//Entro en modo home si presiono el boton
		if (!e->data[i]->sel_home && e->data[i]->wiimote->Button_Home){
			e->data[i]->sel_home = true;
		}

		//Salgo de modo home si presiono A estando en modo home
		if (e->data[i]->sel_home && e->data[i]->wiimote->Button_A){
			e->data[i]->sel_home = false;
			e->data[i]->wiimote->Button_A = 0;
		}

		//Estando en modo home cambio de instrumento en direccion up
		if (!e->data[i]->sel_up && e->data[i]->sel_home  &&  e->data[i]->wiimote->Button_Up){
			e->data[i]->instrumento = ((e->data[i]->instrumento - 1 )  %  5);
			if (e->data[i]->instrumento == 0){
				e->data[i]->instrumento = 4;
			}
			e->data[i]->sel_up = true;			
		} else if (!e->data[i]->wiimote->Button_Up ){
			e->data[i]->sel_up = false;			
		} 

		//Estando en modo home cambio de instrumento en direccion down
		if (!e->data[i]->sel_down && e->data[i]->sel_home  &&  e->data[i]->wiimote->Button_Down){
			e->data[i]->instrumento = ((e->data[i]->instrumento + 1 )  %  5);
			if (e->data[i]->instrumento == 0){
				e->data[i]->instrumento = 1;
			}
			e->data[i]->sel_down = true;			
		} else if (!e->data[i]->wiimote->Button_Down){
			e->data[i]->sel_down = false;			
		} 
		// SELECCION DE TIPO DE INSTRUMENTO
		//Estando en modo home cambio de tipo de instrumento en direccion left o right
		if (!e->data[i]->sel_tipo && e->data[i]->sel_home  &&  (e->data[i]->wiimote->Button_Left || e->data[i]->wiimote->Button_Right)){
			e->data[i]->tipo_instrumento = !e->data[i]->tipo_instrumento;
			e->data[i]->sel_tipo = true;			
		} else if (!e->data[i]->wiimote->Button_Left && !e->data[i]->wiimote->Button_Right){
			e->data[i]->sel_tipo = false;			
		}
		
	}
	
}

//--------------------------------------------------------------
void testApp::draw() {
	
	// let's see something
	ofSetColor(255);
	
	//Mostramos los titulos
	wiimoteI.draw(20,20);
	wiimoteII.draw(240,20);
	wiimoteIII.draw(460,20);
	wiimoteIV.draw(680,20);

	
	//Dibujamos los instrumentos
	for (int k =0; k < 4; k++) {				
		bateria.draw(20 + k*230,100);		
		flauta.draw(20 + k*230,200);
		piano.draw(20 +k*230,300);
		maracas.draw(20 +k*230,400);

		if(e->data[k+1]->tipo_instrumento){
			flauta.draw(20 + k*230,200);
		}
		else{
			//CAMBIAR!!!
			piccolo.draw(20 + k*230,200);
		}
	}
	

	int TAMBOR = 1;
	int	FLAUTA = 2;
	int	PIANO   = 3;
	int	MARACAS = 4;
	

	for ( int i = 0; i < 4; i++) {		 
		if (e->data[i+1]->instrumento == TAMBOR){			
			bateria_selected.draw(20 + i*230,100);
		} else if (e->data[i+1]->instrumento == FLAUTA){
			if (e->data[i+1]->tipo_instrumento)
				flauta_selected.draw(20 + i*230,200);
			else 
				piccolo_selected.draw(20 + i*230,200);
		} else if (e->data[i+1]->instrumento == PIANO){
			piano_selected.draw(20 +i*230,300);
		} else if (e->data[i+1]->instrumento == MARACAS){
			maracas_selected.draw(20 +i*230,400);
		}
	}


	/*ofDrawBitmapString("Para cambiar de instrumento presione HOME", 20, 530);
	ofDrawBitmapString("Para elegir instrumento presione UP, DOWN", 20, 560);
	ofDrawBitmapString("Para confirmar instrumento presione A", 20, 590);
	*/
	ofSetColor(ofColor(255,175,0));
	camb_inst.draw(40, 530);
	sel_inst.draw(420, 530);
	conf_inst.draw(800, 530);

}

//--------------------------------------------------------------
void testApp::exit() {

	// clean up
	midiOutW1.closePort();
	midiOutW2.closePort();
	midiOutW3.closePort();
	midiOutW4.closePort();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {

	// x pos controls the pan (ctl = 10)
	pan = ofMap(x, 0, ofGetWidth(), 0, 127);
	midiOutW1.sendControlChange(channel, 10, pan);

	// y pos controls the pitch bend
	bend = ofMap(y, 0, ofGetHeight(), 0, MIDI_MAX_BEND);
	midiOutW1.sendPitchBend(channel, bend);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {	
}

//--------------------------------------------------------------
void testApp::mouseReleased() {
}
