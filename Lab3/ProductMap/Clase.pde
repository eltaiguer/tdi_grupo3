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
