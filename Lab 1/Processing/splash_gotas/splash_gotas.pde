

XML xml;
XML[] jointCollection;

int STOP = 0;
int r;
int CANT_GOTAS = 6;
float minRadius = 3;
float maxRadius = 40;

float resto = 0;
boolean grow = false;

float[] coloresx;
float[] coloresy;
float[] coloresz;
int i = 1;
void setup() {

  size(1200, 1200);
 PImage  img = loadImage("corner.jpg");
  img.resize(1200,1200);
  background(img);
  //background(255);
  
  xml = loadXML("movements.xml");
  
}





void draw() {
 
  if (STOP == 0){
        translate(600, 600);
        XML[] jointCollection = xml.getChildren("Joint"); //obtengo todos los joints
        for (int j = 0; j < jointCollection.length  ; j=j+1) {
      
          XML[] joints1 = jointCollection[j].getChildren();
 
      
          for (int i = 0; i < joints1.length; i=i+1) {       
      
            float xPosition1 = joints1[i].getChild("Position").getChild("X").getFloatContent()*600;
            float yPosition1 = joints1[i].getChild("Position").getChild("Y").getFloatContent()*600 ;
            float zPosition1 = joints1[i].getChild("Position").getChild("Z").getFloatContent()*600;
       
            //--------------------------
            //Setemos un radio randomico
            r = int (random(5, 20));
      
            drawSplash(xPosition1, -yPosition1, r, 3, i);
                    
          }
        }
   }
   
   //-------------------------------
   //Paramos para que no dibuje mas
   STOP = 1;  
   
   //-------------------
   //Guardamos la imagen
   save("splash_gotas.jpg");   
}

 
//---------------
// Slash en gotas
void drawSplash(float x, float y, int radius, int level, int iJoint)
{

   noStroke();
  
  if (iJoint==0) {       
    fill(17,63, 140);
  } else if (iJoint==1) {    
    fill(1,164,164);    
  } else if (iJoint==2) {    
    fill(215,0,96);
  } 
  //NEW CODE
   else if (iJoint==3) {    
    fill(#9cff5c);
  } else if (iJoint==4) {    
    fill(#d95800);
  }   
  
  //NEW CODe
  
  
  
 
  //Simulo el goteo
  for (int i = 1; i < CANT_GOTAS; i++ ) {  
      ellipse(x, y, radius, radius*2);
      y = y + 10;
      x++ ;
      radius = radius - 4;
  }
    
}

