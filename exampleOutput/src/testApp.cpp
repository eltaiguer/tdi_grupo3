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
	ofBackground(255);
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

	guitarra.loadImage("guitarra.png");
	guitarra_selected.loadImage("guitarra_selected.png");
	piano.loadImage("piano.png");
	piano_selected.loadImage("piano_selected.png");
	flauta.loadImage("flauta.png");
	flauta_selected.loadImage("flauta_selected.png");
	tambor.loadImage("tambor.png");
	tambor_selected.loadImage("tambor_selected.png"); 

	 
}

//--------------------------------------------------------------
void testApp::update() {
	
	// CAPTURA DE DATOS DE LOS MENSAJES OSC
	
	// hide old messages
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		if(timers[i] < ofGetElapsedTimef()){
			msg_strings[i] = "";
		}
	}

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
			e->data[i]->instrumento = ((e->data[i]->instrumento + 1 )  %  6);
			if (e->data[i]->instrumento == 0){
				e->data[i]->instrumento++;
			}
			e->data[i]->sel_right = true;
		} else if (!e->data[i]->wiimote->Button_Right){
			e->data[i]->sel_right = false;
		}
	}

	
	// FIN CAPUTRA

	// CODIGO VIEJO

	// Codigo para que envíe una nota y modificar el sonido
	//note = ofMap('W', 48, 122, 0, 127);
	////printf("nota: "+note);
	//velocity = 64;
	//midiOutW1.sendNoteOn(channel, note,  velocity);
	// Fin codigo prueba



	// hide old messages
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		if(timers[i] < ofGetElapsedTimef()){
			msg_strings[i] = "";
		}
	}

	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message


		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);

		if (m.getAddress()=="/test/Brian/wiimote"){

			note = ofMap('W', 48, 122, 0, 127);
			//printf("nota: "+note);
			velocity = 64;
			midiOutW1.sendNoteOn(2, note,  velocity);

		}

		if (m.getAddress()=="/test/Brian/nunchuk"){

			note = ofMap('W', 48, 122, 0, 127);
			//printf("nota: "+note);
			velocity = 64;
			midiOutW1.sendNoteOn(3, note,  velocity);
			
		}

		if (m.getAddress()=="/test/Brian/wiimote/viento"){
			int tecla = m.getArgAsInt32(0);
			
			if (tecla == -1){
				sonar = false;
				midiOutW1 << NoteOff(channel, note, velocity); // stream interface
			} else {
				enviarNota(tecla+48+22);

			}
			/*
			str_teclas = m.getArgAsString(0);
			
			//printf("Tecla: %s\n", str_teclas);
			if (str_teclas == "000000"){
				sonar = false;
				midiOutW1 << NoteOff(channel, note, velocity); // stream interface
			} else {
				if (str_teclas[0] == 1)
					enviarNotaViento(1,1+48+22);
				if (str_teclas[1] == 1)
					enviarNotaViento(2,2+48+22);
				if (str_teclas[2] == 1)
					enviarNotaViento(3,3+48+22);
				if (str_teclas[3] == 1)
					enviarNotaViento(4,4+48+22);
				if (str_teclas[4] == 1)
					enviarNotaViento(5,5+48+22);
				if (str_teclas[5] == 1)
					enviarNotaViento(6,6+48+22);
			}
			*/
			
			//note = ofMap(tecla+48+22, 48, 122, 0, 127);
			//midiOutW1.sendNoteOn(4, note,  velocity);
			
			
		}
	}
	
	e->data[1]->instrumento = 2; // TEST: Selecciono el instrumento

	
	if (e->data[1]->instrumento == 1){ // Batería seleccionada

		if (!hit_wiimote1_1 && e->data[1]->wiimote->Accel_Z > -1 && e->data[1]->wiimote->Button_B == 0){ // HIHAT
			note = ofMap('W', 48, 122, 0, 127);
			midiOutW1.sendNoteOn(1, note,  velocity);
			hit_wiimote1_1 = true;
		} else if (e->data[1]->wiimote->Accel_Z < -1 && e->data[1]->wiimote->Button_B == 0){
			hit_wiimote1_1 = false;
		}

		if (!hit_wiimote1_2 && e->data[1]->wiimote->Accel_Z > -1 && e->data[1]->wiimote->Button_B == 1){ // OTRO PLATILLO
			note = ofMap('W', 48, 122, 0, 127);
			midiOutW1.sendNoteOn(2, note,  velocity);
			hit_wiimote1_2 = true;
		} else if (e->data[1]->wiimote->Accel_Z < -1 && e->data[1]->wiimote->Button_B == 1){
			hit_wiimote1_2 = false;
		}

		if (!hit_wiimote1_3 && e->data[1]->nunchuck->Accel_Z > -1 && e->data[1]->nunchuck->Button_Z == 0){ // REDOBLANTE
			note = ofMap('W', 48, 122, 0, 127);
			midiOutW1.sendNoteOn(3, note,  velocity);
			hit_wiimote1_3 = true;
		} else if (e->data[1]->nunchuck->Accel_Z < -1 && e->data[1]->nunchuck->Button_Z == 0){
			hit_wiimote1_3 = false;
		}

		if (!hit_wiimote1_4 && e->data[1]->nunchuck->Accel_Z > -1 && e->data[1]->nunchuck->Button_Z == 1){ // OTRO REDOBLANTE
			note = ofMap('W', 48, 122, 0, 127);
			midiOutW1.sendNoteOn(4, note,  velocity);
			hit_wiimote1_4 = true;
		} else if (e->data[1]->nunchuck->Accel_Z < -1){
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
	ofSetColor(0);
	stringstream text;
	text << "connected to port " << midiOutW1.getPort() 
		<< " \"" << midiOutW1.getName() << "\"" << endl
		<< "is virtual?: " << midiOutW1.isVirtual() << endl << endl
		<< "sending to channel " << channel << endl << endl
		<< "current program: " << currentPgm << endl << endl
		<< "note: " << note << endl
		<< "velocity: " << velocity << endl
		<< "pan: " << pan << endl
		<< "bend: " << bend << endl
		<< "touch: " << touch << endl
		<< "polytouch: " << polytouch << endl
		<< "wiimote One: " << e->data[1]->wiimote->Button_One << endl
		<< "wiimote Two: " << e->data[1]->wiimote->Button_Two << endl
		<< "wiimote Z: " << e->data[1]->wiimote->Accel_Z << endl
		<< "nunchuk X: " << e->data[1]->nunchuck->Accel_X << endl
		<< "nunchuk Y: " << e->data[1]->nunchuck->Accel_Y << endl
		<< "nunchuk Z: " << e->data[1]->nunchuck->Accel_Z << endl
		

		
		;
	ofDrawBitmapString(text.str(), 20, 20);
	/*
	//Muestro imagenes
	/*tambor.resize(200,200);
	tambor.draw(0,0);

	piano.resize(200,200);
	piano.draw(200,0);

	flauta.resize(200,200);
	flauta.draw(600,0);

	guitarra.resize(200,200);
	guitarra.draw(800,0);*/

	//

	//Mostramos los titulos
	 
	ofDrawBitmapString("WiiMote I",20,20);
	ofDrawBitmapString("WiiMote II",200,20);
	ofDrawBitmapString("WiiMote III",380,20);
	ofDrawBitmapString("WiiMote IV",560,20);
	
	tambor.resize(50,50);
	guitarra.resize(50,50);
	
	//Dibujamos los instrumentos
	for (int k =0; k < 4; k++) {				
		tambor.draw(10 + k*180,50);		
		guitarra.draw(10 +k*180,150);
	}
	

	int TAMBOR = 1;
	int	FLAUTA = 2;
	int	MARACAS = 3;
	int	PIANO   = 4;
	int GUITARRA = 5;

	printf("instrumento seleccionado : %d\n",e->data[1]->instrumento);
	for ( int i = 1; i < 5; i++) {
		 
		if (e->data[i]->instrumento == TAMBOR){			
			//tambor_selected.draw(10,50);
			ofDrawBitmapString("Selected tambor!",500,500);
		} else if (e->data[i]->instrumento == FLAUTA){
			
		} else if (e->data[i]->instrumento == MARACAS){
		
		} else if (e->data[i]->instrumento == PIANO){
		
		} else if (e->data[i]->instrumento == GUITARRA){
			ofDrawBitmapString("Selected guitarra!",100,100);
			
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


void testApp::enviarNota(int tecla){

	if (!sonar){
		printf("nota enviada: %d\n",tecla);
		note = ofMap(tecla, 48, 122, 0, 127);
		//printf("GHJKLKGKLJnota: "+note);
		velocity = 64;
		midiOutW1.sendNoteOn(channel, note,  velocity);
		sonar = true;
	}
}

void testApp::enviarNotaViento(int canal, int tecla){

	if (!sonar){
		printf("nota enviada: %d\n",tecla);
		note = ofMap(tecla, 48, 122, 0, 127);
		//printf("GHJKLKGKLJnota: "+note);
		velocity = 64;
		midiOutW1.sendNoteOn(canal, note,  velocity);
		sonar = true;
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
	//send a note off if the key is a letter or a number
	if(isalnum(key)) {
		note = ofMap(key, 48, 122, 0, 127);
		velocity = 0;
		midiOutW1 << NoteOff(channel, note, velocity); // stream interface
		sonar = false;
	}
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
