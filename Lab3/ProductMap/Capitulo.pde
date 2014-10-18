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
