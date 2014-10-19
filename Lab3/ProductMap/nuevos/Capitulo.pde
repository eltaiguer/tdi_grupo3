public class Capitulo {
  public String NOMBRE_CAPITULO;
  public ArrayList<Pais> PAISES;
  
    Capitulo(String nombre) {
      NOMBRE_CAPITULO = nombre;
      PAISES  = new ArrayList<Pais>();
    }
  
    void AddPais(Pais p) {
      PAIS.add(p);
    }
    
    Clase find(String nombre){
     
      for (int i = 0 ; i < PAISES.size(); i++){
          if (nombre.equals(PAISES.get(i).NOMBRE_PAIS)){
             return PAISES.get(i);
          }
      }
   
   return null;
    }
}  
