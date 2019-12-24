#include <iostream>
#include <thread>

#ifdef __arm__      // GPIO Wiring on Raspberry PI (Mouse Click else)
#include <wiringPi.h>
#endif

// VISUAL OBJECTS
#include "include/Stars.h"
#include "include/ShootingStar.h"

// GTK SANDBOX CLASSES
#include "include/MyWindow.h"


// MATHS
#define _USE_MATH_DEFINES
#include <math.h>


// GLOBAL VARIABLE
int stateIndex = 0; // Handled by Mouse Click OR Button on RaspberryPI


/**
 * Simple Rain Drop Strcuture
 * 
 * - pos - Current Position (Vector2D)
 * - startPos - Starting Position for Resetting(Vector2D)
 * - yDeadZone - y-position to Reset when Hit
 * - vel - Velocity of Rain Drop
 * - width - Width of Rain Drop (Rectangle)
 * - height - Height of Rain Drop (Rectangle)
 */
struct RainDrop {
    Vector2D    pos,            // Current Position of Rain Drop
                startPos;       // Starting Position of Rain Drop

    int         yDeadZone;      // Y Offset from Starting Position where Death occurs

    float       vel,            // Velocity at which to increment Displacement
                width,          // Width of Rain Drop
                height;         // Height of Rain Drop
};


class ChristmasApp: public ContextArea {
    public:
        ChristmasApp(): stars(90, 2, 40, 100), 
                        groot_sparkles(5, 1, 18, 40),
                        ss(3.0f, 30) {
            std::cout << "Christmas 2019 Constructed!!\n";
            initContextArea(TARGET_FPS::THIRTY);
        }
    

    private:    // KEYBOARD / MOUSE EVENTS
        bool onKeyPress(GdkEventKey* event) {
            if(event->keyval == GDK_KEY_q) {        // Quit on Key Press 'Q'
                std::cout << "Quitting out of Application!" << std::endl;
                return false;
            }
            
            // Return True to keep Running
            return true;
        }

        bool onKeyRelease(GdkEventKey* event) {     // Similair to KeyPress
            // Return True to keep Running
            return true;
        }

        // FLIP THROUGHT STATE ON MOUSE CLICK!
        bool onMousePress(GdkEventButton *event) {
            stateIndex = (stateIndex + 1) % 4;
            return true;
        }

        
    private:    // VAIRABLES USED
        GDK_IMAGE   tiredFace_img, z1_img, z3_img;
        GDK_IMAGE   happyFace_img, sunFace_img, sunRims_img;
        GDK_IMAGE   sadFace_img, tear_img;
        GDK_IMAGE   santaHat_img, 
                    santaHat2_img, 
                    santa_img,
                    merryXMas_img;
        GDK_IMAGE   bgk_space_img;                  // Background Images
        GDK_IMAGE   groot_img, grootHat_img, bunny_img, bunny2_img;
        Stars       stars, groot_sparkles;          // Initiated in ChristmasApp Constructor
        ShootingStar ss;
        std::vector<Stars>    christmasLights;      // Christmas Lights
        std::vector<RainDrop> rain;

    private:    // DRAWING FUNCTIONS
        void setup() {
            // SETUP IMAGES
            std::string rootPath = "";
            #ifdef __arm__      // Different Path for my Raspberry PI
                rootPath = "/home/pi/Downloads/ChristmasProject2019/";
            #endif

            tiredFace_img   = createImageBuffer( rootPath + "resources/Sleep-Emoji/64/FaceOnly.png" );
            z1_img          = createImageBuffer( rootPath + "resources/Sleep-Emoji/128/Z1.png" );
            z3_img          = createImageBuffer( rootPath + "resources/Sleep-Emoji/64/Z3.png" );

            happyFace_img   = createImageBuffer( rootPath + "resources/Happy_Emoji/128/Smile_Face.png" );
            sunFace_img     = createImageBuffer( rootPath + "resources/Sun-Emoji/128/Sun-Face.png" );
            sunRims_img     = createImageBuffer( rootPath + "resources/Sun-Emoji/128/Sun-Rims.png" );

            sadFace_img     = createImageBuffer( rootPath + "resources/Sad-Emoji/128/Sad.png" );
            tear_img        = createImageBuffer( rootPath + "resources/Sad-Emoji/128/Tear.png" );

            santaHat_img    = createImageBuffer( rootPath + "resources/Christmas/64/santa-hat.png" );
            santaHat2_img   = createImageBuffer( rootPath + "resources/Christmas/128/santa-hat2.png" );
            santa_img       = createImageBuffer( rootPath + "resources/Christmas/64/santa.png" );
            merryXMas_img   = createImageBuffer( rootPath + "resources/Christmas/256/Merry-Christmas.png" );

            bgk_space_img   = createImageBuffer( rootPath + "resources/Background/480/CalmSpace_Bkg.png" );
            groot_img       = createImageBuffer( rootPath + "resources/Fuzzy/128/Groot.png" );
            grootHat_img    = createImageBuffer( rootPath + "resources/Christmas/64/vector-hat.png" );
            bunny_img       = createImageBuffer( rootPath + "resources/Fuzzy/64/BunnyBreathing_Anim/Bunny_State1.png" );
            bunny2_img       = createImageBuffer( rootPath + "resources/Fuzzy/64/BunnyBreathing_Anim/Bunny_State2.png" );


            // CONSTRUCT RAIN DROP DATA
            float hs[] = { 13.4f, 17.0f, 15.0f, 14.0f, 17.0f, 13.0f, 19.0f, 12.0f };
            float vs[] = { 6.0f, 5.0, 4.0f, 4.0f, 5.0f, 6.0f, 7.0f, 5.0f };
            for(int i=0; i<8; i++) {
                rain.push_back(
                    { {9*i, 0}, {9*i, 0}, 50, vs[i], 2.0f, hs[i] }
                );
            }

            
            // IMAGE MODIFICATION
            z1_img = resizeImage(z1_img, 64, 64);

            // Christmas Setup
            christmasLights = {
                {20, 2, 40, 100},
                {20, 2, 40, 100},
                {20, 2, 40, 100},
                {20, 2, 40, 100}
            };
            christmasLights[0].setColor({179,    0,      12});
            christmasLights[1].setColor({255,    0,      18});
            christmasLights[2].setColor({0,      255,    62});
            christmasLights[3].setColor({0,      179,    44});


            // Setup Groot's Sparkles & Shooting Star
            groot_sparkles.setColor({255, 255, 255, 10});
            ss.setDeltaT(0.02f);
            ss.setDeltaS(1000.0f, 250.0f);
            ss.setColor({200, 200, 200, 200});
            ss.setTailColor({255, 255, 255, 150});
        }

        double fuzzy_theta1 = 0.0;
        double z_size = 0.25;
        bool z_flip = false;
        void drawFuzzyState(const CTX_REF& ctx, const int WIDTH, const int HEIGHT) {
            // Delta Calculation
            double dx = cos(fuzzy_theta1);
            double dy = sin(fuzzy_theta1);

            
            // DRAW BACKGROUND
            //  scale Background to Fit
            //  smooth movement
            ctx->save();
            ctx->translate(-200.0f + (dx * 2), dy);
            ctx->scale( (WIDTH*1.5 + (dx*5)) / bgk_space_img->get_width(), (HEIGHT*1.2 + (dy*7)) / bgk_space_img->get_height() );
            drawImage(ctx, bgk_space_img);
            ctx->restore();


            // DISPLAY FUZZY TEXT
            ctx->save();
            ctx->set_source_rgb(1.0, 1.0, 1.0);
            ctx->select_font_face("Monospace", Cairo::FontSlant::FONT_SLANT_NORMAL, Cairo::FontWeight::FONT_WEIGHT_NORMAL);
            ctx->set_font_size(50.0);
            ctx->translate((WIDTH/2) - 70, HEIGHT/2);
            ctx->show_text("FUZZY");

            // DRAW BUNNY
            ctx->save();
            ctx->translate(62.0f, -75.0f);
            drawImage(ctx, (z_flip) ? bunny_img : bunny2_img);

            // draw zzz's
            // handle size change
            ctx->translate(0.0f, 10.0f);
            if(z_size > 0.25f || z_size <= 0.05f) z_flip = !z_flip;
            z_size += (z_flip) ? 0.005f : -0.005f;
            ctx->scale(z_size, z_size);

            drawImage(ctx, z1_img);
            ctx->restore();


            // DRAW GROOT + HAT
            ctx->translate(140.0f, -100.0f);
            drawImage(ctx, groot_img);

            ctx->save();
            ctx->translate(24.0f, -10.0f);
            drawImage(ctx, grootHat_img);
            ctx->restore();



            // Draw Sparkles around Groot only
            ctx->translate(10.0f, 10.0f);
            groot_sparkles.update(   groot_img->get_width() - 30.0f, groot_img->get_height());
            groot_sparkles.draw(ctx, groot_img->get_width() - 30.0f, groot_img->get_height());

            ctx->restore();


            // DRAW SHOOTING STAR
            ctx->save();
            ctx->translate(0, 0);
            ss.update(WIDTH, HEIGHT);
            ss.draw(ctx, WIDTH, HEIGHT);
            ctx->restore();
            
            

            


            // Increment Delta
            fuzzy_theta1 = (fuzzy_theta1 + 0.01);
            fuzzy_theta1 = (fuzzy_theta1 > 2*M_PI) ? 0.0 : fuzzy_theta1; 
        }



        /**
         * TIRED STATE
         *  - Draws Sleepy Emoji with Z's
         *  - Draws Stars
         *  - Draws "Tired" Logo
         */
        void drawTiredState(const CTX_REF& ctx, const int WIDTH, const int HEIGHT) {
            // DRAW BACKGROUND
            ctx->set_source_rgb(0.1, 0.1, 0.1);
            ctx->rectangle(0, 0, WIDTH, HEIGHT);
            ctx->fill();


            // DRAW STARS
            stars.update(WIDTH, HEIGHT);
            stars.draw(ctx, WIDTH, HEIGHT);

            // DRAW CHRISTMAS LIGHTS
            for(Stars &light : christmasLights) {
                light.update(WIDTH, HEIGHT);
                light.draw(ctx, WIDTH, HEIGHT);
            }


            // TIRED STATE
            ctx->save();
            ctx->set_source_rgb(1.0, 1.0, 1.0);
            ctx->select_font_face("Monospace", Cairo::FontSlant::FONT_SLANT_NORMAL, Cairo::FontWeight::FONT_WEIGHT_NORMAL);
            ctx->set_font_size(50.0);
            ctx->translate((WIDTH/2) - 80, HEIGHT/2);
            ctx->show_text("TIRED");

            // DRAW SANTA!
            ctx->translate(-15, -90);
            drawImage(ctx, santa_img);
            ctx->restore();


            // DRAW TIRED FACE
            ctx->save();
            
            ctx->translate((WIDTH/2) + 80, (HEIGHT/2) + 20);
            drawImage(ctx, tiredFace_img);

            ctx->translate(-25, -25);
            drawImage(ctx, santaHat_img);


            // Move the Z's Up and Down
            ctx->save();
            ctx->translate(40, -20 + sin(frameCount * 0.03) * 4.0);
            drawImage(ctx, z3_img);
            ctx->restore();

            ctx->save();
            ctx->translate(80, -70 + sin((frameCount * 0.03) + 0.8) * 6.0);
            drawImage(ctx, z1_img);
            ctx->restore();

            ctx->save();
            ctx->translate(150, -120 + sin((frameCount * 0.03) + 1.2) * 8.0);
            drawImage(ctx, z1_img);
            ctx->restore();

            ctx->restore();
        }


        /**
         * HAPPY STATE
         *  - Smily Face
         *  - Clouds
         *  - Spinning Sun
         */
        double r = 0.0;
        double scaleAmt = 0.0;
        void drawHappyState(const CTX_REF& ctx, const int WIDTH, const int HEIGHT) {
            // DRAW BACKGROUND
            ctx->set_source_rgb(0.37, 0.68, 0.89);
            ctx->rectangle(0, 0, WIDTH, HEIGHT);
            ctx->fill();

            // MATHS Used
            double sinScale = sin(scaleAmt);
            double cosScale = cos(scaleAmt);
            double sinCosScale = sinScale * cosScale;

            ctx->save();


            // CHRISTMAS THEME!
            ctx->save();
            ctx->translate(50, HEIGHT - 150);
            drawImage(ctx, merryXMas_img);
            ctx->restore();


            // DRAW CLOUDS
            ctx->save();
            ctx->set_source_rgba(0.917, 0.917, 0.917, 1.0);
            ctx->translate((WIDTH/2) - 8 * cosScale, 60 + 5 * sinScale);
            ctx->scale(1.7, 1.7);
            ctx->arc(   30,                 3 * sinScale, 10, 0, 2*M_PI);
            ctx->arc(   18 + sinScale,     -2 * sinScale, 15, 0, 2*M_PI);
            ctx->fill();
            ctx->arc(   -sinScale,          sinScale, 25, 0, 2*M_PI);
            ctx->arc(  -18,                 5 * sinScale, 15, 0, 2*M_PI);
            ctx->fill();
            ctx->arc(  -30 + sinScale,      0, 10, 0, 2*M_PI);
            ctx->fill();
            ctx->restore();

            // Nromal Cloud
            ctx->save();
            ctx->set_source_rgba(0.917, 0.917, 0.917, 1.0);
            ctx->translate( 50 + sinScale * 4.14, 70 + cosScale * 3.15);
            ctx->scale(1.8, 1.8);
            ctx->arc(   sinScale,     cosScale,  15, 0, 2*M_PI);
            ctx->arc(   15,          -3,         18, 0, 2*M_PI);
            ctx->arc(   33,          -8,         23, 0, 2*M_PI);
            ctx->arc(   55,           cosScale,  13, 0, 2*M_PI);
            ctx->fill();
            ctx->restore();
            
            // Stretchy Cloud
            ctx->save();
            ctx->set_source_rgba(0.917, 0.917, 0.917, 1.0);
            ctx->translate((WIDTH/2) + sinScale, 260 - cosScale);
            ctx->scale(1.8, 1.8);
            ctx->arc(   0,       sinScale, 15, 0, 2*M_PI);
            ctx->arc(   15,      cosScale, 15, 0, 2*M_PI);
            ctx->arc(   30,     -sinScale, 15, 0, 2*M_PI);
            ctx->fill();
            ctx->arc(   45,     -cosScale, 15, 0, 2*M_PI);
            ctx->fill();
            ctx->restore();

            // Weirdo Cloud
            ctx->save();
            ctx->set_source_rgba(0.917, 0.917, 0.917, 1.0);
            ctx->translate(WIDTH - 200 + (10 * sinCosScale), HEIGHT - 100);
            ctx->scale(1.5, 1.5);
            ctx->arc(   sinCosScale,             2 * sinScale,          20, 0, 2*M_PI);
            ctx->arc(   30 + 5*cosScale,        -15 + 6*sinCosScale,    30, 0, 2*M_PI);
            ctx->fill();
            ctx->arc(   55 + 12*sinCosScale,     5 * cosScale,          15, 0, 2*M_PI);
            ctx->fill();
            ctx->restore();
            
            // Cloudy Cloud
            ctx->save();
            ctx->set_source_rgba(0.917, 0.917, 0.917, 1.0);
            ctx->translate(WIDTH - 200, 100);
            ctx->scale(1.5, 1.5);
            ctx->arc(   -sinCosScale,       sinCosScale,        20, 0, 2*M_PI);
            ctx->arc(   20,                 cosScale,           25, 0, 2*M_PI);
            ctx->fill();
            ctx->arc(   40 + sinScale,     -15 + sinCosScale,   25, 0, 2*M_PI);
            ctx->arc(   40 + 2 * cosScale,  10 + sinScale,      15, 0, 2*M_PI);
            ctx->fill();
            ctx->arc(   55 + cosScale,      10 + 2*cosScale,    15, 0, 2*M_PI);
            ctx->arc(   65 + cosScale,      10 * cosScale,      20, 0, 2*M_PI);
            ctx->fill();
            ctx->restore();


            
            // DRAW HAPPY FACE
            ctx->save();
            ctx->translate((WIDTH/3) - 50, (HEIGHT/3) + 20);
            ctx->scale(0.5, 0.5);
            ctx->rotate(-M_PI / 6);
            drawImage(ctx, happyFace_img);

            // DRAW CHRISTMAS HAT!
            ctx->translate(0, -85);
            drawImage(ctx, santaHat2_img);
            ctx->restore();


            // HAPPY STATE
            ctx->set_source_rgb(1.0, 1.0, 1.0);
            ctx->select_font_face("Monospace", Cairo::FontSlant::FONT_SLANT_NORMAL, Cairo::FontWeight::FONT_WEIGHT_NORMAL);
            ctx->set_font_size(50.0);
            ctx->translate((WIDTH/2) - 80, HEIGHT/2);
            ctx->show_text("HAPPY");
            ctx->restore();


            // DRAW SUN
            ctx->save();
            ctx->translate(WIDTH - sunFace_img->get_width() - 20, 20);
            drawImage(ctx, sunFace_img);

            double scale = 0.1 * sin(5 * scaleAmt) + 1.1;
            ctx->translate(sunFace_img->get_width()/2, sunFace_img->get_height()/2);
            ctx->rotate(r);
            ctx->scale(scale, scale);
            ctx->translate(-sunFace_img->get_width()/2, -sunFace_img->get_height()/2);
            drawImage(ctx, sunRims_img);
            
            // Limit Rotation to 2PI
            if(r >= 2*M_PI) r = 0;
            else r += 0.01;

            // Limit Scales to 2PI
            if(scaleAmt >= 2 * M_PI) scaleAmt = 0.0;
            else scaleAmt += 0.01; 

            
            ctx->restore();
        }
        

        /**
         * SAD STATE
         *  - Tearing Sad Face
         *  - Rainy Clouds
         */
        float tearSize = 0.01;          // Tear Size
        float tearAcc = 0.50;           // Tear Acceleration
        float tearVel = 0.0f;           // Tear Velocity
        float tearDisp = 0.0f;          // Tear Displacement
        float cloudTheta = 0.00;        // Cloud Theta change for Sin/Cos
        void drawSadState(const CTX_REF& ctx, const int WIDTH, const int HEIGHT) {
            // DRAW BACKGROUND
            ctx->set_source_rgb(0.204, 0.250, 0.2588);
            ctx->rectangle(0, 0, WIDTH, HEIGHT);
            ctx->fill();

            // SAD STATE
            ctx->save();
            ctx->set_source_rgb(1.0, 1.0, 1.0);
            ctx->select_font_face("Monospace", Cairo::FontSlant::FONT_SLANT_NORMAL, Cairo::FontWeight::FONT_WEIGHT_NORMAL);
            ctx->set_font_size(50.0);
            ctx->translate((WIDTH/2) - 50, HEIGHT/2);
            ctx->show_text("SAD");
            ctx->restore();


            // DRAW FACE & TEAR
            ctx->save();
            ctx->translate(WIDTH/2 + 50, 120);
            drawImage(ctx, sadFace_img); 

            // animate tear dropping
            ctx->translate(100 - (tearSize * 30), 75 + tearDisp);
            ctx->scale(tearSize, tearSize);
            drawImage(ctx, tear_img);
            ctx->restore();


            cloudTheta += 0.05f;
            float sinDelta = sin(cloudTheta);
            float cosDelta = cos(cloudTheta);
            if(cloudTheta >= 2*M_PI) cloudTheta = 0.0f;

            // Cloudy Cloud
            ctx->save();
            ctx->set_source_rgba(0.550, 0.550, 0.550, 1.0);
            ctx->translate(WIDTH - 210, 55);
            ctx->rotate(0.15);
            ctx->scale(1.5, 1.5);
            ctx->arc(  4 * sinDelta,          2   * cosDelta,       20, 0, 2*M_PI);
            ctx->arc(  20 + (4 * sinDelta),   1.5 * cosDelta,       25, 0, 2*M_PI);
            ctx->fill();
            ctx->arc(  40 - (2 * cosDelta),  -15,                   25, 0, 2*M_PI);
            ctx->arc(  40 + (2 * cosDelta),   10,                   15, 0, 2*M_PI);
            ctx->fill();
            ctx->arc(  55 + cosDelta,         10,                   15, 0, 2*M_PI);
            ctx->arc(  60 - (3 * cosDelta),   5 + (sinDelta),       20, 0, 2*M_PI);
            ctx->fill();


            // Adjust Rain Properties
            ctx->set_source_rgb(0.165, 0.556, 0.623);
            ctx->rotate(0.15);

            // Draw & Update RainDrops
            for(RainDrop &r : rain) {
                ctx->rectangle(r.pos.x, r.pos.y, r.width, r.height);
                r.pos.y += r.vel;
                ctx->fill();

                // Reset
                if(r.pos.y >= r.yDeadZone) {
                    r.pos.x = r.startPos.x;
                    r.pos.y = r.startPos.y;
                }
            }
            ctx->restore();



            // Tear Drop Speed MATHS
            if(tearSize <= .35) tearSize += 0.005;
            else {
                // Calculate Velocity & Displacement
                tearDisp += tearVel;
                tearVel += tearAcc;

                // Reset
                if(tearDisp > 2 * HEIGHT) {
                    tearDisp = tearVel = 0.0f;
                    tearSize = 0.01;
                }
            }
        }


        void draw(const CTX_REF& ctx, const int WIDTH, const int HEIGHT) {
            // PICK CORRESPONDING STATE INDEX
            switch (stateIndex)
            {
            case 0:
                drawTiredState(ctx, WIDTH, HEIGHT);
                break;
            case 1:
                drawSadState(ctx, WIDTH, HEIGHT);
                break;

            case 2:
                drawHappyState(ctx, WIDTH, HEIGHT);
                break;

            case 3:
                drawFuzzyState(ctx, WIDTH, HEIGHT);
                break;
            
            default:
                std::cout << "Something Went Wrong! State: " << stateIndex << '\n';
                break;
            }
        }
};


/**
 * Thread that listens to GPIO 0 pin for Press
 *  that will change the State of Mood :)
 */
#ifdef __arm__
void watchButton() {
    const int PIN = 0;      // GPIO 0
    bool clicked = false;   // To Simulate Press and Release

    // Setup WiringPI Library
    wiringPiSetup();
    pinMode(PIN, INPUT);

    while(true) {
        int val = digitalRead(PIN);

        if(!clicked && val) {
            clicked = true;

            // NOTE: Do stuff cause Clicked!
            stateIndex = (stateIndex + 1) % 4;
        }

        else if(clicked && !val) {
            clicked = false;
        }

        delay(100);
    }
}
#endif


int main(int argc, char *argv[]) {
    // START WINDOW + APP
    auto application = Gtk::Application::create(argc, argv, "org.gtkmm.sandbox.base");
    ChristmasApp app;
    MyWindow window(app);           // 640x480 Default Size Window

    // Watch Button Click in Thread
    #ifdef __arm__
    std::thread t1(watchButton);
    #endif

    // Run the Application
    return application->run(window);
}
