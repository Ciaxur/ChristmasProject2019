#include "./include/Stars.h"


/* CONSTRUCTORS */

/**
 * Default Constructor
 * Sets Default values for Star Properties
 */
Stars::Stars(): color(240, 240, 240) {
    stars.resize(40);           // 40 Stars                         [Default]
    starRadius = 3;             // 3 Pixel Radius                   [Default]
    starLifeFrame = 0;          // Always Starts at 0
    FRAMES_TILL_FADE = 10;      // 10 Frame Gap for Fading Effect   [Default]
    STAR_MAX_LIFE_FRAME = 40;   // 40 Frames Life                   [Default]
}

/**
 * Constructs the Properties of the Stars
 * Default color is White
 * 
 * @param totalStars - Total Numbers of Stars to Allocate for
 * @param r - The Radius of each star
 * @param frameFadeGap - The Gap between Fade In/Out
 * @param starMaxLife - The Max Life of the Stars
 */
Stars::Stars(int totalStars, int r, int frameFadeGap, int starMaxLife): color(240, 240, 240) {
    // Setup Star Properties
    stars.resize(totalStars);
    starRadius = r;
    starLifeFrame = 0;
    FRAMES_TILL_FADE = frameFadeGap;
    STAR_MAX_LIFE_FRAME = starMaxLife;
}



/* CREATION / GENERATION METHODS */

/**
 * Generates Random Locationss using a Uniform Distribution
 *  Generator.
 * 
 * @param totalPoints - The Total Number of Points Generated
 * @param v - Vector Reference of Vector2D Structs that will be used to store points
 * @param min1 - The Minimum Value to Generate for X
 * @param max1 - The Maximum Value to Generate for X
 * @param min2 - The Minimum Value to Generate for Y
 * @param max2 - The Maximum Value to Generate for Y
 */
void Stars::genRandomLocations(int totalPoints, std::vector<Vector2D> &v, int min1, int max1, int min2, int max2) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> d1(min1, max1);
    std::uniform_int_distribution<int> d2(min2, max2);

    for (int i=0; i<totalPoints; i++)
        v.push_back( {d1(gen), d2(gen)} );
}

/**
 * Updates the Stars' Data in order to Draw
 * 
 * @param WIDTH - The Width of the Window
 * @param HEIGHT - The Height of the Window
 */
void Stars::update(int WIDTH, int HEIGHT) {
    // GENERATE NEW STARS!
    if(!starLifeFrame) {
        int size = stars.size();
        stars.clear();                              // Empty out the Vector
        genRandomLocations(size, stars, 0, WIDTH, 0, HEIGHT);
        starLifeFrame = STAR_MAX_LIFE_FRAME;        // Reset Life Frame
    }



    // CALCULATE ALPHA
    float alpha = 1.0;
    int fadeOutFrames = starLifeFrame - FRAMES_TILL_FADE;
    int fadeInFrames = STAR_MAX_LIFE_FRAME - starLifeFrame;
    if(fadeOutFrames <= 0) {
        alpha -= (fadeOutFrames * -1.0) / FRAMES_TILL_FADE;
    } 
    
    else if(fadeInFrames <= FRAMES_TILL_FADE) {
        alpha = fadeInFrames / (FRAMES_TILL_FADE * 1.0);
    }

    // Store Alpha in Byte
    color.a = alpha * 255;
}

/**
 * Draws Stars in Current State
 * 
 * @param ctx - Cairo Context Referece
 * @param WIDTH - The WIDTH of the Window
 * @param HEIGHT - The Height of the Window
 */
void Stars::draw(const CTX_REF& ctx, int WIDTH, int HEIGHT) {
    // DRAW STARS!
    ctx->set_source_rgba(0.94, 0.94, 0.94, (color.a / 255.0));
    for(const Vector2D &p : stars) {
        ctx->arc(p.x, p.y, starRadius, 0, 2*M_PI);
        ctx->fill();
    }

    starLifeFrame--;
}


/* SETTERS */

/**
 * Sets the Radius of each Star
 * 
 * @param r - The Radius of Each Star
 */
void Stars::setRadius(int r) {
    starRadius = r;
}

/**
 * Sets the Frame Fade Gap between Fade In/Out
 * 
 * @param fadeGap - The Fade Gap
 */
void Stars::setFrameFadeGap(int fadeGap) {
    FRAMES_TILL_FADE = fadeGap;
}

/**
 * Sets the Max Frame Life of the Stars till DEATH
 * 
 * @param maxLife - The Maximum Frame Life of all Stars
 */
void Stars::setMaxLifeFrame(int maxLife) {
    STAR_MAX_LIFE_FRAME = maxLife;
}

/**
 * Set the Color of all Stars
 * 
 * @param _color - Reference to RGBA Struct
 */
void Stars::setColor(RGBA& _color) {
    color.r = _color.r;
    color.g = _color.g;
    color.b = _color.b;
    color.a = _color.a;
}