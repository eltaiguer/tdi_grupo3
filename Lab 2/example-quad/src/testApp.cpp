#include "testApp.h"

using namespace ofxCv;
using namespace cv;

//--------------------------------------------------------------
void testApp::setup(){

	// listen on the given port
	cout << "listening for osc messages on port " << PORT << "\n";
	receiver.setup(PORT);


	ofSetVerticalSync(true);
	
	// this uses depth information for occlusion
	// rather than always drawing things on top of each other
	glEnable(GL_DEPTH_TEST);
	
	// ofBox uses texture coordinates from 0-1, so you can load whatever
	// sized images you want and still use them to texture your box
	// but we have to explicitly normalize our tex coords here
	ofEnableNormalizedTexCoords();
	 
	light1.enable();
	light2.enable();
	light3.enable();
	light4.enable();
	light5.enable();
	light6.enable();
     
	 
	//Quad de la cara de frente,
	front.addVertex(ofVec3f(-100,200,100));//4	
	front.addVertex(ofVec3f(100,200,100));//5	
	front.addVertex(ofVec3f(100,200,-100));//6	
	front.addVertex(ofVec3f(-100,200,-100));//7
	
	//Agrego la textura
	front.addTexCoord(ofVec2f(0,0));
	front.addTexCoord(ofVec2f(0,1));
	front.addTexCoord(ofVec2f(1,1));
	front.addTexCoord(ofVec2f(1,0));
	
	 
	
	
	
		
	
	
	
	
	
	derecha.addVertex( ofPoint(-100,200,-100)); //7
	derecha.addVertex( ofPoint(100,200,-100));  //6
	derecha.addVertex( ofPoint(100,0,-100));  //2
	derecha.addVertex( ofPoint(-100,0,-100)); //3
	
	derecha.addTexCoord(ofVec2f(0,0));
	derecha.addTexCoord(ofVec2f(0,1));
	derecha.addTexCoord(ofVec2f(1,1));		
	derecha.addTexCoord(ofVec2f(1,0));
	

	
	
	
	izquierda.addVertex( ofPoint(-100,0,100));   //0
	izquierda.addVertex( ofPoint(100,0,100));    //1	
	izquierda.addVertex( ofPoint(100,200,100));  //5
	izquierda.addVertex( ofPoint(-100,200,100)); //4

	izquierda.addTexCoord(ofVec2f(0,0));
	izquierda.addTexCoord(ofVec2f(0,1));
	izquierda.addTexCoord(ofVec2f(1,1));
	izquierda.addTexCoord(ofVec2f(1,0));


	top.addVertex( ofPoint(-100,200,100));   //4
	top.addVertex( ofPoint(-100,200,-100)); //7
	top.addVertex( ofPoint(-100,0,-100)); //3	
	top.addVertex( ofPoint(-100,0,100));   //0
	

	top.addTexCoord(ofVec2f(0,0));
	top.addTexCoord(ofVec2f(0,1));
	top.addTexCoord(ofVec2f(1,1));
	top.addTexCoord(ofVec2f(1,0));

	
	
	bottom.addVertex( ofPoint(-100,0,100));   //0
	bottom.addVertex( ofPoint(100,0,100));    //1		
	bottom.addVertex( ofPoint(100,0,-100));  //2
	bottom.addVertex( ofPoint(-100,0,-100)); //3

	bottom.addTexCoord(ofVec2f(0,0));
	bottom.addTexCoord(ofVec2f(0,1));
	bottom.addTexCoord(ofVec2f(1,1));
	bottom.addTexCoord(ofVec2f(1,0));
	
	back.addVertex( ofPoint(100,200,100));  //5
	back.addVertex( ofPoint(100,200,-100));  //6	
	back.addVertex( ofPoint(100,0,-100));  //2	
	back.addVertex( ofPoint(100,0,100));    //1	
	

	back.addTexCoord(ofVec2f(0,0));
	back.addTexCoord(ofVec2f(0,1));
	back.addTexCoord(ofVec2f(1,1));
	back.addTexCoord(ofVec2f(1,0));
	

	//------------------------------------------
	//Dibujo la cara de frente	en el quad front
	front.addTriangle( 0, 1, 2 ); 
	front.addTriangle( 2, 3 ,0 );	
 
	 
	izquierda.addTriangle(0, 1, 2);  
	izquierda.addTriangle(2, 3, 0);
	 
	derecha.addTriangle( 0, 1, 2 );
	derecha.addTriangle( 2, 3, 0 );
	
	top.addTriangle( 0, 1, 2 );
	top.addTriangle( 2, 3, 0 );
	
	bottom.addTriangle( 0, 1, 2 );
	bottom.addTriangle( 2, 3, 0 );
	
	back.addTriangle( 0, 1, 2 );
	back.addTriangle( 2, 3, 0 );
	

	// Masculino
	img_front_comun_mas.loadImage("mas_comun.png");
	img_front_boca_abierta_mas.loadImage("mas_boca_abierta.png");
	img_front_boca_abierta_cejas_mas.loadImage("mas_boca_abierta_cejas.png");
	img_front_boca_fruncida_mas.loadImage("mas_boca_fruncida.png");
	img_front_cejas_arriba_mas.loadImage("mas_cejas_arriba.png");
	img_front_sonrisa_mas.loadImage("mas_sonrisa.png");

	img_izquierda_mas.loadImage("mas_izquierda.png");
	img_derecha_mas.loadImage("mas_derecha.png");
	img_background_mas.loadImage("mas_superior.png");

	// Femenino
	img_front_comun_fem.loadImage("fem_comun.png");
	img_front_boca_abierta_fem.loadImage("fem_boca_abierta.png");
	img_front_boca_abierta_cejas_fem.loadImage("fem_boca_abierta_cejas.png");
	img_front_boca_fruncida_fem.loadImage("fem_boca_fruncida.png");
	img_front_cejas_arriba_fem.loadImage("fem_cejas_arriba.png");
	img_front_sonrisa_fem.loadImage("fem_sonrisa.png");

	img_izquierda_fem.loadImage("fem_izquierda.png");
	img_derecha_fem.loadImage("fem_derecha.png");
	img_background_fem.loadImage("fem_superior.png");


	//EXPRESIONS
	cam.initGrabber(640, 480);
	tracker.setup();
	tracker.setRescale(.1);
	classifier.load("expressions");
	genero = true;
	exp = 4; // cara comun


	currentPitchAngle=0;
	currentYawAngle=0;
	currentRollAngle=0;
	

}

//--------------------------------------------------------------
void testApp::update(){
	cam.update();
	if(cam.isFrameNew()) {
		if(tracker.update(toCv(cam))) {
			exp = classifier.classify(tracker);
			printf("exp: %d\n",exp);
						
		}		
	}
	light1.setPosition(200, 0, 0);
	light2.setPosition(-200, 0, 0);
	light3.setPosition(0, 200, 0);
	light4.setPosition(0, -200, 0);
	light5.setPosition(0, 0, 200);
	light6.setPosition(0, 0, -200);

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
        
		if (m.getAddress()=="/head/orientationAngles/"){
			printf("PITCH %f\n",m.getArgAsFloat(0));
			printf("YAW %f\n",m.getArgAsFloat(1));
			printf("ROLL %f\n",m.getArgAsFloat(2));

			pitchAngle=m.getArgAsFloat(0);
			yawAngle=m.getArgAsFloat(1);
			rollAngle=m.getArgAsFloat(2);	

			/*if (abs(abs(currentYawAngle) - abs(yawAngle)) > DIFF){
				 */currentYawAngle=yawAngle; /*
			}*/

			/*if ((abs(currentRollAngle - rollAngle)) > DIFF){
				*/currentRollAngle=rollAngle;/*
			}
			*/
			//if (abs(abs(currentPitchAngle) - abs(pitchAngle)) > DIFF){
				currentPitchAngle=-pitchAngle;
			//}
		}
	}

}

//--------------------------------------------------------------
void testApp::draw(){
	   
	ofPushMatrix();

	tracker.draw();	
	
	
	ofTranslate( ofGetWidth()/2, ofGetHeight()/2, 0 );
	ofRotateX(90);
	ofRotateY(90);		
	
	 
	 
	 float time  = ofGetElapsedTimef();
	
	 ofRotate(currentPitchAngle, 0 , 0, 1.5 );
	 ofRotate(currentRollAngle, 0 , 1, 0 );
	 
	 ofRotate(currentYawAngle, 1.5, 0, 0 );
	  
	 ofSetColor( 255, 255 ,255 );  
    	  	 
	


	//Dibujo la cara de frente dependiendo del género seleccionado y la expresión detectada
	 if (exp == 0){
		 if (genero){
			 img_front_boca_abierta_mas.getTextureReference().bind();	
			 front.draw();
			 img_front_boca_abierta_mas.unbind();
		 } else {
			 img_front_boca_abierta_fem.getTextureReference().bind();	
			 front.draw();
			 img_front_boca_abierta_fem.unbind();
		 }
	 } else if (exp == 1){
		 if (genero){
			 img_front_boca_abierta_cejas_mas.getTextureReference().bind();	
			 front.draw();
			 img_front_boca_abierta_cejas_mas.unbind();
		 } else {
			 img_front_boca_abierta_cejas_fem.getTextureReference().bind();	
			 front.draw();
			 img_front_boca_abierta_cejas_fem.unbind();
		 }
	 } else if (exp == 2){
		 if (genero){
			 img_front_boca_fruncida_mas.getTextureReference().bind();	
			 front.draw();
			 img_front_boca_fruncida_mas.unbind();
		 } else {
			 img_front_boca_fruncida_fem.getTextureReference().bind();	
			 front.draw();
			 img_front_boca_fruncida_fem.unbind();
		 }
	 } else	if (exp == 3){
		 if (genero){
			 img_front_cejas_arriba_mas.getTextureReference().bind();	
			 front.draw();
			 img_front_cejas_arriba_mas.unbind();
		 } else {
			 img_front_cejas_arriba_fem.getTextureReference().bind();	
			 front.draw();
			 img_front_cejas_arriba_fem.unbind();
		 }
	} else if (exp == 4){
		if (genero){
			 img_front_comun_mas.getTextureReference().bind();	
			 front.draw();
			 img_front_comun_mas.unbind();
		 } else {
			 img_front_comun_fem.getTextureReference().bind();	
			 front.draw();
			 img_front_comun_fem.unbind();
		 }
	} else if (exp == 5){
		if (genero){
			 img_front_sonrisa_mas.getTextureReference().bind();	
			 front.draw();
			 img_front_sonrisa_mas.unbind();
		 } else {
			 img_front_sonrisa_fem.getTextureReference().bind();	
			 front.draw();
			 img_front_sonrisa_fem.unbind();
		 }
	}
	
	// Dibujo el resto de la cabeza dependiendo del genero
	if (genero){
		//Dibujo la cara izquierda
		img_izquierda_mas.getTextureReference().bind();	
		izquierda.draw();
		img_izquierda_mas.unbind();
	
		//Dibujo la cara derecha  
		img_derecha_mas.getTextureReference().bind();	
		derecha.draw();
		img_derecha_mas.unbind();

		img_background_mas.getTextureReference().bind();	
		//Dibujo top
		top.draw();
		//Dibujo bottom
		bottom.draw();
		//Dibujo Back
		back.draw();
		img_background_mas.unbind();
	} else {
		//Dibujo la cara izquierda
		img_izquierda_fem.getTextureReference().bind();	
		izquierda.draw();
		img_izquierda_fem.unbind();
	
		//Dibujo la cara derecha  
		img_derecha_fem.getTextureReference().bind();	
		derecha.draw();
		img_derecha_fem.unbind();

		img_background_fem.getTextureReference().bind();	
		//Dibujo top
		top.draw();
		//Dibujo bottom
		bottom.draw();
		//Dibujo Back
		back.draw();
		img_background_fem.unbind();
	}

	ofPopMatrix();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
if (key == 'c'){
		genero = !genero;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	 

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}