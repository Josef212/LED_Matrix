# LED_Matrix-Arduino

The project includes a python script to convert images into a pixel array prepared for the arduino sketch.
The array is written into a txt named as the image.

The project also includes the arduino sketch to control the led matrix. The matrix size is controlled by a couple of macros.
Frames are stored with arrays in the Flash memory.

Will update how to display the arrays soon. ###TODO

The sketch also includes the possibility to get a button interruption and control the leds brightness with a potentiometer on a analog pin.

Both, the pin for interruptions and the analog are defined with a macro.

The convertion code and the arduino sketch is programmed considering the following pixel distribution:

0 ->->->->->   
  <-<-<-<-<-   
  ->->->->->   
  <-<-<-<-<- n   
