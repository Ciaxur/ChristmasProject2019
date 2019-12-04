#include <iostream>

// VISUAL OBJECTS
#include "include/Stars.h"

// GTK SANDBOX CLASSES
#include "include/MyWindow.h"


// MATHS
#define _USE_MATH_DEFINES
#include <math.h>




class ChristmasApp: public ContextArea {
    public:
        ChristmasApp(): stars(150, 2, 40, 100) {
            std::cout << "Christmas 2019 Constructed!!\n";
            initContextArea(TARGET_FPS::THIRTY);
        }
    

    private:    // KEYBOARD EVENTS
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

        
    private:    // Variables Used
        GDK_IMAGE   tiredFace_img, z1_img, z3_img;
        GDK_IMAGE   happyFace_img, sunFace_img, sunRims_img;
        Stars       stars;                              // Initiated in ChristmasApp Contructor
        

    private:    // DRAWING FUNCTIONS
        void setup() {
            // SETUP IMAGES
            #ifdef __arm__      // Different Path for my Raspberry PI
            tiredFace_img = createImageBuffer( "/home/pi/Downloads/ChristmasProject2019/resources/Sleep-Emoji/64/FaceOnly.png" );
            z1_img = createImageBuffer( "/home/pi/Downloads/ChristmasProject2019/resources/Sleep-Emoji/128/Z1.png" );
            z3_img = createImageBuffer( "/home/pi/Downloads/ChristmasProject2019/resources/Sleep-Emoji/64/Z3.png" );

            #else
            tiredFace_img = createImageBuffer( "resources/Sleep-Emoji/64/FaceOnly.png" );
            z1_img = createImageBuffer( "resources/Sleep-Emoji/128/Z1.png" );
            z3_img = createImageBuffer( "resources/Sleep-Emoji/64/Z3.png" );

            happyFace_img = createImageBuffer( "resources/Happy_Emoji/128/Smile_Face.png" );
            sunFace_img = createImageBuffer( "resources/Sun-Emoji/128/Sun-Face.png" );
            sunRims_img = createImageBuffer( "resources/Sun-Emoji/128/Sun-Rims.png" );
            

            #endif
            
            // IMAGE MODIFICATION
            z1_img = resizeImage(z1_img, 64, 64);
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
            

            // TIRED STATE
            ctx->save();
            ctx->set_source_rgb(1.0, 1.0, 1.0);
            ctx->select_font_face("Monospace", Cairo::FontSlant::FONT_SLANT_NORMAL, Cairo::FontWeight::FONT_WEIGHT_NORMAL);
            ctx->set_font_size(50.0);
            ctx->translate((WIDTH/2) - 80, HEIGHT/2);
            ctx->show_text("TIRED");
            ctx->restore();

            // DRAW TIRED FACE
            ctx->save();
            
            ctx->translate((WIDTH/2) + 80, (HEIGHT/2) + 20);
            drawImage(ctx, tiredFace_img);


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
        

        // NOTE: Currently Working ON
        /**
         * SAD STATE
         */
        void drawSadState(const CTX_REF& ctx, const int WIDTH, const int HEIGHT) {
            // DRAW BACKGROUND
            ctx->set_source_rgb(0.204, 0.250, 0.2588);
            ctx->rectangle(0, 0, WIDTH, HEIGHT);
            ctx->fill();


        }

        

        void draw(const CTX_REF& ctx, const int WIDTH, const int HEIGHT) {
            // drawTiredState(ctx, WIDTH, HEIGHT);
            // drawHappyState(ctx, WIDTH, HEIGHT);
            drawSadState(ctx, WIDTH, HEIGHT);
        }
};



int main(int argc, char *argv[]) {
    // START WINDOW + APP
    auto application = Gtk::Application::create(argc, argv, "org.gtkmm.sandbox.base");
    ChristmasApp app;
    MyWindow window(app);           // 640x480 Default Size Window

    // Run the Application
    return application->run(window);
}
