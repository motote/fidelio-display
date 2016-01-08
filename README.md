# fidelio-display
Arduino library for the Philips Fidelio AS111 display

Used in a project to revive an old Fidelio AS111 clock feature, therefore only the numbers are supported.

The usage is very easy.
Just initialize the object with the pins is connected to 

FidelioDisplay display(4, 5, 6);

And write anything

display.write("2215");

You can also change the flags (dots, pm, alarm) using the toogle or set functions

