#include "ContextArea.hpp"

class MyWindow : public Gtk::Window {
    private:
        ContextArea *drawArea;
    
    public:
        MyWindow() {
            // Setup Properties
            set_default_size(640, 480);
            set_title("123FLOAT");

            // Drawing Area
            drawArea = new ContextArea();

            // Add Area
            add(*drawArea);
            drawArea->show();

            // SETUP EVENTS
            add_events(Gdk::KEY_PRESS_MASK);
        }

        virtual ~MyWindow() {
            delete drawArea;
        }
    
    private:
        bool on_key_press_event(GdkEventKey *event) {
            if(event->keyval == GDK_KEY_space) {
                std::cout << "KEY PRESS: SPACE\n";
            }

            else if(event->keyval == GDK_KEY_s) {
                std::cout << "KEY PRESS: S\n";
            }

            return true;
        }
};