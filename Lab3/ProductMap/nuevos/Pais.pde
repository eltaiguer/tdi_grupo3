public class Pais{
  public String NOMBRE_PAIS;
  public ArrayList<Clase> CLASES;
  Pais(String nombre) {
      NOMBRE_PAIS = nombre;
      CLASES = new ArrayList<Clase>();
  }
  
  
  void addClase(Clase c) {
    CLASES.add(c);
  }
  
  Clase find(String nombre) {
    for (int i = 0 ; i < CLASES.size(); i++){
          if (nombre.equals((CLASES.get(i)).NOMBRE_CLASE)){
             return CLASE.get(i);
          }
      }
    return null;    
  }
}
