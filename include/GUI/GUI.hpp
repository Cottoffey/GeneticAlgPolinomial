#ifndef GUI_H
#define GUI_H

#include <TGUI/TGUI.hpp>

class GUI {
private:
    sf::RenderWindow window;
    tgui::Gui        gui;

public:
    GUI ();

    void        init           ();
    // void        init_buttons   (Facade *);
    void        start          (sf::Sprite&, sf::Sprite&);
    tgui::Gui & getGui         ();
};

#endif