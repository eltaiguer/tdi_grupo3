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
    
    CONT = polarToCartesian(CONTVECTOR.x, CONTVECTOR.y, 80);
    CONT1 = polarToCartesian(CONTVECTOR1.x, CONTVECTOR1.y, 80);
    CONT2 = polarToCartesian(CONTVECTOR2.x, CONTVECTOR2.y, 80);
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
  
    
    canvas.noFill();
    canvas.strokeWeight(LINES_WEIGHT);
    canvas.bezier(START.x,START.y,START.z,END.x,END.y,END.z,CONT1.x,CONT1.y,CONT1.z,CONT.x,CONT.y,CONT.z);
    canvas.bezier(CONT.x,CONT.y,CONT.z, CONT2.x,CONT2.y,CONT2.z,ENDURU.x,ENDURU.y,ENDURU.z, STARTURU.x,STARTURU.y,STARTURU.z);
    
//    canvas.line(START.x,START.y,START.z,END.x,END.y,END.z);
//    canvas.point(CONT1.x,CONT1.y,CONT1.z);
//    canvas.point(CONT2.x,CONT2.y,CONT2.z);
    
    /*
    canvas.noFill();
    canvas.strokeWeight(LINES_WEIGHT);
    canvas.bezier(START.x,START.y,START.z,END.x,END.y,END.z,END.x,END.y,END.z,CONT1.x,CONT1.y,CONT1.z);
    canvas.bezier(CONT1.x,CONT1.y,CONT1.z,CONT.x,CONT.y,CONT.z,CONT.x,CONT.y,CONT.z,CONT2.x,CONT2.y,CONT2.z);
    canvas.bezier(CONT2.x,CONT2.y,CONT2.z,ENDURU.x,ENDURU.y,ENDURU.z,ENDURU.x,ENDURU.y,ENDURU.z, STARTURU.x,STARTURU.y,STARTURU.z);
  */
  }
      
}
