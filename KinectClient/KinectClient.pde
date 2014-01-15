import processing.net.*;//network library

int spacer;

void setup() {
  size(800, 600);
  spacer = 20;
  stroke(0);
}

void draw() {
  background(255);
  for (int y = 0; y < height; y += spacer) {
    for (int x = 0; x < width; x += spacer) {
      point(x + spacer/2, y + spacer/2);//will be replaced with ponints in an array
    }
  }
}

