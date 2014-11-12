
Arquitectura:
Se cuenta con 3 grandes componentes.
1) Proyecto WiimoteLib 
Es el encargado de capturar las se�ales enviadas por los controles al pc mediante bluetooth. El proyecto original se puede encontrar en http://wiimotelib.codeplex.com/
Para nuestro trabajo se le aplicaron algunas modificaciones como el env�o de mensajes OSC, el uso de wiimotes con motion plus incorporado, entre otras.
Se encuentra codificado en c#

2) ExampleOutput
Proyecto openframeworks encargado en recibir los mensajes OSC con las se�ales de los controles y traducirlas a mensajes midi acordes al instrumento que se desea tocar. Estos mensajes midi son enviados a un puerto midi creado con LoopMidi. 
Tambi�n contiene la interfaz de usuario.

Para cuando quisimos cambiarle el nombre ya se nos complicaba demasiado con las referencias y termin� quedando as�

3) LoopMidi
Recibe los mensajes enviados por el ExampleOuput y los reenv�a al Ableton Live

4) AbletonLive
Recibe los mensajes midi y los reproduce

Instrucciones de uso:
1) Iniciar la aplicaci�n de ExampleOutput
2) Iniciar LoopMidi y luego el Ableton Live mediante el archivo de configuraci�n Config WiiBand
3) Conectar los wiimotes necesarios a la pc
4) Correr el proyecto WiimoteLib
