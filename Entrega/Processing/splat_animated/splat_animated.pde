XML xml;
color col = color(181,157,0,100);
float angle=0;
int drawCount = 0;
XML[] jointCollection;
color[] palette;
int delta_min = 5;
int delta_max = 20;
ArrayList trails = new ArrayList();

int PMAX = 10;
int HMIN = 0;
int HMAX = 20;

class Trail {
  float xpos;
  float ypos;
  float xprev;
  float yprev;
  float accel = 10;
  color c;
  boolean alive = true;
  float talpha = 255;
  
  Trail(float xpos, float ypos, float ssize, color c) {
    this.xpos = xpos;
    this.ypos = ypos;  
    xprev = xpos;
    yprev = ypos;
    accel = ssize+random(-2, 2);
    this.c = c;
    talpha = alpha(c);
  }
 
  void draw() {
    color d = color(hue(c), brightness(c), saturation(c), talpha);
    stroke(d);  
    println("xprev " + xprev);
    println("yprev " + yprev);
    println("xpos " + xpos);  
    println("ypos " + ypos);    
    line(xprev, yprev, xpos, ypos);
    xprev = xpos;
    yprev = ypos;
    xpos += accel*0.2*random(-1,1);
    ypos += accel;
    accel -= 1;
    talpha -= 40;
    if(accel<0 || talpha<0) {
      alive = false;
    }    
  } 
}

class Splat {
  int splats = 1;
  int hswing = 5; // hue shift (degrees)
  color c;
  float x, y;
  
  Splat(float xpos, float ypos, float xtarget, float ytarget, color c) {
    println("xpos "+ xpos);
    println("ypos "+ ypos);
    println("xtarget "+ xtarget);
    println("ytarget "+ ytarget);

    splats = floor(abs((ytarget-ypos)/(xtarget-xpos)));
    println("splats "+splats);
    if (splats>15) {
     splats = 15;
    }
    if(splats<2) {
      splats = 2; 
    }

    this.c = c;
    x = (xpos+xtarget)/2;
    y = (ypos+ytarget)/2;
    
    println("X " + X);
    println("Y " + Y);
  }
  void draw() {
    float t = alpha(c);
    float h = hue(c);
    float s = saturation(c);
    float b = brightness(c);
    //println("I " + (-floor(splats/2)));
    //println("splats/2 "+ (splats/2));
    for(int i=-floor(splats/2); i<(splats/2); i++) {
      t -= 10;
      h += random(-hswing, hswing);
      color d = color(h, s, b, t);   
      fill(d);
      float _x = x+i*random(-2, 2);
      float _y = y+i*random(-2, 2);
      float esize = abs(i*2);
      ellipse(_x, _y, esize, esize);
      println("esize " + esize);
      if(esize>5) {
        trails.add(new Trail(_x, _y, esize, d));   
      
      }
    }
  }
}


color[] getPalatte(int max, int hue_min, int hue_max) {
  println("Creating palette");
  color[] palette = new color[max];
  for (int i=0; i<max; i++) {
    palette[i] = color(random(hue_min, hue_max), 255, 255, random(50, 230));
    println("added color: "+hex(palette[i]));
  }
  return palette;  
}

color c;

void setup() {
  
  
  size(1000, 1000);
  colorMode(HSB);
  smooth();
  noStroke();
  background(0);
  palette = getPalatte(PMAX, HMIN, HMAX);
  
  xml = loadXML("movements.xml");  
  
  println(xml.getName());
  jointCollection = xml.getChildren("Joint"); //obtengo todos los joints
  c = palette[int(random(0, PMAX))];

  frameRate(240);

  println(jointCollection.length);

}


void draw(){
  
  if (drawCount<jointCollection.length){
    println(drawCount);
  translate(500, 500);
  XML[] joints1 = jointCollection[drawCount].getChildren();
       
    for (int i = 0; i < joints1.length; i=i+1){       
      
      float xPosition1 = joints1[i].getChild("Position").getChild("X").getFloatContent()*400;
      float yPosition1 = -joints1[i].getChild("Position").getChild("Y").getFloatContent()*400;
      float zPosition1 = joints1[i].getChild("Position").getChild("Z").getFloatContent()*20;
      
      float xSpeed = joints1[i].getChild("Speed").getChild("X").getFloatContent()*400;
      float ySpeed = joints1[i].getChild("Speed").getChild("Y").getFloatContent()*400;
      float zSpeed = joints1[i].getChild("Speed").getChild("Z").getFloatContent()*400;
      
      float lineLength = sqrt(pow(xSpeed,2)+pow(ySpeed,2));   
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
      float step = random(delta_min, delta_max);
      
      
      for (int iter = 0; iter<lines; iter++){
       // drawLine(xPosition1,yPosition1,zPosition1);
       float xsig = xPosition1 + (int)random(-step,step);
       float ysig = yPosition1 + (int)random(-step,step);
        stroke(255, 30);
        //line(xPosition1, yPosition1, xsig, ysig);
        noStroke();
        Splat s = new Splat(xPosition1, yPosition1, xsig, ysig, c);
        s.draw();
       
      }
      
      println("trails "+trails.size()); 
      
  if (trails.size() >0 ) {
    for(int m=0; m<trails.size();m++) {
      Trail t = (Trail)trails.get(m);
      if(t.alive) {
        t.draw();        
      } else {
        trails.remove(t);        
      }
    }    
  }
      
    }
    
    drawCount++;
  }
}
