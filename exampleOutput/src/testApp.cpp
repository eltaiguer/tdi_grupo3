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
	velocity = 0;
	pan = 0;
	bend = 0;
	touch = 0;
	polytouch = 0;

	sonar = false;

	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);

	e = new Estructura();

	guitarra.loadImage("guitarra.png");
	piano.loadImage("piano.png");
	flauta.loadImage("flauta.png");
	tambor.loadImage("tambor.png");

	muestroPiano    = false;
	muestroGuitarra = false;
	muestroTambor   = false;
	muestroFlauta   = false;

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
				e->data[indice_remote]->nunchuck->Button_X = m.getArgAsInt32(2);
				e->data[indice_remote]->nunchuck->Button_Y = m.getArgAsInt32(3);
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
	
	
	
}

//--------------------------------------------------------------
void testApp::draw() {
	
	// let's see something
	ofSetColor(0);
	stringstream text;
	/*text << "connected to port " << midiOutW1.getPort() 
		<< " \"" << midiOutW1.getName() << "\"" << endl
		<< "is virtual?: " << midiOutW1.isVirtual() << endl << endl
		<< "sending to channel " << channel << endl << endl
		<< "current program: " << currentPgm << endl << endl
		<< "note: " << note << endl
		<< "velocity: " << velocity << endl
		<< "pan: " << pan << endl
		<< "bend: " << bend << endl
		<< "touch: " << touch << endl
		<< "polytouch: " << polytouch;
	ofDrawBitmapString(text.str(), 20, 20);*/
	
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

	int tope = 4;
	for ( int i = 1; i < tope; i++) {
		if (e->data[i]->wiimote->Button_A) {		
			tambor.resize(50,50);
			tambor.draw(10,50);
		}

		if (e->data[i]->wiimote->Button_One) {
			guitarra.resize(50,50);
			guitarra.draw(10,150);
		}
		//break;
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

	enviarNota(key);
	



	//// send a note on if the key is a letter or a number
	//if(isalpha((unsigned char) key)) {

	//	// scale the ascii values to midi velocity range 0-127
	//	// see an ascii table: http://www.asciitable.com/
	//	note = ofMap(key, 48, 122, 0, 127);

	//	velocity = 64;
	//	midiOutW1.sendNoteOn(channel, note,  velocity);
	//	printf("envio nota: %d\n", key);
	//}

	

	if (key == OF_KEY_PAGE_UP){
		note = ofMap(key, 48, 122, 0, 127);
		midiOutW1.sendNoteOn(channel, note,  velocity);
		// Envio nota para subir el volumen
	}

	if (key == OF_KEY_PAGE_DOWN){
		// Envio nota para bajar el volumen
		note = ofMap(key, 48, 122, 0, 127);
		midiOutW1.sendNoteOn(channel, note,  velocity);
	}

	// Utilizo los numeros para cambiar de canal
	if (isdigit((unsigned char) key)){
		printf("%d",key-48);
		channel = key-48;

	}
}

//--------------------------------------------------------------
//void testApp::keyReleased(int key) {
//	
//	switch(key) {
//	
//		// send pgm change on arrow keys
//		case OF_KEY_UP:
//			currentPgm = (int) ofClamp(currentPgm+1, 0, 127);
//			midiOutW1.sendProgramChange(channel, currentPgm);
//			break;
//		case OF_KEY_DOWN:
//			currentPgm = (int) ofClamp(currentPgm-1, 0, 127);
//			midiOutW1 << ProgramChange(channel, currentPgm); // stream interface
//			break;
//
//		// aftertouch
//		case '[':
//			touch = 64;
//			midiOutW1.sendAftertouch(channel, touch);
//			break;
//		case ']':
//			touch = 127;
//			midiOutW1 << Aftertouch(channel, touch); // stream interface
//			break;
//
//		// poly aftertouch
//		case '<':
//			polytouch = 64;
//			midiOutW1.sendPolyAftertouch(channel, 64, polytouch);
//			break;
//		case '>':
//			polytouch = 127;
//			midiOutW1 << PolyAftertouch(channel, 64, polytouch); // stream interface
//			break;
//			
//		// sysex using raw bytes (use shift + s)
//		case 'S': {
//			// send a pitch change to Part 1 of a MULTI on an Akai sampler
//			// from http://troywoodfield.tripod.com/sysex.html
//			//
//			// do you have an S2000 to try?
//			//
//			// note: this is probably not as efficient as the next two methods
//			//       since it sends only one byte at a time, instead of all
//			//       at once
//			//
//			midiOutW1.sendMidiByte(MIDI_SYSEX);
//			midiOutW1.sendMidiByte(0x47);	// akai manufacturer code
//			midiOutW1.sendMidiByte(0x00); // channel 0
//			midiOutW1.sendMidiByte(0x42); // MULTI
//			midiOutW1.sendMidiByte(0x48); // using an Akai S2000
//			midiOutW1.sendMidiByte(0x00); // Part 1
//			midiOutW1.sendMidiByte(0x00);	// transpose
//			midiOutW1.sendMidiByte(0x01); // Access Multi Parts
//			midiOutW1.sendMidiByte(0x4B); // offset
//			midiOutW1.sendMidiByte(0x00);	// offset
//			midiOutW1.sendMidiByte(0x01); // Field size = 1
//			midiOutW1.sendMidiByte(0x00); // Field size = 1
//			midiOutW1.sendMidiByte(0x04); // pitch value = 4
//			midiOutW1.sendMidiByte(0x00); // offset
//			midiOutW1.sendMidiByte(MIDI_SYSEX_END);
//			
//			// send again using a vector
//			//
//			// sends all bytes within one message
//			//
//			vector<unsigned char> sysexMsg;
//			sysexMsg.push_back(MIDI_SYSEX);
//			sysexMsg.push_back(0x47);
//			sysexMsg.push_back(0x00);
//			sysexMsg.push_back(0x42);
//			sysexMsg.push_back(0x48);
//			sysexMsg.push_back(0x00);
//			sysexMsg.push_back(0x00);
//			sysexMsg.push_back(0x01);
//			sysexMsg.push_back(0x4B);
//			sysexMsg.push_back(0x00);
//			sysexMsg.push_back(0x01);
//			sysexMsg.push_back(0x00);
//			sysexMsg.push_back(0x04);
//			sysexMsg.push_back(0x00);
//			sysexMsg.push_back(MIDI_SYSEX_END);
//			midiOutW1.sendMidiBytes(sysexMsg);
//			
//			// send again with the byte stream interface
//			//
//			// builds the message, then sends it on FinishMidi()
//			//
//			midiOutW1 << StartMidi() << MIDI_SYSEX
//					<< 0x47 << 0x00 << 0x42 << 0x48 << 0x00 << 0x00 << 0x01
//					<< 0x4B << 0x00 << 0x01 << 0x00 << 0x04 << 0x00
//					<< MIDI_SYSEX_END << FinishMidi();
//			break;
//		}
//		
//		// print the port list
//		case '?':
//			midiOutW1.listPorts();
//			break;
//		
//		// note off using raw bytes
//		case ' ':	
//			// send with the byte stream interface, noteoff for note 60
//			midiOutW1 << StartMidi() << 0x80 << 0x3C << 0x40 << FinishMidi();
//			break;
//
//		default:
//    
//			// send a note off if the key is a letter or a number
//			if(isalnum(key)) {
//				note = ofMap(key, 48, 122, 0, 127);
//				velocity = 0;
//				midiOutW1 << NoteOff(channel, note, velocity); // stream interface
//			}
//			break;
//	}
//}

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
