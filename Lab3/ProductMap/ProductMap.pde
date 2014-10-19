/* @pjs preload="WorldVisAllCoords/data/w.png"; */

import controlP5.*;

final float MIN_TO_DEG= 1/60f;     
final float SEG_TO_DEG= 1/3600f;
final float SCALE_F= 8e-6;

int 
X,Y;
final int
TEXT_COL      = 0xaa000000,
DATA_COL      = 0xDD9ACD32,
HOVER_COL     = 0xffffaa00,
WORLD_TINT    = 0xffffffff,
LINES_WEIGHT  = 6,
BUFF_LINES_W  = 10;
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

String nombrePaisSel;
Boolean paisSel = false;
////////////////////////////////////////////////////////////////////////////////////////

//@@@ NEW CODE
Table t2;
 
DataHolderCapituloClasePais[] dataCapituloClasePais;
ControlP5 cp5;
ControlP5 cp5_cap;

CheckBox checkbox;
CheckBox check_cap;

int myColorBackground;

HashMap<Integer,String> nombres;
HashMap<Integer,PImage> img_capitulos;
HashMap<Integer,PImage> img_capitulos_checked;
Estructura e; 


void setup(){
   //Buffers
  //size(1350,690,P3D);
 size(displayWidth, displayHeight-100,P3D); 
  bg= createGraphics(width,height, JAVA2D);    //Buffer for storing the background
  hover=  createGraphics(width,height,P3D); //Color picking buffer
   //Fonts
  //h1= loadFont("WorldVisAllCoords/data/Lato-Regular-24.vlw");
  h1= loadFont("Lato-Regular-24.vlw");
  //h2= loadFont("WorldVisAllCoords/data/Lato-Light-24.vlw");
  h2= loadFont("Lato-Light-24.vlw");
  h3= createFont("Arial",18,false);
   //General settings
  X= width/2+100;
  Y= height/2-100;
  
  
  createBackground (bg,X,Y,.1);
  frameRate(60);
  cursor(CROSS);
  textMode(SCREEN);
   //Objects
  //w= new Globe(250,24,"WorldVisAllCoords/data/w.png");
  w= new Globe(170,60,"w.png");
  //t= new Table("WorldVisAllCoords/data/coords2.csv");
  t= new Table("coords2.csv");
  ////println("lineas"+t.getNumRows());
  data= new DataHolder[t.getNumRows()-1];
  for(int i=0;i<data.length;i++){
    data[i]= new DataHolder(i);  
  }
  

  
  
  //Obtengo las categorias
   PFont fontLabel = createFont("Arial",11,false);
   t2= new Table("capitulo-pais-clase-productos.csv"); 
   e = new Estructura();   
    cp5 = new ControlP5(this);
    
    
   checkbox = cp5.addCheckBox("checkBox")
                .setPosition(20, 20)
                .setColorForeground(color(0))
                .setColorActive(color(255))
                .setColorLabel(color(0))
                .setSize(15, 15)
                .setItemsPerRow(1)
                .setSpacingRow(6);
               
   cp5.setFont(fontLabel);
   
   img_capitulos = new HashMap<Integer,PImage>();
   img_capitulos_checked = new HashMap<Integer,PImage>();
   
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
    
          String img_name = Cap;
          img_name = img_name.replace(" ", "-");
          img_capitulos.put(i, loadImage("data/checkboxes/"+img_name+"-OFF.png"));
          img_capitulos_checked.put(i, loadImage("data/checkboxes/"+img_name+"-ON.png"));
          
      
          //@@@@@@@@ NEW CODE  
          int Cantidad_Productos = dataCapituloClasePais[i].CANTIDAD_PRODUCTOS;
          Capitulo c = e.find(Cap);
          
          if (c == null) {
            c = new Capitulo(Cap);
            e.addCapitulo(c);
          }
          
          Pais p = c.find(Pais_nombre);          
          if (null == p) {
              p = new Pais(Pais_nombre);
              c.addPais(p);
          }
           
          Clase cla = p.find(Clase_nombre);          
          if (null == cla){
            cla = new Clase(Clase_nombre);
            cla.setCantidadProductos(Cantidad_Productos);
            p.addClase(cla);
          }
          
          //@@@@@@@NEW CODE
 
      
   }//for
  
    //println("cantidad de capitulos en total: ");
    //println(e.CAPITULOS.size());
    
    for(int k=0; k < e.CAPITULOS.size(); k++){
        Capitulo ca = e.CAPITULOS.get(k);
        //println(" clases del capitulo " + ca.CLASES.size()); 
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
  if (key =='a'){
    checkbox.activateAll();
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
  
  
  if (paisSel){
      fill(TEXT_COL);
      textFont(h1);
      text(nombrePaisSel,75,height-175);  
      mostrarInfo();
      dibujarDetalles(nombrePaisSel);
    }
  
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
          
          for (int p = 0; p < cap.PAISES.size(); p++) {
            String nom_pais = cap.PAISES.get(p).NOMBRE_PAIS;  
            paises_mostrar.put(nom_pais, nom_pais);

            
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
      pushMatrix();
      fill(TEXT_COL);
      textFont(h1);
      text(data[i].COUNTRY,width/2+350,height/2+100);
      noFill();
      popMatrix();
      break;
    }else{
      data[i].setHoveredTo(false);
    }
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

void mouseClicked() {
  
  //if (mouseY < height-150) {
  
    int c=hover.get(mouseX,mouseY);
    int index= c/0x010101 + 254; 
    for(int i=0;i<data.length;i++){
      if (i==index) {
        data[i].setHoveredTo(true);
        fill(TEXT_COL);
        textFont(h1);
        //text(data[i].COUNTRY,20,20);
        
        nombrePaisSel = data[i].COUNTRY;
        paisSel = true;
        data[i].hovered = true;
        noFill();
        
        
        break;
      }else{
       // data[i].setHoveredTo(false);
        //paisSel = false;
      }
    }
  //}
}

void mostrarInfo(){
  
  int alto = 150;
  int ancho = width;
  
  /*
  Group g2 = cp5.addGroup("g2")
                .setPosition(0,height-alto)
                .setWidth(ancho)
                .setHeight(20)
                .activateEvent(true)
                .setBackgroundColor(color(255,80))
                .setBackgroundHeight(alto)
                .setLabel("Hello World.")
                ;
                
   cp5.addSlider("S-1")
     .setPosition(80,10)
     .setSize(180,9)
     .setGroup(g2)
     ;
     
  cp5.addSlider("S-2")
     .setPosition(80,20)
     .setSize(180,9)
     .setGroup(g2)
     ;
     
  cp5.addRadioButton("radio")
     .setPosition(10,10)
     .setSize(20,9)
     .addItem("black",0)
     .addItem("red",1)
     .addItem("green",2)
     .addItem("blue",3)
     .addItem("grey",4)
     .addItem("2black",5)
     .addItem("2red",6)
     .addItem("2green",7)
     .addItem("2blue",8)
     .addItem("2grey",9)
     .setGroup(g2)
     ;
     */                
 // rect(0,height-alto,ancho,alto);
}

void dibujarDetalles(String pais){
  int alto = 150;
  int ancho = width;
  
  HashMap<Float,String> agregados = new HashMap<Float,String>();
  cp5_cap = new ControlP5(this);
  check_cap = cp5_cap.addCheckBox("checkBox_cap")
                          .setPosition(0,height-alto)
                          .setColorForeground(color(0))
                          .setColorActive(color(255))
                          .setColorLabel(color(0))
                          .setSize(41,20)
                          .setItemsPerRow(20)
                          .setSpacingRow(6);
  
  for(int i=0; i < e.CAPITULOS.size(); i++){
        Capitulo ca = e.CAPITULOS.get(i);
        for (int j=0; j < ca.PAISES.size(); j++){
          if (pais.equals(ca.PAISES.get(j).NOMBRE_PAIS)){
             for (int k=0;k<checkbox.getArrayValue().length;k++) {
                
                if (checkbox.getItem(k).getState()) {
                  String nom_cap = checkbox.getItem(k).getName();
                  println("capitulo"+nom_cap);
                  
                  agregados.put(checkbox.getItem(k).internalValue(),nom_cap);
                            
                  
                }
             }
              
          }
        }
    } 
   
   for (Float valor : agregados.keySet()){
     check_cap.addItem(valor.toString(), valor);
   }
   

  
   for(Toggle t:check_cap.getItems()) {
      // replace the default view for each checkbox toggle with our custom view 
      t.setView(new CheckBoxItemView());
    }
  


  
}







