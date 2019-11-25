class Animate {
    private Thing thing;                // Thing Being Animated
    private int x, y;                   // Current Location
    private int dirX, dirY;             // Direction of Movement
    private int speed;
    

    /**
     * Resets Animation to Default
     */
    private void reset() {
        // RANDOMIZE DIRECTION
        dirX = random(1) < 0.5 ? 1 : -1;
        dirY = random(1) < 0.5 ? 1 : -1;

        // RANDOMIZE SPEED
        speed = floor(random(1, 5));

        // RANDOMIZE POSITION
        x = floor(random(width));
        y = floor(random(height));
    }

    /**
     * Sets Location of Thing
     * @param newX - Initial X Location
     * @param newY - Initial Y Location
     */
    public void setLocation(int newX, int newY) {
        x = newX;
        y = newY;
    }

    /**
     * Updates State of Animation
     */
    public void update() {
        // UPDATE POSITION & DRAW
        x += dirX * speed;
        y += dirY * speed;
        thing.show(x, y);

        // RESET IF REACHED EDGES
        if(x >= width || x <= 0 || y >= height || y < 0) 
            reset();
    }

    


    Animate(Thing t) {
        thing = t;
        reset();
    }    
};