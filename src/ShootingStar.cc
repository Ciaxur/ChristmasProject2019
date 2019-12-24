#include "include/ShootingStar.h"


/**
 * Initiates Default Values for Shooting Star
 *  Object
 */
ShootingStar::ShootingStar(): 
    color1(255, 255, 255), tailColor(255, 255, 255) {
    radius = 2.0f;
    tailLimit = 20;
    xs.push_back(0.0);
    ys.push_back(0.0);
    initDefaults();
}

/**
 * Sets Radius of Star
 * 
 * @param r - Radius of Star
 */
ShootingStar::ShootingStar(double r): 
    color1(255, 255, 255), tailColor(255, 255, 255) {
    radius = r;
    tailLimit = 20;
    initDefaults();
}

/**
 * Sets Radius of Star and History Limit for
 *  star tail
 * 
 * @param r - Radius of Star
 * @param _tailLimit - Limit of Tail History
 */
ShootingStar::ShootingStar(double r, int _tailLimit):
    color1(255, 255, 255), tailColor(255, 255, 255) {
    radius = r;
    tailLimit = _tailLimit;
    initDefaults();
}

/**
 * Simple Helper Method for Initializing 
 *  default values
 */
void ShootingStar::initDefaults() {
    theta = 0.0f;
    theta_dt = 0.01f;
    dx = dy = 10.0f * radius;
}

/**
 * Sets Color of Star
 * 
 * @param clr - RGBA Color Structure
 */
void ShootingStar::setColor(RGBA clr) {
    color1 = clr;
}

/**
 * Sets the Tail Trail Color
 * 
 * @param tailClr - RGBA Color Structure
 */
void ShootingStar::setTailColor(RGBA tailClr) {
    tailColor = tailClr;
}

/**
 * Set the Change in Theta
 * 
 * @param dt - Change in Theta over Time
 */
void ShootingStar::setDeltaT(double dt) {
    theta_dt = dt;
}

/**
 * Set the Change in Position over Time
 * 
 * @param _dx - Change in x-position over time
 * @param _dy - Change in y-position over time
 */
void ShootingStar::setDeltaS(double _dx, double _dy) {
    dx = _dx;
    dy = _dy;
}


/**
 * Update the Maths of the Star
 * 
 * @param WIDTH - The width limit of context
 * @param HEIGHT - The height limit of context
 */
void ShootingStar::update(int WIDTH, int HEIGHT) {
    // Add movement
    xs.push_back(cos(theta) * dx);
    ys.push_back(sin(theta) * dy);
    
    
    // Limit the tail length
    if(xs.size() > tailLimit) {
        xs.erase(xs.begin());
        ys.erase(ys.begin());
    }

    // Update Theta
    theta = (theta + theta_dt);
    theta = (theta > 2 * M_PI) ? 0.0f : theta;
}

/**
 * Draws the Shooting Star at the current
 *  state
 * 
 * @param ctx - Reference to the Context
 * @param WIDTH - The width limit of context
 * @param HEIGHT - The height limit of context
 */
void ShootingStar::draw(const CTX_REF& ctx, int WIDTH, int HEIGHT) {
    // Draw Tail
    ctx->set_source_rgba(tailColor.r / 255.0f, tailColor.g / 255.0f, tailColor.b / 255.0f, tailColor.a / 255.0f);
    for (int i=0; i<xs.size(); i++) {
        if(xs[i] < WIDTH && ys[i] < HEIGHT)
            ctx->line_to(xs[i], ys[i]);
    }
    ctx->stroke();

    // Draw Star
    if(xs.size()) {
        ctx->set_source_rgba(color1.r / 255.0f, color1.g / 255.0f, color1.b / 255.0f, color1.a / 255.0f);
        if(xs.back() < WIDTH && ys.back() < HEIGHT) {
            ctx->arc(xs.back(), ys.back(), radius, 0.0f, 2.0f * M_PI);
            ctx->fill();
        }
    }
}
