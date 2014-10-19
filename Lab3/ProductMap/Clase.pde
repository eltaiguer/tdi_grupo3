public class Clase{
  public String NOMBRE_CLASE;
  public int CANTIDAD_PRODUCTOS;
  
  Clase (String nombre) {
      NOMBRE_CLASE = nombre;
      CANTIDAD_PRODUCTOS = 0;
  }
  
  void setCantidadProductos(int cant) {
    CANTIDAD_PRODUCTOS = cant;
  }
  
}
