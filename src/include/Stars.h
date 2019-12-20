#pragma once
#include "Vector2D.h"
#include "include/ContextArea.h"
#include <vector>
#include <random>


/**
 * Stars Object that handles, updates, and draws
 *  stars using a Uniform Distrubution Generator
 */
class Stars {
    private:
        std::vector<Vector2D>   stars;                  // Star Locations
        int                     starRadius;             // Star Radius
        RGBA                    color;                  // Star Color
        int                     starLifeFrame;          // Current Life Frame till DEATH
        int                     FRAMES_TILL_FADE;       // Frame Gap till Fade In/Out
        int                     STAR_MAX_LIFE_FRAME;    // Star's Maximum Frame Life

    public:     // Creation/Generation
        Stars();                                        // Sets up Default Data
        Stars(int, int, int, int);                      // Sets up All Animation Settings

        /**
         * Generates Random Locations for Stars
         *  using a Uniform Distrubution Generator
         */
        void genRandomLocations(int totalPoints, std::vector<Vector2D>&, int, int, int, int);
        void update(int, int);                          // Updates Star Maths
        void draw(const CTX_REF&, int, int);            // Draws the Stars
    
    public:     // Setters
        void setRadius(int);                            // Sets Star Radius
        void setFrameFadeGap(int);                      // Sets Frame Till Fade
        void setMaxLifeFrame(int);                      // Sets Max Life Frame
        void setColor(RGBA);                            // Sets the Stars' Color
};