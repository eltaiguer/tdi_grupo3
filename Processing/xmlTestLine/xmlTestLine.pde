XML xml;

void setup() {
  xml = loadXML("movements.xml");
  
  //String name=;
  
  println(xml.getName());
  XML[] jointCollection = xml.getChildren("Joint"); //obtengo todos los joints
  
  
  //println(Float.parseFloat(jointCollection[0].getChild("X").getContent()));
  
  size(800, 800);
  translate(400, 400);
  background(255);
  //smooth();

  noFill();
  //beginShape();
  
  println(jointCollection.length);
  for (int j = 0; j < jointCollection.length-1; j=j+1){
    
    XML[] joints1 = jointCollection[j].getChildren();
    XML[] joints2 = jointCollection[j+1].getChildren(); //obtengo los handright, handleft, etc
   // println(j);
    for (int i = 0; i < joints1.length; i=i+1){       
      println(joints1[i].getName());
      float xPosition1 = joints1[i].getChild("Position").getChild("X").getFloatContent()*400;
      float yPosition1 = joints1[i].getChild("Position").getChild("Y").getFloatContent()*400;
      float zPosition1 = joints1[i].getChild("Position").getChild("Z").getFloatContent()*400;
      
      
      float xSpeed1 = joints1[i].getChild("Speed").getChild("X").getFloatContent();
      float ySpeed1 = joints1[i].getChild("Speed").getChild("Y").getFloatContent();
      float zSpeed1 = joints1[i].getChild("Speed").getChild("Z").getFloatContent();
      
      
      float xPosition2 = joints2[i].getChild("Position").getChild("X").getFloatContent()*400;
      float yPosition2 = joints2[i].getChild("Position").getChild("Y").getFloatContent()*400;
      float zPosition2 = joints2[i].getChild("Position").getChild("Z").getFloatContent()*400;
      
    
      float xSpeed2 = joints2[i].getChild("Speed").getChild("X").getFloatContent();
      float ySpeed2 = joints2[i].getChild("Speed").getChild("Y").getFloatContent();
      float zSpeed2 = joints2[i].getChild("Speed").getChild("Z").getFloatContent();    
           
      if (joints1[i].getName()=="HandRight"){
        stroke(255,27,27); //rojo
      }
      else if (joints1[i].getName()=="HandLeft"){
        stroke(37,27,227); //azul
      }
      else if (joints1[i].getName()=="Head"){
        stroke(18,166,40); //verde
      }
   
     // stroke(abs(xPosition1),abs(yPosition1),abs(zPosition1)); 
      line(xPosition1, -yPosition1,xPosition2,-yPosition2);
    
    }
    // float speed = jointCollection[i].getChild("Speed").getFloatContent();
    
//    if (i==0 || i== jointCollection.length-1){
//     curveVertex(xPosition1,yPosition1);
//    }   
//    curveVertex(xPosition1,yPosition1);
    
    //println("X:"+xPosition+" Y:"+yPosition+" Z:"+zPosition+" Speed:"+speed);
  }
  
  
  //endShape();
}



//void setup()
//{
//  int[ ] coords = {
//    40, 40, 80, 60, 100, 100, 60, 120, 50, 150
//  };
//  int i;
//  
//  size(1000, 800);
//  background(255);
//  smooth();
//
//  noFill();
//  stroke(0);
//  beginShape();
//  for (i = 0; i < coords.length; i += 2)
//  {
//    if (i==0 || i== coords.length-2){
//      curveVertex(coords[i],coords[i+1]);
//    }
//    
//    curveVertex(coords[i],coords[i+1]);
//  }
//  
//  
////  curveVertex(40, 40); // the first control point
////  curveVertex(40, 40); // is also the start point of curve
////  curveVertex(80, 60);
////  curveVertex(100, 100);
////  curveVertex(60, 120);
////  curveVertex(50, 150); // the last point of curve
////  curveVertex(50, 150); // is also the last control point
//  endShape();
//  
//  // use the array to keep the code shorter;
//  // you already know how to draw ellipses!
//  fill(255, 0, 0);
//  noStroke();
//  for (i = 0; i < coords.length; i += 2)
//  {
//    ellipse(coords[i], coords[i + 1], 3, 3);
//  }
//  
//}
