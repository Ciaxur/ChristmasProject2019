#include <iostream>

// GTKMM CLASSES
#include "MyWindow.hpp"

// MATHS
#define _USE_MATH_DEFINES
#include <math.h>


int main(int argc, char *argv[]) {
    // START WINDOW + APP
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.sandbox.base");
    MyWindow window;

    // Run the Application
    return app->run(window);
}
