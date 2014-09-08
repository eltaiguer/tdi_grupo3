import processing.pdf.PGraphicsPDF;

XML xml;
XML[] jointCollection;

int r;
float minRadius = 3;
float maxRadius = 40;

boolean grow = false;

float[] coloresx;
float[] coloresy;
float[] coloresz;
int i = 1;
void setup() {
  
  size(900,650);
  
  //PImage img;
  //img = loadImage("fondo.jpg");
  //img.resize(900, 650);
  
  translate(500, 400);
  background(255);
  smooth();
  
 // filter(BLUR, 6);
  xml = loadXML("movements2.xml");
  XML[] jointCollection = xml.getChildren("Joint"); //obtengo todos los joints
  
  //frameRate(10);
  /*
  coloresx= new float[jointCollection.length];
  coloresy= new float[jointCollection.length];
  coloresz= new float[jointCollection.length];
   
  for (int k = 0; k < jointCollection.length -1; k++){
    coloresx[k] = random(360);
    coloresy[k] = random(360);
    coloresz[k] = random(360);
  }
  */

  for (int j = 0; j < jointCollection.length-1; j=j+1){
    
    XML[] joints1 = jointCollection[j].getChildren();
    XML[] joints2 = jointCollection[j+1].getChildren(); //obtengo los handright, handleft, etc
       
    for (int i = 0; i < joints1.length; i=i+1){       
      //println(joints1[i].getName());
      float xPosition1 = joints1[i].getChild("Position").getChild("X").getFloatContent()*400;
      float yPosition1 = joints1[i].getChild("Position").getChild("Y").getFloatContent()*400;
      float zPosition1 = joints1[i].getChild("Position").getChild("Z").getFloatContent()*400;
      
      float xSpeed = joints2[i].getChild("Speed").getChild("X").getFloatContent()*255; 
      float ySpeed = joints2[i].getChild("Speed").getChild("Y").getFloatContent()*255;
      float zSpeed = joints2[i].getChild("Speed").getChild("Z").getFloatContent()*255;
      println(abs(xSpeed % 255)+"-"+abs(ySpeed % 255)+"-"+abs(zSpeed % 255));
      float xPosition2 = joints2[i].getChild("Position").getChild("X").getFloatContent()*400;
      float yPosition2 = joints2[i].getChild("Position").getChild("Y").getFloatContent()*400;
      float zPosition2 = joints2[i].getChild("Position").getChild("Z").getFloatContent()*400;
      
      /*
      float lineLength = zPosition1;   
      float lines = 1;
      if (i==0){
        col = color(181,157,0,100);
      }
      else if (i==1){
        col = color(0,130,164,100);
      }
      else if (i==2){
        col = color(87,35,129,100);
      }
      */
      drawLine(xPosition1,-yPosition1,zPosition1,xPosition2,-yPosition2,zPosition2,xSpeed,ySpeed,zSpeed);
      
      
    }   

  }  

save("splash.jpeg");

}

void drawLine(float xPosition1, float yPosition1, float zPosition1, float xPosition2, float yPosition2, float zPosition2, float xSpeed, float ySpeed, float zSpeed){

    //strokeWeight(abs(zPosition1)/2);
    //stroke(100,200,250);
    
    float speed = sqrt((pow(xSpeed,2) + pow(ySpeed,2) + pow(zSpeed,2))) % 6;
    strokeWeight(speed);
    stroke(abs(xPosition1 % 255),abs(yPosition1 % 255),abs(zPosition1 % 255)); 
    line(xPosition1, yPosition1,xPosition2,yPosition2);

}
// Circle splatter machine
void drawSplash(float x, float y, int radius, int level,int iJoint, int j)
{
  noStroke();
  
  //float tt = 126 * level / 6.0;
  //fill (tt, 0, 116);
  
  if (iJoint==0){
        fill(181,157,0,30);
        stroke(181,157,0,50);
      }
  else if (iJoint==1){
        fill(0,130,164,30);
        stroke(0,130,164,50);
      }
  else if (iJoint==2){
        fill(87,35,129,30);
        stroke(87,35,129,50);
      }
      
  ellipse(x, y, radius*2, radius*2);
  if (level > 1) {
    level = level - 1;
    int num = int (random(2, 5));
    for(int i=0; i<num; i++) {
      float a = random(0, TWO_PI);
      float nx = x + cos(a) * 6.0 * level;
      float ny = y + sin(a) * 6.0 * level;
      drawSplash(nx, ny, radius/2, level,i,j);
    }
  }
}
