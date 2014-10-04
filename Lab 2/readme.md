iCraft
El proyecto trata de detectar los movimientos de la cabeza, a la vez que los gestos faciales, y 
transformarlos en un avatar, espec�ficamente en uno inspirado en los personajes del juego Minecraft

Arquitectura:
Est� formado por dos proyectos, uno se encarga de realizar el tracking de la posici�n y movimientos de la cabeza utilizando el sensor kinect mientras que el otro reconoce gestos faciales y dibuja el avatar.

Instrucciones de uso:
Los diferentes proyectos se comunican mediante mensajes OSC. En caso de utilizar ambos proyectos en un mismo pc es necesario configurar la direcci�n IP dentro del proyecto "DollHead_Pose", en caso de ejecutarlos en distintos pcs es necesario que ambos pertenezcan a la misma red.
Una vez configurado la direcci�n IP resta solo ejecutarlos.