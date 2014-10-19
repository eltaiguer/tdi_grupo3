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
