class Thing {
  public float WIDTH, HEIGHT;
  private PImage img;  
  
  
  /**
   * Construct Thing by Initializing the Thing
   */
  Thing(String img_src) {
    // Load In Image
    img = loadImage(img_src);
    
    // Store Properties
    WIDTH   = img.width;
    HEIGHT   = img.height;
  }
  


  /**
   * Displays Current Image Thing at
   *  given location
   *
   * @param x - X Location to Show Image
   * @param y - Y Location to Show Image
   */
  void show(int x, int y) {
    image(img, x, y, WIDTH, HEIGHT);
  }
  
  /**
   * Sets Size of current Image Thing
   *
   * @param w - Width of Thing
   * @param h - Height of Thing
   */
  void setSize(float w, float h) {
    WIDTH   = w;
    HEIGHT  = h;
  }
  
  
  /**
   * Resized current Image Thing with an offset to
   *  size.
   *
   * @param w - Width Precentage
   * @param h - Height Precentage
   */
  void resize(float w, float h) {
    WIDTH   *= w;
    HEIGHT  *= h;
  }
};
