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
	
	hit_wiimote1_1 = false;
	hit_wiimote1_2 = false;
	hit_wiimote1_3 = false;
	hit_wiimote1_4 = false;
	hit_wiimote1_5 = false;
	
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
		int indice_remote = 0;
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

			indice_remote++;
		}
	}

	for (int i =1; i <= 4; i++){
		//Actualizo el instrumento que esta seleccionado con el right
		if (!e->data[i]->sel_right &&  e->data[i]->wiimote->Button_Right){
			e->data[i]->instrumento = ((e->data[i]->instrumento + 1 )  %  5);
			if (e->data[i]->instrumento == 0){
				e->data[i]->instrumento = 1;
			}
			e->data[i]->sel_right = true;
		} else if (!e->data[i]->wiimote->Button_Right){
			e->data[i]->sel_right = false;
		}
	}

	
	// FIN CAPUTRA

	//e->data[1]->instrumento = 1; // TEST: Selecciono el instrumento

	
	if (e->data[1]->instrumento == 1){ // Batería seleccionada


		if (!hit_wiimote1_1 && e->data[1]->wiimote->SwingDown == 1 && e->data[1]->wiimote->Button_B == 0){ // HIHAT
			note = ofMap('W', 48, 122, 0, 127);
			midiOutW1.sendNoteOn(1, note,  velocity);
			hit_wiimote1_1 = true;
			e->data[1]->wiimote->SwingDown = 0;
		} else if (e->data[1]->wiimote->SwingDown == 0 && e->data[1]->wiimote->Button_B == 0){
			hit_wiimote1_1 = false;
		}

		if (!hit_wiimote1_2 && e->data[1]->wiimote->SwingDown == 1 && e->data[1]->wiimote->Button_B == 1){ // OTRO PLATILLO
			note = ofMap('W', 48, 122, 0, 127);
			midiOutW1.sendNoteOn(2, note,  velocity);
			hit_wiimote1_2 = true;
			e->data[1]->wiimote->SwingDown = 0;
		} else if (e->data[1]->wiimote->SwingDown == 0 && e->data[1]->wiimote->Button_B == 1){
			hit_wiimote1_2 = false;
		}

		if (!hit_wiimote1_3 && e->data[1]->nunchuck->SwingDown == 1 && e->data[1]->nunchuck->Button_Z == 0){ // REDOBLANTE
			note = ofMap('W', 48, 122, 0, 127);
			midiOutW1.sendNoteOn(3, note,  velocity);
			hit_wiimote1_3 = true;
			e->data[1]->nunchuck->SwingDown = 0;
		} else if (e->data[1]->nunchuck->SwingDown == 0 && e->data[1]->nunchuck->Button_Z == 0){
			hit_wiimote1_3 = false;
		}

		if (!hit_wiimote1_4 && e->data[1]->nunchuck->SwingDown == 1 && e->data[1]->nunchuck->Button_Z == 1){ // OTRO REDOBLANTE
			note = ofMap('W', 48, 122, 0, 127);
			midiOutW1.sendNoteOn(4, note,  velocity);
			hit_wiimote1_4 = true;
			e->data[1]->nunchuck->SwingDown = 0;
		} else if (e->data[1]->nunchuck->SwingDown == 0 && e->data[1]->nunchuck->Button_Z == 1){
			hit_wiimote1_4 = false;
		}
	}

	if (e->data[1]->instrumento == 2){ // Instrumento Viento seleccionada
		
		note = ofMap('G', 48, 122, 0, 127);
		if (!hit_wiimote1_1 && e->data[1]->wiimote->Button_Up == 1){
			midiOutW2.sendNoteOn(1, note,  velocity);
			hit_wiimote1_1 = true;
		} else if (e->data[1]->wiimote->Button_Up == 0){
			hit_wiimote1_1 = false;
			midiOutW2 << NoteOff(1, note, velocity);
		}

		note = ofMap('H', 48, 122, 0, 127);
		if (!hit_wiimote1_2 && e->data[1]->wiimote->Button_Down == 1){
			midiOutW2.sendNoteOn(2, note,  velocity);
			hit_wiimote1_2 = true;
		} else if (e->data[1]->wiimote->Button_Down == 0){
			hit_wiimote1_2 = false;
			midiOutW2 << NoteOff(2, note, velocity);
		}
		
		note = ofMap('J', 48, 122, 0, 127);
		if (!hit_wiimote1_3 && e->data[1]->wiimote->Button_A == 1){
			midiOutW2.sendNoteOn(3, note,  velocity);
			hit_wiimote1_3 = true;
		} else if (e->data[1]->wiimote->Button_A == 0){
			hit_wiimote1_3 = false;
			midiOutW2 << NoteOff(3, note, velocity);

		}
		
		note = ofMap('K', 48, 122, 0, 127);
		if (!hit_wiimote1_4 && e->data[1]->wiimote->Button_One == 1){
			midiOutW2.sendNoteOn(4, note,  velocity);
			hit_wiimote1_4 = true;
		} else if (e->data[1]->wiimote->Button_One == 0){
			hit_wiimote1_4 = false;
			midiOutW2 << NoteOff(4, note, velocity);
		}

		note = ofMap('L', 48, 122, 0, 127);
		if (!hit_wiimote1_5 && e->data[1]->wiimote->Button_Two == 1){
			midiOutW2.sendNoteOn(5, note,  velocity);
			hit_wiimote1_5 = true;
		} else if (e->data[1]->wiimote->Button_Two == 0){
			hit_wiimote1_5 = false;
			midiOutW2 << NoteOff(5, note, velocity);
		}
	}

	//Seleccionamos los instrumentos
	
	
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
	}
	

	int TAMBOR = 1;
	int	FLAUTA = 2;
	int	PIANO   = 3;
	int	MARACAS = 4;
	

	for ( int i = 0; i < 4; i++) {		 
		if (e->data[i+1]->instrumento == TAMBOR){			
			bateria_selected.draw(20 + i*230,100);
		} else if (e->data[i+1]->instrumento == FLAUTA){
			flauta_selected.draw(20 + i*230,200);
		} else if (e->data[i+1]->instrumento == PIANO){
			piano_selected.draw(20 +i*230,300);
		} else if (e->data[i+1]->instrumento == MARACAS){
			maracas_selected.draw(20 +i*230,400);
		}
	}

	
	
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
