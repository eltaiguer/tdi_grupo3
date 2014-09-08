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

   for (int j = 0; j < jointCollection.length; j=j+1){
    
    XML[] joints1 = jointCollection[j].getChildren();
    //XML[] joints2 = jointCollection[j+1].getChildren(); //obtengo los handright, handleft, etc
       
    for (int i = 0; i < joints1.length; i=i+1){       
      //println(joints1[i].getName());
      float xPosition1 = joints1[i].getChild("Position").getChild("X").getFloatContent()*600;
      float yPosition1 = joints1[i].getChild("Position").getChild("Y").getFloatContent()*600;
      float zPosition1 = joints1[i].getChild("Position").getChild("Z").getFloatContent()*600;
      
      float lineLength = zPosition1;   
      float lines = 1;
      
        //drawLine(xPosition1,yPosition1,lineLength);
      r = int (random(5,20));
      drawSplash(xPosition1, -yPosition1, r,3,i, j); 
      
      
    }   
  
}

save("splash.jpeg");

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
