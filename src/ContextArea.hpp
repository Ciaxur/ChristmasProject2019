#include <gtkmm.h>
#include <chrono>

#define ENABLE_DEBUG_PRINTS 1        // DEBUG: Debug Prints

// BETTER READABILITY
#define GDK_IMAGE Glib::RefPtr<Gdk::Pixbuf>
#define CTX_REF Cairo::RefPtr<Cairo::Context>
#define CHRONO_HIGH_RES_CLOCK std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::nanoseconds>



class ContextArea: public Gtk::DrawingArea {
    private:
        GDK_IMAGE tiredFace_img, z1_img, z3_img;
        GDK_IMAGE imgTest;
        unsigned long long frameCount;


    protected:
        /**
         * Simple Wrapper for creating Image Buffer from Image Path
         * @param ctx - Cairo Drawing Context
         * @param path - Path to Image
         * @returns Image Reference Buffer
         */
        GDK_IMAGE createImageBuffer(std::string path) {
            return Gdk::Pixbuf::create_from_file(path);
        }
    
        /**
         * Draws Given Image from Path as large as the image
         *  is.
         * 
         * @param ctx - Cario Drawing Context
         * @param path - Image Path
         */
        void drawImage(const CTX_REF& ctx, GDK_IMAGE img) {
            Gdk::Cairo::set_source_pixbuf(ctx, img, 0, 0);
            ctx->rectangle(0, 0, img->get_width(), img->get_height());
            ctx->fill();
        }

        /**
         * Simple, Easy wrapper for Resizing Image
         * 
         * @param img - Reference to the Image that'll be resized
         * @param newWidth - New Width of Image
         * @param newHeight - New Height of Image
         * @return New GDK_IMAGE of Resized Image
         */
        GDK_IMAGE resizeImage(const GDK_IMAGE& img, int newWidth, int newHeight) {
            return img->scale_simple(newWidth, newHeight, Gdk::InterpType::INTERP_NEAREST);
        }
    


    private:
        /**
         * Keeps Track / Calculates Frames Per Second
         */
        CHRONO_HIGH_RES_CLOCK prevTime = std::chrono::high_resolution_clock::now();
        int elapsedFrames = 0;
        double FPS = 0.0;
        void calcFramesPerSecond() {
            // GET FPS
            auto now = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - prevTime);
            if (elapsed.count() >= 1) {     // 1 Second Elapsed
                prevTime = now;
                if(elapsedFrames != 0) {    // No Div by 0, end of the world!
                    FPS = elapsedFrames / elapsed.count();
                    elapsedFrames = 0;

                    // DEBUG: Prints
                    #if ENABLE_DEBUG_PRINTS
                        std::cout << "FPS [" << FPS << "]\n";
                    #endif
                }
            }
            elapsedFrames++;
        }
    
    public:
        ContextArea() {
            // Set "Draw Refresh Rate"      [10 = 60FPS], [33 = 30FPS]
            Glib::signal_timeout().connect(
                sigc::mem_fun(*this, &ContextArea::on_timeout),
                33
            );

            // ENABLE KEYPRESS EVENTS
            add_events(Gdk::KEY_RELEASE_MASK | Gdk::KEY_PRESS_MASK);
            signal_key_release_event().connect(
                sigc::mem_fun(*this, &ContextArea::onKeyRelease)
            );
            signal_key_press_event().connect(
                sigc::mem_fun(*this, &ContextArea::onKeyPress)
            );


            // SETUP VARIABLES
            frameCount = 0;
            
            // SETUP IMAGE VARIABLES
            tiredFace_img = createImageBuffer("./resources/Sleep-Emoji/64/FaceOnly.png");
            z1_img = createImageBuffer("./resources/Sleep-Emoji/128/Z1.png");
            z1_img = resizeImage(z1_img, 64, 64);
            z3_img = createImageBuffer("./resources/Sleep-Emoji/64/Z3.png");
        }


        
    // public: // DEBUG: Access from Window Key Press Events :)
        

    protected:
        
    
        /**
         * On Draw Function for Draw Area
         * 
         * @param ctx - Cairo Context
         */
        bool on_draw(const CTX_REF& ctx) override {
            // Keep Track of Window Dimensions
            Gtk::Allocation allocation = get_allocation();
            const int WIDTH = allocation.get_width();
            const int HEIGHT = allocation.get_height();
            
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

            
            
            
                        

            // COUNTER TRACK
            calcFramesPerSecond();
            frameCount++;
            return true;
        }

        
        /**
         * Key Release Event
         * @param event - GDK Event Key
         */
        bool onKeyRelease(GdkEventKey *event) {
            if(event->keyval == GDK_KEY_space) {
                printf("SPACE RELEASED\n");
            }
            
            return true;
        }

        /**
         * Key Press Event
         * @param event - GDK Event Key
         */
        bool onKeyPress(GdkEventKey *event) {
            if(event->keyval == GDK_KEY_space) {
                printf("SPACE PRESSED\n");
            }
            
            return true;
        }

        /**
         * Forces Draw Area to Refresh
         */
        bool on_timeout() {
            auto win = get_window();
            if(win)
                win->invalidate(false);
            return true;
        }
    
};