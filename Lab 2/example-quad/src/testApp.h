#pragma once

#include "ofMain.h"
#include "of3dPrimitives.h"
#include "ofxFaceTracker.h"
#include "ofxOsc.h"

// listen on port 12345
#define PORT 12345
#define NUM_MSG_STRINGS 20
#define DIFF 1

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	 
		// EXPRESIONS
		ofVideoGrabber cam;
		ofxFaceTracker tracker;
		ExpressionClassifier classifier;
		int exp;
		int img_dim;

		bool genero;
		// FIN EXPRESIONS


		ofMesh quad;
		ofMesh  front;
		ofMesh  izquierda;
		ofMesh  derecha;
		ofMesh  top;
		ofMesh  bottom;
		ofMesh  back;
		ofImage img_front_comun_mas, img_front_boca_abierta_mas, img_front_boca_abierta_cejas_mas, img_front_boca_fruncida_mas, img_front_cejas_arriba_mas, img_front_sonrisa_mas;
		ofImage img_izquierda_mas, img_derecha_mas, img_background_mas;
		ofImage img_front_comun_fem, img_front_boca_abierta_fem, img_front_boca_abierta_cejas_fem, img_front_boca_fruncida_fem,	img_front_cejas_arriba_fem,	img_front_sonrisa_fem; 
		ofImage img_izquierda_fem, img_derecha_fem, img_background_fem;
		ofTexture text;
		float factor; 
		float scale; 
		ofLight light1;
		ofLight light2;
		ofLight light3;
		ofLight light4;
		ofLight light5;
		ofLight light6;
		
		ofxOscReceiver receiver;
		int current_msg_string;
		string msg_strings[NUM_MSG_STRINGS];
		float timers[NUM_MSG_STRINGS];

		float pitchAngle;
		float rollAngle;
		float yawAngle;

		float currentPitchAngle;
		float currentRollAngle;
		float currentYawAngle;

		
		
};
