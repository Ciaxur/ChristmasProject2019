ArrayList<Pattern> patterns;


void setup() {
  size(500, 500);

  // Initiate Pattern List
  patterns = new ArrayList();
  
  // Add Patterns
  Pattern p1;
   p1 = new Pattern(20, height - 50, 20, 30, 0.15, 0.055);
   p1.setStrokeColor(color(188, 0, 0));
   p1.setPathHistory(2000);
   patterns.add(p1);
  
  
   p1 = new Pattern(80, height - 50, 40, 30, 0.123, 0.321);
   p1.setStrokeColor(color(0, 188, 0));
   p1.setPathHistory(500);
   patterns.add(p1);
  
   int size = 50;
   p1 = new Pattern(width/2, height/2, size, size, 0.41097, 0.4297);
   p1.setStrokeColor(color(0, 188, 188));
   p1.setPathHistory(200);
   patterns.add(p1);
}


void draw() {
  background(0);
  
  for(Pattern p : patterns) {
    p.update();
    p.draw();
  }
  
}
