public class Clase{
  public String NOMBRE_CLASE;
  public String CANTIDAD_PRODUCTOS;
  
  Clase (String nombre) {
      NOMBRE_CLASE = nombre;
      CANTIDAD_PRODUCTOS = 0;
  }
  
  void setCantidadProductos(String cant) {
    CANTIDAD_PRODUCTOS = cant;
  }
  
}
