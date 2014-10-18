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


