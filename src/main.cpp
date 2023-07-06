#include <TGUI/TGUI.hpp>
#include "../include/GUI/GUI.hpp"
#include "../include/model/Facade.hpp"

int main () {

    GUI app;
    Facade facade (app.getGui());
    app.init();
    facade.init_buttons();
    // app.init_buttons(&facade);
    app.start(facade.getg1_spr(), facade.getg2_spr());

    return 0;
}