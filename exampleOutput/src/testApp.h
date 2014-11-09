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
#pragma once

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxOsc.h"
#include "Estructura.h"

// listen on port 12345
#define PORT 12345

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void exit();
	
	void keyPressed (int key);
	void keyReleased (int key);
	
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased();
	void enviarNota(int key);
	void enviarNotaViento(int canal, int key);
	
	ofxMidiOut midiOutW1;
	ofxMidiOut midiOutW2;
	ofxMidiOut midiOutW3;
	ofxMidiOut midiOutW4;
	int channel;
	ofxOscReceiver receiver;
	int current_msg_string;

	unsigned int currentPgm;
	int note, velocity;
	int pan, bend, touch, polytouch;
	string str_teclas;

	bool sonar;
	bool hit_wiimote1_1;
	bool hit_wiimote1_2;
	bool hit_wiimote1_3;
	bool hit_wiimote1_4;
	bool hit_wiimote1_5;

	Estructura* e;

	ofImage wiimoteI,wiimoteII,wiimoteIII,wiimoteIV,bateria,bateria_selected,piano,maracas,maracas_selected,piano_selected,guitarra,guitarra_selected,flauta,flauta_selected;
	bool muestroTambor,muestroPiano,muestroGuitarra,muestroFlauta;
};
