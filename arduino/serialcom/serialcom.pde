import processing.serial.*;

int value; 
char c , s;
Serial port;
PFont f; 
 
void setup()
{
 size(600,300);
 f = createFont("Colibri", 10,true);
 port = new Serial(this, "/dev/cu.usbmodemFA131", 9600);
}
 
void draw()
{
 background(0, 0, 0);
 textFont(f,200);
 text(value,200,300);
}

void keyPressed () {
  char c[]= {65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90};
  char s[]= {};
}