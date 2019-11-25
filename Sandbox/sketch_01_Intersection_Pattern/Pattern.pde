class Pattern {
  // Path of Intersections
  private ArrayList<PVector> path;
  private int pathHistory;  // Number of Points to keep track of
  
  // Orbiter1
  private float x1, y1;     // Positions
  private float r1;         // Radius of Spin
  private float n1;         // Theta 1 used (0-2PI)
  private float f1;         // Frequency of Orbiter
  
  // Orbiter2
  private float x2, y2;     // Positions
  private float r2;         // Radius of Spin
  private float n2;         // Theta 2 used (0-2PI)
  private float f2;         // Frequency of Orbiter
  
  
  // Pattern Properties
  private int x, y;         // Pattern Location
  private int strokeW;      // Stroke Weight
  private color strokeC;    // Stroke Color
  
  
  /**
   * Construct both Orbiters
   * 
   *  @param _x - X Location of Pattern Drawn
   *  @param _y - Y Location of Pattern Drawn
   *  @param _w - Width of Pattern
   *  @param _h - Height of Pattern
   *  @param _f1 - Frequency of Orbiter 1
   *  @param _f2 - Frequency of Orbiter 2
   */
  Pattern(int _x, int _y, int _w, int _h, float _f1, float _f2){
    // Setup Pattern Properties
    x   = _x;
    y   = _y;
    r1  = _w;
    r2  = _h;
    f1  = _f1;
    f2  = _f2;
    
    // Setup Default Values
    pathHistory = 800;
    strokeW = 2;
    strokeC = color(255);
    n1 = n2 = 0.0f;
    
    
    // Initiate Path List
    path = new ArrayList();
  }
  
  private void showDebugLines() {
    fill(255);
    strokeWeight(1);
    stroke(0);
    ellipse(x1, y1, 10, 10);
    
    strokeWeight(2);
    stroke(255);
    line(x1, 0, x1, height);

    
    
    fill(255);
    strokeWeight(1);
    stroke(0);
    ellipse(x2, y2, 10, 10);
    
    strokeWeight(2);
    stroke(255);
    line(0, y2, width, y2);
  }
  
  
  public void setStrokeWeight(int weight) {
    strokeW = weight;
  }
  
  public void setStrokeColor(color c) {
    strokeC = c;
  }
  
  public void setPathHistory(int newHistory) {
    if(newHistory > 0)
      pathHistory = newHistory;
  }
  

  public void update() {
    // Calculate Orbiter 1 Data
    x1 = (cos(n1) * r1) + (x + (r1/2));
    y1 = (sin(n1) * r1);
    
    // Calculate Orbiter 2 Data
    x2 = (cos(n2) * r2);
    y2 = (sin(n2) * r2) + (y + (r2/2));
    
    // Store Intersection Points
    path.add(new PVector(x1, y2));
    
    // Restrict Path History
    if(path.size() >= pathHistory)
      path.remove(0);
    
    // Update Value Numbers based on Frequencies
    n1 = (n1 + f1) % TWO_PI;
    n2 = (n2 + f2) % TWO_PI;
  }


  public void draw() {
    // Draw Path
    noFill();
    strokeWeight(strokeW);
    stroke(strokeC);
    
    beginShape();
    for(PVector v : path)
      vertex(v.x, v.y);
    endShape();
  }
};
