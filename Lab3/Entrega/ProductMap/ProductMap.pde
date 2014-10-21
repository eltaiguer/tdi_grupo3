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
h0,h1,h2,h3,fontCheck;
//
Globe w;
Table t;
DataHolder[] data;

String nombrePaisSel;
Boolean paisSel = false;
Boolean dibujado = false;
Boolean capituloSel = false;
Boolean dibujado_slides = false;

int alto_detalles;
////////////////////////////////////////////////////////////////////////////////////////

//@@@ NEW CODE
Table t2;
 
DataHolderCapituloClasePais[] dataCapituloClasePais;
ControlP5 cp5;
ControlP5 cp5_cap;
ControlP5 cp5_cap_slider;
ControlWindow controlWindow;


CheckBox checkbox;
RadioButton check_cap;

int myColorBackground;

HashMap<Integer,String> nombres;
HashMap<Integer,PImage> img_capitulos;
HashMap<Integer,PImage> img_capitulos_checked;
HashMap<Integer,PImage> img_tab_capitulos;
HashMap<Integer,PImage> img_tab_capitulos_checked;
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
  fontCheck = createFont("Calibri", 14);
   //General settings
  X= width/2+100;
  Y= height/2-100;
  
  alto_detalles = height - 100;
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
   t2= new Table("capitulo-pais-clase-productos2.csv"); 
   e = new Estructura();   

  
    cp5 = new ControlP5(this);
    cp5_cap = new ControlP5(this);
    cp5_cap_slider = new ControlP5(this);
    
    int incrementoX = 200;
    int incrementoY = alto_detalles-10;
    for (int m=0; m<8; m++){
      
      
       if (m > 0 && (m % 3 ) == 0) {
         //YA IMPRIMI TRES COLUMNAS
         incrementoY = alto_detalles-10;    //vuelvo a la fila 0
         incrementoX += 480; //me cambio de columna
       }
       
       cp5_cap_slider.addSlider("slider"+m)
         .setPosition(incrementoX,incrementoY)
         .setRange(0,100)
         .setValue(0)
         .setHeight(20)
         .setVisible(false)
         .setColorLabel(255)
         .lock()
       ;
                  
      incrementoY += 40;   
      
      cp5_cap_slider.getController("slider"+m).getCaptionLabel().alignX(ControlP5.LEFT_OUTSIDE).setPaddingX(10);
    }
    cp5_cap_slider.addSlider("otros")
         .setPosition(incrementoX,incrementoY)
         .setRange(0,100)
         .setHeight(20)
         .setValue(0)
         .setColorLabel(255)
         .setVisible(false)
         .lock()
       ;
      
     cp5_cap_slider.getController("otros").getCaptionLabel().alignX(ControlP5.LEFT_OUTSIDE).setPaddingX(10);
    cp5_cap_slider.setFont(fontLabel);
    
   checkbox = cp5.addCheckBox("checkBox")
                .setPosition(20, 20)
                .setColorForeground(color(0))
                .setColorActive(color(255))
                .setColorLabel(color(0))
                .setSize(41, 15)
                .setItemsPerRow(1)
                .setSpacingRow(6);
               
   cp5.setFont(fontLabel);
   
   img_capitulos = new HashMap<Integer,PImage>();
   img_capitulos_checked = new HashMap<Integer,PImage>();
   
   img_tab_capitulos = new HashMap<Integer,PImage>();
   img_tab_capitulos_checked = new HashMap<Integer,PImage>();
   
   dataCapituloClasePais= new DataHolderCapituloClasePais[t2.getNumRows()-1];
   ArrayList<String> mostrados = new ArrayList<String>();
   nombres  = new HashMap<Integer,String>();
   for(int i=0;i<dataCapituloClasePais.length;i++){
      dataCapituloClasePais[i]= new DataHolderCapituloClasePais(i);  
         
      String Cap          = dataCapituloClasePais[i].CAPITULO;
      String Clase_nombre =  dataCapituloClasePais[i].CLASE;
      String Pais_nombre  = dataCapituloClasePais[i].PAIS;

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
   
   for(int i=0; i < e.CAPITULOS.size(); i++){
      Capitulo ca = e.CAPITULOS.get(i);
      String img_name = ca.NOMBRE_CAPITULO.replace(" ", "-");
    
      img_capitulos.put(i, loadImage("data/checkboxes/"+img_name+"-OFF.png"));
      img_capitulos_checked.put(i, loadImage("data/checkboxes/"+img_name+"-ON.png"));
      
      img_tab_capitulos.put(i, loadImage("data/tabs/"+img_name+"-OFF.png"));
      img_tab_capitulos_checked.put(i, loadImage("data/tabs/"+img_name+"-ON.png"));
 
      //if (!mostrados.contains(dataCapituloClasePais[i].CAPITULO)) {
      checkbox.addItem(ca.NOMBRE_CAPITULO, i);          
      nombres.put(i,dataCapituloClasePais[i].CAPITULO);                    
      //mostrados.add(dataCapituloClasePais[i].CAPITULO);
      //}//if
     
    }
   
  // inicializarTabs(); 
   
   
  
  for(Toggle t:checkbox.getItems()) {
      // replace the default view for each checkbox toggle with our custom view 
      t.setView(new CheckBoxItemView());
      
  }
  
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
  
  if (paisSel && !dibujado){
      fill(TEXT_COL);
      textFont(h1);
      text(nombrePaisSel,75,height-175);  

      dibujarDetalles(nombrePaisSel);
      dibujado = true;
    }
    
    if (paisSel && capituloSel && !dibujado_slides){
      dibujarSliders();
      dibujado_slides = true;
    }
   detectHover();

}

void controlEvent(ControlEvent theEvent) {
  if (theEvent.isFrom(checkbox)) {
    myColorBackground = 0;
    
    ocultarPaises();
    int col = 0;
    for (int i=0;i<checkbox.getArrayValue().length;i++) {
      int n = (int)checkbox.getArrayValue()[i];
     
      if(n==1) {
        myColorBackground += checkbox.getItem(i).internalValue();
      }
      
      
      if (checkbox.getItem(i).getState()) {
        String nom_cap =   checkbox.getItem(i).getName();
        
        Capitulo cap = e.find(nom_cap);
        
        if (cap != null) {
          
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
  } else if (theEvent.isFrom(check_cap)){
    
    dibujado_slides = false;
    capituloSel = true;      
  }
  
}

void dibujarSliders(){
  int cantidad_prod_clase = 0;
    int max_graficas = 8;
    int otros = 0;
    
    ArrayList<String> nombres_clases_sliders = new ArrayList<String>();
    ArrayList<Integer> valores_clases_sliders = new ArrayList<Integer>();
    
    for(int m = 0; m<10; m++){
      if (m<max_graficas){
         cp5_cap_slider.getController("slider"+m).setVisible(false);
       } else {
         cp5_cap_slider.getController("otros").setVisible(false);
       }
    }
    
    for (int i=0;i<check_cap.getArrayValue().length;i++) {
      if (check_cap.getItem(i).getState()) {
        String nom_cap = check_cap.getItem(i).getName();
        
        for (int j=0; j<e.CAPITULOS.size(); j++){
          Capitulo ca = e.CAPITULOS.get(j);
          
          if(nom_cap.equals(ca.NOMBRE_CAPITULO)){
            
            for (int k=0; k<ca.PAISES.size(); k++){
              Pais p = e.CAPITULOS.get(j).PAISES.get(k);
              if (nombrePaisSel.equals(p.NOMBRE_PAIS)){
                
                
                for (int l=0; l<p.CLASES.size(); l++){
                  Clase cla = p.CLASES.get(l);
                  
                  cantidad_prod_clase += cla.CANTIDAD_PRODUCTOS;
                   
                   if (l < max_graficas){
                      nombres_clases_sliders.add(cla.NOMBRE_CLASE);
                      valores_clases_sliders.add(cla.CANTIDAD_PRODUCTOS);
                       println("clase: " + cla.NOMBRE_CLASE + " - " + cla.CANTIDAD_PRODUCTOS);
                   } else {
                       otros += cla.CANTIDAD_PRODUCTOS;
                   }
                  
                }
                println("Cantidad total: " + cantidad_prod_clase);
                
                if (p.CLASES.size() > max_graficas){
                  nombres_clases_sliders.add("otros");
                  valores_clases_sliders.add(otros);
                }
                
               
                for (int m=0; m<nombres_clases_sliders.size(); m++){
                  String nombre_clase = nombres_clases_sliders.get(m);
                   int valor_clase = valores_clases_sliders.get(m);
                   println(nombre_clase + " : " + valor_clase); 
                   
                   if (m<max_graficas){
                     cp5_cap_slider.getController("slider"+m).setValue(Math.round((valor_clase * 100/cantidad_prod_clase)));
                     cp5_cap_slider.getController("slider"+m).setCaptionLabel(nombre_clase);
                     cp5_cap_slider.getController("slider"+m).setVisible(true);
                   } else {
                     cp5_cap_slider.getController("otros").setValue(Math.round((valor_clase * 100/cantidad_prod_clase)));
                     cp5_cap_slider.getController("otros").setCaptionLabel(nombre_clase);
                     cp5_cap_slider.getController("otros").setVisible(true);
                   }
                   
                }
                
                break;
              }
              
            }
            break;
          }
        }
     
        break;  
      }
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
        dibujado = false;
        
        if (check_cap != null)
          check_cap.remove();
          
        
        
          
        noFill();
        
        
        break;
      }else{
       //data[i].setHoveredTo(false);
        //paisSel = false;
      }
    }
  //}
}


void dibujarDetalles(String pais){
  
  int ancho = width;
  //rect(0,height-alto,ancho,56);
  HashMap<Float,String> agregados = new HashMap<Float,String>();
  
 
  check_cap = cp5_cap.addRadioButton("checkBox_cap")
                          .setPosition(0,alto_detalles-80)
                          .setColorForeground(color(0))
                          .setColorActive(color(255))
                          .setColorLabel(color(0))
                          .setSize(56,45)
                          .setItemsPerRow(20)
                          .setSpacingRow(6);
  
  
  for (int k=0;k<checkbox.getArrayValue().length;k++) {           
    if (checkbox.getItem(k).getState()) {
      String nom_cap = checkbox.getItem(k).getName();
  
      for(int i=0; i < e.CAPITULOS.size(); i++){
          Capitulo ca = e.CAPITULOS.get(i);
          if (nom_cap.equals(ca.NOMBRE_CAPITULO)){
            
              for (int j=0; j < ca.PAISES.size(); j++){
                if (pais.equals(ca.PAISES.get(j).NOMBRE_PAIS)){
                  agregados.put(checkbox.getItem(k).internalValue(),nom_cap);
                  break;
                }
             }
          }
        }
    }
  } 
   
  
   for (Float valor : agregados.keySet()){
     check_cap.addItem(agregados.get(valor), valor);
   }
   
   println("cant checkbox: "+check_cap.getInfo());

  
   for(Toggle t:check_cap.getItems()) {
      // replace the default view for each checkbox toggle with our custom view 
      t.setView(new TabItemView());
    }
  

/*
  cp5_cap.window().setPositionOfTabs(0,height-alto);
  Tab tab_cap = cp5_cap.addTab("extasadsdasdasdra")
       .setColorBackground(color(0, 160, 100))
       .setColorLabel(color(255))
       .setColorActive(color(255,128,0))
       .setWidth(400)
       ;
    
    Toggle t = (Toggle)tab_cap;
    t.setView(new TabItemView());
 /*
  for(Toggle t:tab_cap.getItems()) {
      // replace the default view for each checkbox toggle with our custom view 
      t.setView(new TabItemView());
    }
    */

    

}


/* PARA EL SETUP
void inicializarTabs(){
  int alto = 150;
  int ancho = width;
    
  CheckBox check_cap = cp5_cap.addCheckBox("checkBox_cap")
                          .setPosition(0,height-alto)
                          .setColorForeground(color(0))
                          .setColorActive(color(255))
                          .setColorLabel(color(0))
                          .setSize(56,45)
                          .setItemsPerRow(20)
                          .setSpacingRow(6);
                          
  for(int i=0; i < e.CAPITULOS.size(); i++){
     check_cap.addItem(e.CAPITULOS.get(i).NOMBRE_CAPITULO, i);
  }
  
  for(Toggle t:check_cap.getItems()) {
      // replace the default view for each checkbox toggle with our custom view 
      t.setView(new TabItemView());
    }
    
  check_cap.getItem(2).setVisible(false);
  
}


*/



