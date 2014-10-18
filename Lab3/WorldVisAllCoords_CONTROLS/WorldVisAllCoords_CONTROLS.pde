/* @pjs preload="WorldVisAllCoords/data/w.png"; */

import controlP5.*;

final float MIN_TO_DEG= 1/60f;     
final float SEG_TO_DEG= 1/3600f;
final float SCALE_F= 8e-6;

class DataHolderCapituloClasePais {  
  String 
  CLASE,CAPITULO,PAIS,
  NAME, COUNTRY;
  int 
  VALUE, INDEX;
  float 
  LATITUDE, LONGITUDE;
  PVector 
  START, END, STARTURU, ENDURU;
  PVector
  CONT, CONTVECTOR, CONT1, CONTVECTOR1, CONT2, CONTVECTOR2;
  boolean 
  hovered=false;
  
  
  DataHolderCapituloClasePais (int i) {
    INDEX     = i+1;  
    CAPITULO   = t2.getString (i+1,0);
    CLASE   = t2.getString (i+1,1);
    PAIS   = t2.getString (i+1,2);
  }
  
   
  
  void setHoveredTo (boolean booleanToSet){
    hovered= booleanToSet;
  }

   
   
}

public class Pais{
  public String NOMBRE_PAIS;
  
  Pais(String nombre) {
      NOMBRE_PAIS = nombre;
  }
}

public class Clase{
  public String NOMBRE_CLASE;
  public ArrayList<Pais> PAISES;
  
  Clase (String nombre) {
      NOMBRE_CLASE = nombre;
      PAISES = new ArrayList<Pais>();

  }
  
  void addPais(Pais p) {
    PAISES.add(p);
  }
  
  Pais find(String nombre) {
    for (int i = 0 ; i < PAISES.size(); i++){
          if (nombre.equals((PAISES.get(i)).NOMBRE_PAIS)){
             return PAISES.get(i);
          }
      }
    return null;    
  }
}

public class Capitulo {
  public String NOMBRE_CAPITULO;
  public ArrayList<Clase> CLASES;
  
    Capitulo(String nombre) {
      NOMBRE_CAPITULO = nombre;
      CLASES  = new ArrayList<Clase>();
    }
  
    void AddClase(Clase c) {
      CLASES.add(c);
    }
    
    Clase find(String nombre){
    
      ////println("find en capitulo");
      ////println(CLASES.size());
      for (int i = 0 ; i < CLASES.size(); i++){
          if (nombre.equals(CLASES.get(i).NOMBRE_CLASE)){
             return CLASES.get(i);
          }
      }
   
   return null;
    }
}  

public class Estructura {
   public ArrayList<Capitulo> CAPITULOS;
   
   Estructura(){
     CAPITULOS = new ArrayList<Capitulo>();  
   }
   Capitulo find(String nombre){
     ////println(" find en capitulos");
     ////println("#" + nombre + "#");
      for (int i = 0 ; i < CAPITULOS.size(); i++){
          ////println("@" + ((CAPITULOS.get(i)).NOMBRE_CAPITULO) + "@");
          if (nombre.equals((CAPITULOS.get(i)).NOMBRE_CAPITULO)){
            ////println("encontre el capitulo"); 
            return CAPITULOS.get(i);
          }
          
      }
      return null;
   }
   
   void addCapitulo(Capitulo c) {
     CAPITULOS.add(c);
   }
   
}



class DataHolder {  
  String 
  NAME, COUNTRY;
  int 
  VALUE, INDEX;
  float 
  LATITUDE, LONGITUDE;
  PVector 
  START, END, STARTURU, ENDURU;
  PVector
  CONT, CONTVECTOR, CONT1, CONTVECTOR1, CONT2, CONTVECTOR2;
  boolean 
  hovered=false;
  boolean
  MOSTRAR;
  
  DataHolder (int i){
    INDEX     = i+1;  
    COUNTRY   = t.getString (i+1,0);
    LATITUDE  = parseCoord  (t.getString(i+1,1));
    LONGITUDE = parseCoord  (t.getString(i+1,2));
    START     = polarToCartesian (LATITUDE,LONGITUDE,-1);
    STARTURU  = polarToCartesian (parseCoord("34 50 S"),parseCoord("56 8 W"),-1);
    ENDURU    = polarToCartesian (parseCoord("34 50 S"),parseCoord("56 8 W"),50);
    END       = polarToCartesian (LATITUDE,LONGITUDE,50);
    MOSTRAR   = false;
       
    CONTVECTOR =  puntoMedio(LATITUDE, LONGITUDE, parseCoord("34 50 S"),parseCoord("56 8 W"));
    CONTVECTOR =  puntoMedio(LATITUDE, LONGITUDE, parseCoord("34 50 S"),parseCoord("56 8 W"));
    CONTVECTOR =  puntoMedio(LATITUDE, LONGITUDE, parseCoord("34 50 S"),parseCoord("56 8 W"));
    CONTVECTOR1 = puntoMedio(LATITUDE, LONGITUDE, CONTVECTOR.x, CONTVECTOR.y);
    CONTVECTOR2 = puntoMedio(CONTVECTOR.x, CONTVECTOR.y, parseCoord("34 50 S"),parseCoord("56 8 W"));
    
    CONT = polarToCartesian(CONTVECTOR.x, CONTVECTOR.y, 100);
    CONT1 = polarToCartesian(CONTVECTOR1.x, CONTVECTOR1.y, 100);
    CONT2 = polarToCartesian(CONTVECTOR2.x, CONTVECTOR2.y, 100);
  }

  PVector puntoMedio (float LAT1, float LONG1, float LAT2, float LONG2){
    
    double Bx = Math.cos(LAT2) * Math.cos(LONG2-LONG1);
    double By = Math.cos(LAT2) * Math.sin(LONG2-LONG1);
    double LAT3 = Math.atan2(Math.sin(LAT1) + Math.sin(LAT2),
                      Math.sqrt( (Math.cos(LAT1)+Bx)*(Math.cos(LAT1)+Bx) + By*By ) );
    double LONG3 = LONG1 + Math.atan2(By, Math.cos(LAT1) + Bx); 
    
    return new PVector((float)LAT3, (float)LONG3, (float)350);
  }
  
  //A custom method to parse GeoNames´s database coordinates 
  float parseCoord(String a){
    //Split the string using whitespace characters as delimiters.
    String[] c= split(a," ");
    //Match a regular expresion in order to exclude any symbol
   //for (int i=0;i<c.length;i++) c[i]= match(c[i],"\\d++")[0]; 
   
    //Transform the coordinates into a single floating value
    float coord= int(c[0]) + int(c[1])*MIN_TO_DEG + 0*SEG_TO_DEG; 
    ////println(c[0]+","+c[1]);
    //And check orientation: if first char is 'S' or 'W' set a negative sign
    char orientation=c[2].charAt(0);
    ////println(orientation);
    if  (orientation==87 || orientation==83) coord*=-DEG_TO_RAD; else coord*=DEG_TO_RAD;
    return coord;  
  }

  void setHoveredTo (boolean booleanToSet){
    hovered= booleanToSet;
  }

   // returns a Pvector representing the lat, long and altitude in 3d space
   // altitude is relative to the surface of the globe
  PVector polarToCartesian(float lat, float lng, float hght) {
    float shift_lat = lat + HALF_PI;                     // shift the lat by 90 degrees
    float tot_hght  = w.globeRadius + hght;
    
    float x = -tot_hght * sin(shift_lat) * cos(lng);     // -1 needed cause of the orientation of the processing 3d cartesian coordinate system
    float z =  tot_hght * sin(shift_lat) * sin(lng);
    float y =  tot_hght * cos(shift_lat);
    return  new PVector(x,y,z);
  }
  
  void render(PGraphics canvas, boolean buffered){    
    canvas.strokeWeight(LINES_WEIGHT);
    if      (buffered) {canvas.strokeWeight(BUFF_LINES_W); canvas.stroke(INDEX);} 
    else if  (hovered) canvas.stroke(HOVER_COL); 
    else               canvas.stroke(DATA_COL);
  
    //canvas.stroke(0,255,0);
    canvas.noFill();
    canvas.strokeWeight(LINES_WEIGHT);
    canvas.bezier(START.x,START.y,START.z,END.x,END.y,END.z,CONT1.x,CONT1.y,CONT1.z,CONT.x,CONT.y,CONT.z);
    canvas.bezier(CONT.x,CONT.y,CONT.z, CONT2.x,CONT2.y,CONT2.z,ENDURU.x,ENDURU.y,ENDURU.z, STARTURU.x,STARTURU.y,STARTURU.z);
  
  }
      
}



//A generic class to render textured spheres. The code is extracted from Flink Labs´s work. /////////////////////////
//At the beginning I started with the "Textured Sphere" example on the GL section of processing examples... /////////
//Bad election... that code isn´t a good base indeed! It´s all messed up...//////////////////////////////////////////
//I´ve slightly improved performance, removing unnecessary operations from the render() method.//////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Globe {
  
  PImage 
  txtMap;
  int 
  globeRadius; 
  float 
  rWRatio, 
  rHRatio,
  ROTATION_FACTOR=.01*DEG_TO_RAD;
  PVector   
  rotation, 
  rotSpeed;
  
  // Textured sphere implementation 
  float[][] 
  texturedSphereX,
  texturedSphereY, 
  texturedSphereZ, 
  texturedSphereU, 
  texturedSphereV; 
  int   
  texturedSphereDetail;

  ////////////////////////////////////////////////////////////////////////CONSTRUCTOR
   
  Globe(int _radius, int _sphereDetail, String _mapFilename) {
    globeRadius = _radius;
    txtMap = loadImage(_mapFilename);
    rWRatio= txtMap.width/globeRadius;
    rHRatio= txtMap.height/globeRadius;
    setTexturedSphereDetail(_sphereDetail); 
    rotation= new PVector(0,HALF_PI);
    rotSpeed= new PVector(0,0);
  }
  
  ////////////////////////////////////////////////////////////////////////////METHODS
  
  void setTexturedSphereDetail(int detail) {   //Set the detail level for textured spheres, constructing the underlying vertex and uv map data  
    
    if (detail == texturedSphereDetail) return; 
    
    texturedSphereDetail = detail; 
    float step = PI / detail; 
    float ustep = .5 / detail; 
    float vstep = 1. / detail; 
    int d1= detail+1;
    int d2= detail*2 +1;

    texturedSphereX = new float[d1][d2]; 
    texturedSphereY = new float[d1][d2]; 
    texturedSphereZ = new float[d1][d2]; 
    texturedSphereU = new float[d1][d2]; 
    texturedSphereV = new float[d1][d2]; 

    for (int i = 0; i <= detail; i++) { 
      float theta = step * i; 
      float y = cos(theta); 
      float sin_theta = sin(theta); 
      float v = 1.0f - vstep * i; 

      for (int j = 0; j <= 2 * detail; j++) { 
        float phi = step * j; 
        float x = sin_theta * cos(phi); 
        float z = sin_theta * sin(phi); 
        float u = 1.0f - ustep * j; 

        texturedSphereX[i][j] = x * globeRadius; 
        texturedSphereY[i][j] = y * globeRadius; 
        texturedSphereZ[i][j] = z * globeRadius; 
        texturedSphereU[i][j] = u * txtMap.width; 
        texturedSphereV[i][j] = v * txtMap.height; 
      }   
    } 
  }

  void render() {  // draw the sphere
    noStroke();
    int nexti, t2= 2*texturedSphereDetail;
    //
    for (int i = 0; i < texturedSphereDetail; i=nexti) { 
      nexti = i + 1;   
      beginShape(QUAD_STRIP); 
      texture(txtMap); 
        for (int j=0 ; j<=t2 ; j++) {         
          float u  = texturedSphereU[i][j]; 
          float x1 = texturedSphereX[i][j]; 
          float y1 = texturedSphereY[i][j]; 
          float z1 = texturedSphereZ[i][j]; 
          float v1 = texturedSphereV[i][j]; 
          float x2 = texturedSphereX[nexti][j]; 
          float y2 = texturedSphereY[nexti][j]; 
          float z2 = texturedSphereZ[nexti][j]; 
          float v2 = texturedSphereV[nexti][j]; 
          vertex(x1, y1, z1, u, v1); 
          vertex(x2, y2, z2, u, v2); 
        }   
      endShape(); 
    }
  }
  
  void addRotation(int mX,int mY,int pmX,int pmY){
    rotSpeed.x += (pmY-mY)* ROTATION_FACTOR;
    rotSpeed.y -= (pmX-mX)* ROTATION_FACTOR;     
  }
 
  void update(){
    rotation.add  (rotSpeed);
    rotSpeed.mult (.95);  
  }
}



//Table///////////////////////////////almost classic class, extracted from Ben Fry's "Visualizing Data"
//////////////////////////////////////////////////////////////////////////////////////////////////////

class Table {
  String[][] data;
  int numRows, numCols;

  //CONSTRUCTOR
  Table(String nombre) {   
    String[] filas = loadStrings(nombre); 
    numRows = filas.length;
    ////println("filas: "+numRows);
    data = new String[numRows][];
    for (int i = 0; i < filas.length; i++) {
      if (trim(filas[i]).length() == 0) {
        continue;
      }   
      if (filas[i].startsWith("#")) {      //startsWith() doesn't work on processingjs
        continue;
      }   
      data[i] = split(filas[i],",");       //dont use TAB on processingjs
    }       
    numCols=data[0].length;
  }

  //METHODS

  //Returns number of rows
  int getNumRows() { return numRows; }

  //Return number of cols
  int getNumCols() { return numCols; }

  //Returns name of a row, specified by index
  String getRowName(int rowIndex) { return getString(rowIndex,0); }

  //Returns value as String | be careful with method overloading using processingjs
  //String getString(String rowName, int col) { return getString(getRowIndex(rowName),col); }
  String getString(int rowIndex, int colIndex) { return data[rowIndex][colIndex]; }

  //Returns value as Int | be careful, bla, bla..
  //int getInt(String rowName, int col) { return parseInt(getString(rowName,col));}   
  int getInt(int rowIndex, int colIndex) { return parseInt(getString(rowIndex,colIndex)); }

  //Returns value as Float | be careful, bla, bla..
  //float getFloat(String rowName, int col) { return parseFloat(getString(rowName,col)); }
  float getFloat(int rowIndex, int colIndex) { return parseFloat(getString(rowIndex,colIndex)); }

  //Find file by its name and returns -1 in case of failure
  int getRowIndex(String name) {
    for (int i = 0; i < numRows; i++) {
      if (data[i][0].equals(name)) {
        return i;
      }
    }
    //println("I didn't found any row called '"+ name+"!'");
    return -1;
  }

  //Returns the sum of all the values in a row, specified by index
  int rowSum (int index) {
    int sum=0;
    for (int i=1;i<numCols;i++) {
      sum+=getInt(index,i);
    }
    return sum;
  }
  
  //Returns the sum of all the values in a column, specified by index
  int colSum (int index) {
    int sum=0;
    for (int i=1;i<numRows;i++) {
      sum+=getInt(i,index);
    } 
    return sum;
  }
  
  //Returns the row with maximum value sum
  int maxRowSum() { 
    int maxSum=0;  
    for (int i=1; i<numRows; i++) {
      if (rowSum(i)>=maxSum) {
        maxSum=rowSum(i);
      }
    }
    return maxSum;
  }
  
  //Returns the total sum of all the values in the table
  int totalSum() {
    int sum=0;  
    for (int i=1; i<numRows; i++) {
      sum+=rowSum(i);
    } 
    return sum;
  }
} 



/* OpenProcessing Tweak of *@*http://www.openprocessing.org/sketch/50864*@* */
/* !do not delete the line above, required for linking your tweak if you upload again */
//WorldVis///////////////////////////////////////////////////////////////////////////////
//A generic tool to display some cuantitative data onto Earth surface////////////////////
//Inspired by Flink Labs visualization on climate change:////////////////////////////////
//www.flinklabs.com/projects/climatedata/////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
//This example display most populated metropolis (on this world :-)//////////////////////
//Data: cityPopulation + geoNames//////////////////////////////////////////////////////// 
//http://es.wikipedia.org/wiki/Anexo:Aglomeraciones_urbanas_m%C3%A1s_pobladas_del_mundo//
/////////////////////////////////////////////////////////////////////////////////////////
//Custom image based on work from [http://commons.wikimedia.org/wiki/User:Thesevenseas]//
//Font-family: Lato // Author: Lukasz Dziedzic///////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////Ale González · 60rpm.tv/i
/////////////////////////////////////////////////////////////////////////////Pubic Domain
/////////////////////////////////////////////////////////////////////////////////////////

int 
X,Y;
final int
TEXT_COL      = 0xaa000000,
DATA_COL      = 0x99ff0000,
HOVER_COL     = 0xffffaa00,
WORLD_TINT    = 0xffffffff,
LINES_WEIGHT  = 3,
BUFF_LINES_W  = 6;
float 
a,b;
PGraphics 
bg, 
hover;
PFont 
h0,h1,h2,h3;
//
Globe w;
Table t;
DataHolder[] data;
////////////////////////////////////////////////////////////////////////////////////////

//@@@ NEW CODE
Table t2;
 
DataHolderCapituloClasePais[] dataCapituloClasePais;
ControlP5 cp5;

CheckBox checkbox;

int myColorBackground;

HashMap<Integer,String> nombres;
Estructura e; 


void setup(){
   //Buffers
  size(1100,690,P3D); 
  bg= createGraphics(width,height, JAVA2D);    //Buffer for storing the background
  hover=  createGraphics(width,height,P3D); //Color picking buffer
   //Fonts
  //h1= loadFont("WorldVisAllCoords/data/Lato-Regular-24.vlw");
  h1= loadFont("Lato-Regular-24.vlw");
  //h2= loadFont("WorldVisAllCoords/data/Lato-Light-24.vlw");
  h2= loadFont("Lato-Light-24.vlw");
   //General settings
  X=  width/2+100;
  Y= height/2;
  createBackground (bg,X,Y,.1);
  frameRate(30);
  cursor(CROSS);
  textMode(SCREEN);
   //Objects
  //w= new Globe(250,24,"WorldVisAllCoords/data/w.png");
  w= new Globe(200,24,"w.png");
  //t= new Table("WorldVisAllCoords/data/coords2.csv");
  t= new Table("coords2.csv");
  ////println("lineas"+t.getNumRows());
  data= new DataHolder[t.getNumRows()-1];
  for(int i=0;i<data.length;i++){
    data[i]= new DataHolder(i);  
  }
  

  
  
  //Obtengo las categorias
   t2= new Table("capitulo-clase-pais.csv"); 
   e = new Estructura();   
    cp5 = new ControlP5(this);
   checkbox = cp5.addCheckBox("checkBox")
                .setPosition(50, 50)
                .setColorForeground(color(120))
                .setColorActive(color(255))
                .setColorLabel(color(0))
                .setSize(20, 20)
                .setItemsPerRow(1)
                .setSpacingColumn(30)
                .setSpacingRow(10);
   dataCapituloClasePais= new DataHolderCapituloClasePais[t2.getNumRows()-1];
   ArrayList<String> mostrados = new ArrayList<String>();
   nombres  = new HashMap<Integer,String>();
   for(int i=0;i<dataCapituloClasePais.length;i++){
      dataCapituloClasePais[i]= new DataHolderCapituloClasePais(i);  
      //println(  dataCapituloClasePais[i].CAPITULO);
      if (!mostrados.contains(dataCapituloClasePais[i].CAPITULO)) {
          checkbox.addItem(dataCapituloClasePais[i].CAPITULO, i);          
          nombres.put(i,dataCapituloClasePais[i].CAPITULO);                    
          mostrados.add(dataCapituloClasePais[i].CAPITULO);
      }//if    
          String Cap          = dataCapituloClasePais[i].CAPITULO;
          String Clase_nombre =  dataCapituloClasePais[i].CLASE;
          String Pais_nombre  = dataCapituloClasePais[i].PAIS;
    
    
      
          //println("cap : " + Cap); 
                
          Capitulo c = e.find(Cap);
          
          if (c == null) {
            c = new Capitulo(Cap);
            e.addCapitulo(c);
          }
          
          //println("cantidad de capitulos: ");
          //println(e.CAPITULOS.size());
          
          //println("nombreClase: "+ Clase_nombre);
          Clase cla = c.find(Clase_nombre);
          c = e.find(Cap);
          if (null == cla){
            cla = new Clase(Clase_nombre);
            c.AddClase(cla);
          }
          
          Pais p = cla.find(Pais_nombre);
          
          if (null == p) {
              p = new Pais(Pais_nombre);
              cla.addPais(p);
          }
          
          
         
     
      
      
      
   }//for
  
    //println("cantidad de capitulos en total: ");
    //println(e.CAPITULOS.size());
    
    for(int k=0; k < e.CAPITULOS.size(); k++){
        Capitulo ca = e.CAPITULOS.get(k);
        println(" clases del capitulo " + ca.CLASES.size()); 
    } 
          

}

void keyPressed() {
  if (key==' ') {
    checkbox.deactivateAll();
  } 
  else {
    for (int i=0;i<6;i++) {
      // check if key 0-5 have been pressed and toggle
      // the checkbox item accordingly.
      if (keyCode==(48 + i)) { 
        // the index of checkbox items start at 0
        checkbox.toggle(i);
        //println("toggle "+checkbox.getItem(i).name());
        // also see 
        // checkbox.activate(index);
        // checkbox.deactivate(index);
      }
    }
  }
}
  
  void createBackground (PGraphics pg, int X, int Y,float f){ 
      int x,y;
      pg.beginDraw();
      pg.smooth();
      for(int i=0;++i<pg.width*pg.height;) 
       {pg.set (x=i%pg.width, y=i/pg.width, (255-round(dist(x,y,X,Y)*f))*0x010101);}
      pg.endDraw();
      background(pg);
  }

////////////////////////////////////////////////////////////////////////////////////////

void draw(){
  background(bg);
  hover.beginDraw(); hover.background(0); hover.endDraw();
  lights();
  w.update();
  render(X,Y); 
  detectHover();
  
}

void controlEvent(ControlEvent theEvent) {
  if (theEvent.isFrom(checkbox)) {
    myColorBackground = 0;
    
    ////println("##############");
      ////println("chequeados: ");
    
    ocultarPaises();
    int col = 0;
    for (int i=0;i<checkbox.getArrayValue().length;i++) {
      int n = (int)checkbox.getArrayValue()[i];
     // print(n);
      if(n==1) {
        myColorBackground += checkbox.getItem(i).internalValue();
      }
      
      
      if (checkbox.getItem(i).getState()) {
        String nom_cap =   checkbox.getItem(i).getName();
        //println(checkbox.getItem(i).getName());
        
        
        //println("nombre capitulo a buscar: #" + nom_cap + "#");
        //println("clases : ");
        Capitulo cap = e.find(nom_cap);
        //println("1");
        if (cap != null) {
          //println("2");
          //println("cantidad de clases del capitulo: " + cap.CLASES.size());
          HashMap<String,String> paises_mostrar = new HashMap<String,String>();
          
          for (int p = 0; p < cap.CLASES.size(); p++) {
              Clase c = cap.CLASES.get(p);
              
              
              for (int k = 0; k < c.PAISES.size(); k++){
                String nom_pais = c.PAISES.get(k).NOMBRE_PAIS;
                paises_mostrar.put(nom_pais, nom_pais);
              }
              
              //println(" ====> "  + c.NOMBRE_CLASE);
          }
          
          mostrarPaises(paises_mostrar);
        }
          
      }
    }
   // //println();    
  }
}

void checkBox(float[] a) {
  //println(a);
}

//@@@ NEW CODE


void render(int x, int y){
  hover.beginDraw();
  pushMatrix();
    translate(x,y);
    hover.translate(x,y);
    pushMatrix();
      rotateX(w.rotation.x);
      rotateY(w.rotation.y);
      hover.rotateX(w.rotation.x);
      hover.rotateY(w.rotation.y);
      fill(WORLD_TINT);
      w.render();
      for (int i=0;i<data.length;i++){
          if (data[i].MOSTRAR){
            data[i].render(g,false);
            data[i].render(hover,true);
          }
      }
    popMatrix();
  popMatrix();
  hover.endDraw();
}

////////////////////////////////////////////////////////////////////////////////////////

void mouseDragged(){
  if (mouseButton==LEFT)  w.addRotation(mouseX,mouseY,pmouseX,pmouseY);
}

void detectHover(){
  int c=hover.get(mouseX,mouseY);
  int index= c/0x010101 + 254; 
  for(int i=0;i<data.length;i++){
    if (i==index) {
      data[i].setHoveredTo(true);
      fill(TEXT_COL);
      textFont(h1);
      text(data[i].COUNTRY,75,height-175);
      
      noFill();
    }else{
      data[i].setHoveredTo(false);}
  }
}

void mostrarPaises(HashMap<String,String> paises){
  
  
  for (String valor : paises.keySet()){
    for(int i=0; i<data.length; i++){
      if ((data[i].COUNTRY).equals(valor))
        data[i].MOSTRAR = true;
    }
  }
}

void ocultarPaises(){
  for(int i=0; i<data.length; i++){
     data[i].MOSTRAR = false;
  }
}

