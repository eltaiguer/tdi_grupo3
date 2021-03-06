XML xml;

float h;
float r = 15;

boolean grow = false;

float minRadius = 10;
float maxRadius = 20;

void setup() {
  xml = loadXML("movimientos.xml");
  
  //String name=;
  
  println(xml.getName());
  XML[] jointCollection = xml.getChildren("HandRight");
  
  
  //println(Float.parseFloat(jointCollection[0].getChild("X").getContent()));
  
  
  size(800, 800);
  translate(400, 400);
  
  background(255);
  //smooth();
  
  colorMode( HSB, 360, 100, 100, 100 );
    
  h = random(360);

  noFill();
  stroke(0);
 
  //beginShape();
  for (int i = 0; i < jointCollection.length-1; i=i+1){
    
    float xPosition1 = jointCollection[i].getChild("X").getFloatContent()*600;
    float yPosition1 = jointCollection[i].getChild("Y").getFloatContent()*600;
    float zPosition1 = jointCollection[i].getChild("Z").getFloatContent()*600;
    float speed = jointCollection[i+1].getChild("Speed").getFloatContent();
    
    float xPosition2 = jointCollection[i+1].getChild("X").getFloatContent()*600;
    float yPosition2 = jointCollection[i+1].getChild("Y").getFloatContent()*600;
    float zPosition2 = jointCollection[i+1].getChild("Z").getFloatContent()*600;
    
    
    //println("#"+hex((int)speed,6));
    //color c = color(hex((int)speed,6));
    
    //int thickne
    if(abs(speed)>4){
    println(abs(speed));
    }
    //strokeWeight(abs(speed)/4);
    //stroke(abs(xPosition1),abs(yPosition1),abs(zPosition1)); 
    //line(xPosition1, yPosition1,xPosition2,yPosition2);
    
    fill( h, random(100), random(100), 50 );
    stroke( h, random(100), random(100), 70 );
    ellipse(xPosition1, -yPosition1, r * 2, r * 2);
    
    if ( grow ) {
        r++;
        if (r > maxRadius) {
            grow = false;
        } 
    } else {
        r--;
        if (r < minRadius) {
            grow = true;
        }
    }
    
    // float speed = jointCollection[i].getChild("Speed").getFloatContent();
    
//    if (i==0 || i== jointCollection.length-1){
//     curveVertex(xPosition1,yPosition1);
//    }   
//    curveVertex(xPosition1,yPosition1);
    
    //println("X:"+xPosition+" Y:"+yPosition+" Z:"+zPosition+" Speed:"+speed);
  }
  //endShape();
  save("dibujo.jpg");
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
