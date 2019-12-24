#pragma once
#include "Vector2D.h"
#include "include/ContextArea.h"
#include <vector>

class ShootingStar {
    private:
        std::vector<double> xs, ys;     // Star Body
        double  radius;                 // Star's Radius
        double  theta;                  // Theta
        double  theta_dt, dx, dy;       // Change in Star
        int     tailLimit;              // Tail Length Limit
        RGBA    color1, tailColor;      // Color Style

        void initDefaults();            // Initalizes Default Settings

    public:
        ShootingStar();                                                     // Default Constructor on 0,0 Position with white colors and 50 limit
        ShootingStar(double r);                                             // Constructs Radius
        ShootingStar(double r, int _tailLimit);                             // Constructs Radius, and Tail Limit

        void setColor(RGBA clr);                                            // Sets Color1
        void setTailColor(RGBA tailClr);                                    // Sets the Tail Color
        void setDeltaT(double dt);                                          // Sets the Change in Theta
        void setDeltaS(double _dx, double _dy);                             // Sets Changes in Position over Time

        void update(int WIDTH, int HEIGHT);                                 // Updates Math
        void draw(const CTX_REF& ctx, int WIDTH, int HEIGHT);               // Draws Shooting Star
};