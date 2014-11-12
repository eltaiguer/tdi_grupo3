Este proyecto transforma controles de Wii en diversos instrumentos musicales, logrando así tener desde una batería en el wiimote y nunchuk hasta un órgano de iglesia en el classic controller pro. 

Arquitectura:
Se cuenta con 3 grandes componentes.
1) Proyecto WiimoteLib 
Es el encargado de capturar las señales enviadas por los controles al pc mediante bluetooth. El proyecto original se puede encontrar en http://wiimotelib.codeplex.com/
Para nuestro trabajo se le aplicaron algunas modificaciones como el envío de mensajes OSC, el uso de wiimotes con motion plus incorporado, entre otras.
Se encuentra codificado en c#

2) ExampleOutput
Proyecto openframeworks encargado en recibir los mensajes OSC con las señales de los controles y traducirlas a mensajes midi acordes al instrumento que se desea tocar. Estos mensajes midi son enviados a un puerto midi creado con LoopMidi. 
También contiene la interfaz de usuario.

Para cuando quisimos cambiarle el nombre ya se nos complicaba demasiado con las referencias y terminó quedando así

3) LoopMidi
Recibe los mensajes enviados por el ExampleOuput y los reenvía al Ableton Live

4) AbletonLive
Recibe los mensajes midi y los reproduce

Instrucciones de uso:
1) Iniciar la aplicación de ExampleOutput
2) Iniciar LoopMidi y luego el Ableton Live mediante el archivo de configuración Config WiiBand
3) Conectar los wiimotes necesarios a la pc
4) Correr el proyecto WiimoteLib
