#include <iostream>

// VISUAL OBJECTS
#include "include/Stars.h"

// GTK SANDBOX CLASSES
#include "include/MyWindow.hpp"


// MATHS
#define _USE_MATH_DEFINES
#include <math.h>




class ChristmasApp: public ContextArea {
    public:
        ChristmasApp(): stars(150, 2, 40, 100) {
            std::cout << "Christmas 2019 Constructed!!\n";
            initContextArea();
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
        GDK_IMAGE   happyFace_img;
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


        // TODO: Currently working on this
        /**
         * HAPPY STATE
         */
        void drawHappyState(const CTX_REF& ctx, const int WIDTH, const int HEIGHT) {
            // DRAW BACKGROUND
            ctx->set_source_rgb(0.37, 0.68, 0.89);
            ctx->rectangle(0, 0, WIDTH, HEIGHT);
            ctx->fill();


            // HAPPY STATE
            ctx->save();
            ctx->set_source_rgb(1.0, 1.0, 1.0);
            ctx->select_font_face("Monospace", Cairo::FontSlant::FONT_SLANT_NORMAL, Cairo::FontWeight::FONT_WEIGHT_NORMAL);
            ctx->set_font_size(50.0);
            ctx->translate((WIDTH/2) - 80, HEIGHT/2);
            ctx->show_text("HAPPY");
            ctx->restore();

            // DRAW HAPPY FACE
            ctx->save();
            ctx->translate(0, 0);
            drawImage(ctx, happyFace_img);
            ctx->restore();

            // DRAW SUN 

            // DRAW CLOUDS
        }
        
        

        

        void draw(const CTX_REF& ctx, const int WIDTH, const int HEIGHT) {
            // drawTiredState(ctx, WIDTH, HEIGHT);
            drawHappyState(ctx, WIDTH, HEIGHT);
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
