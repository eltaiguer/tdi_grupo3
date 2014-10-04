XML xml;
color[] colors = {color(218,151,0,100), color(102,45,145,100), color(27,20,100,100), color(0,169,157,100),  color(217,88,0,100)};
color col = color(181,157,0,100);
float angle=0;


void drawLine(float x1,float y1, float z1){
  pushMatrix();
  noFill();
  stroke(col);
  strokeWeight(10.0);
  //point(x1,-y1);
  translate(x1,-y1);
  rotate(radians(angle));
  strokeWeight(0.5);
  line(0,0,z1,0);
  popMatrix();
  angle+=1.0;
}



void setup() {
  xml = loadXML("movements.xml");  
  
  println(xml.getName());
  XML[] jointCollection = xml.getChildren("Joint"); //obtengo todos los joints
  
  size(800, 800);
  translate(400, 400);
  background(255);
  smooth();
 
  
  //beginShape();
  
  println(jointCollection.length);
  for (int j = 0; j < jointCollection.length; j=j+1){
    
    XML[] joints1 = jointCollection[j].getChildren();
       
    for (int i = 0; i < joints1.length; i=i+1){       
      //println(joints1[i].getName());
      float xPosition1 = joints1[i].getChild("Position").getChild("X").getFloatContent()*400;
      float yPosition1 = joints1[i].getChild("Position").getChild("Y").getFloatContent()*400;
      float zPosition1 = joints1[i].getChild("Position").getChild("Z").getFloatContent()*100;
      
      float lineLength = zPosition1;   
      float lines = 1;
      
      col=colors[i];
      
      for (int iter = 0; iter<lines; iter++){
        drawLine(xPosition1,yPosition1,lineLength);
      }
      
    }   

  }  
}
