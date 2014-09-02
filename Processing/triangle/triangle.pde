XML xml;
color col = color(181,157,0,100);
float angle=0;


void drawLine(float x1,float y1, float z1){
  pushMatrix();
  strokeWeight(1.0);
  noFill();
  stroke(col);
  strokeWeight(10.0);
 // point(x1,-y1);
  translate(x1,-y1);
  rotate(radians(angle));
 // println("x1:"+x1+" y1:"+y1+" x2:"+(x1+sin(angle)*z1)+" y2:"+(-y1-cos(angle)*z1));
//  line(x1, -y1, x1+cos(angle)-z1,-y1 -sin(angle)*z1);
  strokeWeight(1.0);
  line(0,0,z1,0);
  popMatrix();
  angle+=1.0;
}



void setup() {
  xml = loadXML("movements2.xml");
  
  //String name=;
  
  println(xml.getName());
  XML[] jointCollection = xml.getChildren("Joint"); //obtengo todos los joints
  
  
  //println(Float.parseFloat(jointCollection[0].getChild("X").getContent()));
  
  size(800, 800);
  translate(400, 400);
  background(255);
  smooth();
 
  
  //beginShape();
  
  println(jointCollection.length);
  for (int j = 0; j < jointCollection.length; j=j+1){
    
    XML[] joints1 = jointCollection[j].getChildren();
    //XML[] joints2 = jointCollection[j+1].getChildren(); //obtengo los handright, handleft, etc
       
    for (int i = 0; i < joints1.length; i=i+1){       
      //println(joints1[i].getName());
      float xPosition1 = joints1[i].getChild("Position").getChild("X").getFloatContent()*400;
      float yPosition1 = joints1[i].getChild("Position").getChild("Y").getFloatContent()*400;
      float zPosition1 = joints1[i].getChild("Position").getChild("Z").getFloatContent()*400;
      
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
      for (int iter = 0; iter<lines; iter++){
        drawLine(xPosition1,yPosition1,lineLength);
      }
      
    }   

   

   
   
//    for (int i = 0; i < joints1.length-1; i=i+1){  
//      
//      println(joints1[i].getName());
//      float xPosition1 = joints1[i].getChild("Position").getChild("X").getFloatContent()*400;
//      float yPosition1 = joints1[i].getChild("Position").getChild("Y").getFloatContent()*400;
//      float zPosition1 = joints1[i].getChild("Position").getChild("Z").getFloatContent()*400;
//      
//      
//      float xSpeed1 = joints1[i].getChild("Speed").getChild("X").getFloatContent();
//      float ySpeed1 = joints1[i].getChild("Speed").getChild("Y").getFloatContent();
//      float zSpeed1 = joints1[i].getChild("Speed").getChild("Z").getFloatContent();
//      
//      
//      float xPosition2 = joints1[i+1].getChild("Position").getChild("X").getFloatContent()*400;
//      float yPosition2 = joints1[i+1].getChild("Position").getChild("Y").getFloatContent()*400;
//      float zPosition2 = joints1[i+1].getChild("Position").getChild("Z").getFloatContent()*400;
//      
//    
//      float xSpeed2 = joints1[i+1].getChild("Speed").getChild("X").getFloatContent();
//      float ySpeed2 = joints1[i+1].getChild("Speed").getChild("Y").getFloatContent();
//      float zSpeed2 = joints1[i+1].getChild("Speed").getChild("Z").getFloatContent();    
//           
//      if (joints1[i].getName()=="HandRight"){
//        stroke(255,27,27); //rojo
//      }
//      else if (joints1[i].getName()=="HandLeft"){
//        stroke(37,27,227); //azul
//      }
//      else if (joints1[i].getName()=="Head"){
//        stroke(18,166,40); //verde
//      }
//   
//     // stroke(abs(xPosition1),abs(yPosition1),abs(zPosition1)); 
//      line(xPosition1, -yPosition1, xPosition2, -yPosition2);
//    
//    }
  }  
}
