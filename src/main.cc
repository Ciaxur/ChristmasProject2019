#include <iostream>

// GTK SANDBOX CLASSES
#include "./include/MyWindow.hpp"

// MATHS
#define _USE_MATH_DEFINES
#include <math.h>


class ChristmasApp: public ContextArea {
    public:
        ChristmasApp() {
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
        GDK_IMAGE tiredFace_img, z1_img, z3_img;
        GDK_IMAGE imgTest;

    private:    // DRAWING FUNCTIONS
        void setup() {
            // SETUP IMAGES
            tiredFace_img = createImageBuffer("./resources/Sleep-Emoji/64/FaceOnly.png");
            z1_img = createImageBuffer("./resources/Sleep-Emoji/128/Z1.png");
            z1_img = resizeImage(z1_img, 64, 64);
            z3_img = createImageBuffer("./resources/Sleep-Emoji/64/Z3.png");
        }


        void draw(const CTX_REF& ctx, const int WIDTH, const int HEIGHT) {
            // DRAW BACKGROUND
            ctx->set_source_rgb(0.1, 0.1, 0.1);
            ctx->rectangle(0, 0, WIDTH, HEIGHT);
            ctx->fill();

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
};



int main(int argc, char *argv[]) {
    // START WINDOW + APP
    auto application = Gtk::Application::create(argc, argv, "org.gtkmm.sandbox.base");
    ChristmasApp app;
    MyWindow window(app);

    // Run the Application
    return application->run(window);
}
