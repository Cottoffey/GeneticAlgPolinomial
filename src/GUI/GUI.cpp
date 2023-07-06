#include "../../include/GUI/GUI.hpp"
#include <vector>
#define TEXT_SIZE_14 14 * 93 / 72
#define TEXT_SIZE_12 12 * 93 / 72
#define TEXT_SIZE_18 18 * 93 / 72

GUI::GUI() : window(sf::VideoMode(1200, 800), "Polinomial Solver"), gui(window) {}

void GUI::init()
{

    /*--------------
         Input
    --------------*/

    /* Polinomial pars */

    auto polinomial_pars_l = tgui::Label::create("Polinomial parametrs");
    polinomial_pars_l->setPosition(230, 480);
    polinomial_pars_l->setTextSize(TEXT_SIZE_14);
    gui.add(polinomial_pars_l);

    auto x_l = tgui::Label::create("x10\t  x9\t  x8\t  x7\t  x6\t  x5\t  x4\t  x3\t  x2\t  x1\t  x0");
    x_l->setPosition(40, 520);
    x_l->setTextSize(TEXT_SIZE_14);
    gui.add(x_l);

    std::vector<tgui::EditBox::Ptr> pars(11);
    for (int i = 0; i < 11; i++)
    {
        pars[i] = tgui::EditBox::create();
        pars[i]->setPosition(620 - i * 59, 550);
        pars[i]->setSize(45, 25);
        pars[i]->setInputValidator(tgui::EditBox::Validator::Float);
        gui.add(pars[i], tgui::String(i));
    }

    /* Algorithm parametrs */

    // Range
    auto range_l = tgui::Label::create("Range");
    range_l->setPosition(55, 625);
    range_l->setTextSize(TEXT_SIZE_14);
    gui.add(range_l, "range");

    auto range_min = tgui::EditBox::create();
    auto range_max = tgui::EditBox::create();
    range_min->setTextSize(TEXT_SIZE_14);
    range_max->setTextSize(TEXT_SIZE_14);
    range_min->setSize(70, 30);
    range_max->setSize(70, 30);
    range_min->setPosition(170, 620);
    range_max->setPosition(250, 620);
    range_min->setInputValidator(tgui::EditBox::Validator::Float);
    range_min->setInputValidator(tgui::EditBox::Validator::Float);
    gui.add(range_min, "range_min");
    gui.add(range_max, "range_max");

    // Number of individuals
    auto ni_l = tgui::Label::create("Number of\nindividuals");
    ni_l->setPosition(55, 675);
    ni_l->setTextSize(TEXT_SIZE_14);
    gui.add(ni_l);

    auto ni_lb = tgui::ComboBox::create();
    ni_lb->setPosition(200, 680);
    ni_lb->setSize(120, 30);
    ni_lb->setTextSize(TEXT_SIZE_14);
    ni_lb->addItem("10");
    ni_lb->addItem("20");
    ni_lb->addItem("50");
    ni_lb->addItem("100");
    ni_lb->addItem("200");
    ni_lb->addItem("500");
    ni_lb->addItem("1000");
    ni_lb->addItem("5000");
    ni_lb->setSelectedItem("10");
    gui.add(ni_lb, "number_of_individuals");

    // Number of generations
    auto ng_l = tgui::Label::create("Number of\ngenerations");
    ng_l->setPosition(55, 725);
    ng_l->setTextSize(TEXT_SIZE_14);
    gui.add(ng_l);

    auto ng_lb = tgui::ComboBox::create();
    ng_lb->setPosition(200, 730);
    ng_lb->setSize(120, 30);
    ng_lb->setTextSize(TEXT_SIZE_14);
    ng_lb->addItem("10");
    ng_lb->addItem("20");
    ng_lb->addItem("50");
    ng_lb->addItem("100");
    ng_lb->addItem("200");
    ng_lb->addItem("500");
    ng_lb->addItem("1000");
    ng_lb->addItem("5000");
    ng_lb->setSelectedItem("10");
    gui.add(ng_lb, "number_of_generations");

    // Mutation parametr
    auto mp_l = tgui::Label::create("Mutation\nparametr");
    mp_l->setPosition(350, 615);
    mp_l->setTextSize(TEXT_SIZE_14);
    gui.add(mp_l);

    auto mp_s = tgui::ListBox::create();
    mp_s->getRenderer()->setSelectedBackgroundColor(tgui::Color(230, 230, 230));
    mp_s->getRenderer()->setSelectedBackgroundColorHover(tgui::Color(220, 220, 220));
    mp_s->getRenderer()->setSelectedTextColor(tgui::Color(60, 60, 60));
    mp_s->setPosition(500, 620);
    mp_s->setSize(120, 30);
    mp_s->setTextSize(TEXT_SIZE_14);
    mp_s->setItemHeight(30);
    for (int i = 2; i < 31; i++)
        mp_s->addItem(tgui::String::fromNumber(i));
    mp_s->setSelectedItem("20");
    gui.add(mp_s, "mutation_parametr");

    // Mutation probability
    auto mpr_l = tgui::Label::create("Mutation\nprobability");
    mpr_l->setPosition(350, 675);
    mpr_l->setTextSize(TEXT_SIZE_14);
    gui.add(mpr_l);

    auto mpr_s = tgui::ListBox::create();
    mpr_s->getRenderer()->setSelectedBackgroundColor(tgui::Color(230, 230, 230));
    mpr_s->getRenderer()->setSelectedBackgroundColorHover(tgui::Color(220, 220, 220));
    mpr_s->getRenderer()->setSelectedTextColor(tgui::Color(60, 60, 60));
    mpr_s->setPosition(500, 680);
    mpr_s->setSize(120, 30);
    mpr_s->setTextSize(TEXT_SIZE_14);
    mpr_s->setItemHeight(30);
    for (double i = 0.5; i < 50; i += 0.5)
        mpr_s->addItem(tgui::String::fromNumber(i));
    mpr_s->setSelectedItem("1");
    gui.add(mpr_s, "mutation_probability");

    // Parent selection
    auto ps_l = tgui::Label::create("Parent\nselection");
    ps_l->setPosition(350, 725);
    ps_l->setTextSize(TEXT_SIZE_14);
    gui.add(ps_l);

    auto ps_lb = tgui::ComboBox::create();
    ps_lb->setPosition(500, 730);
    ps_lb->setSize(150, 30);
    ps_lb->setTextSize(TEXT_SIZE_14);
    ps_lb->addItem("Panmixia");
    ps_lb->addItem("Inbreeding");
    ps_lb->addItem("Outbreeding");
    ps_lb->setSelectedItem("Panmixia");
    gui.add(ps_lb, "parent_selection");


    /*---------------
      Visualisation
    ----------------*/

    // Steps
    auto steps_l = tgui::Label::create("Generation");
    steps_l->setSize(200, 50);
    steps_l->setPosition(850, 500);
    steps_l->setTextSize(TEXT_SIZE_18);
    steps_l->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Right);
    gui.add(steps_l);

    auto steps_nl = tgui::Label::create("0");
    steps_nl->setSize(100, 50);
    steps_nl->setPosition(1050, 500);
    steps_nl->setTextSize(TEXT_SIZE_18);
    steps_nl->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Right);
    gui.add(steps_nl, "generation");

    // Solutions
    auto cur_l = tgui::Label::create("Current");
    cur_l->setSize(117, 50);
    cur_l->setPosition(800, 550);
    cur_l->setTextSize(TEXT_SIZE_14);
    cur_l->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Right);
    gui.add(cur_l);

    auto next1_l = tgui::Label::create("Next");
    next1_l->setSize(117, 50);
    next1_l->setPosition(917, 550);
    next1_l->setTextSize(TEXT_SIZE_14);
    next1_l->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Right);
    gui.add(next1_l);

    auto next2_l = tgui::Label::create("Next");
    next2_l->setSize(117, 50);
    next2_l->setPosition(1043, 550);
    next2_l->setTextSize(TEXT_SIZE_14);
    next2_l->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Right);
    gui.add(next2_l);

    auto min_l = tgui::Label::create("min");
    min_l->setSize(50, 50);
    min_l->setPosition(750, 600);
    min_l->setTextSize(TEXT_SIZE_14);
    min_l->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
    gui.add(min_l);

    auto max_l = tgui::Label::create("max");
    max_l->setSize(50, 50);
    max_l->setPosition(750, 650);
    max_l->setTextSize(TEXT_SIZE_14);
    max_l->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
    gui.add(max_l);

    auto cur_min = tgui::Label::create("0\n0");
    cur_min->setSize(117, 50);
    cur_min->setPosition(800, 600);
    cur_min->setTextSize(TEXT_SIZE_12);
    cur_min->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Right);
    gui.add(cur_min, "current_min");

    auto cur_max = tgui::Label::create("0\n0");
    cur_max->setSize(117, 50);
    cur_max->setPosition(800, 650);
    cur_max->setTextSize(TEXT_SIZE_12);
    cur_max->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Right);
    gui.add(cur_max, "current_max");

    auto next1_min = tgui::Label::create("0\n0");
    next1_min->setSize(117, 50);
    next1_min->setPosition(917, 600);
    next1_min->setTextSize(TEXT_SIZE_12);
    next1_min->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Right);
    gui.add(next1_min, "next1_min");

    auto next1_max = tgui::Label::create("0\n0");
    next1_max->setSize(117, 50);
    next1_max->setPosition(917, 650);
    next1_max->setTextSize(TEXT_SIZE_12);
    next1_max->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Right);
    gui.add(next1_max, "next1_max");

    auto next2_min = tgui::Label::create("0\n0");
    next2_min->setSize(117, 50);
    next2_min->setPosition(1034, 600);
    next2_min->setTextSize(TEXT_SIZE_12);
    next2_min->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Right);
    gui.add(next2_min, "next2_min");

    auto next2_max = tgui::Label::create("0\n0");
    next2_max->setSize(117, 50);
    next2_max->setPosition(1034, 650);
    next2_max->setTextSize(TEXT_SIZE_12);
    next2_max->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Right);
    gui.add(next2_max, "next2_max");


    // Progress bar 
    auto progress = tgui::ProgressBar::create ();
    progress->getRenderer()->setFillColor (tgui::Color (163, 207, 175));
    progress->setPosition (700, 500);
    progress->setSize (200, 30);
    progress->setValue (0);
    gui.add (progress, "progress");

    /* Buttons */

    // Start
    auto start_b = tgui::Button::create("Start");
    start_b->setSize(100, 50);
    start_b->setPosition(750, 720);
    start_b->setTextSize(TEXT_SIZE_14);
    gui.add(start_b, "start");

    // Next
    auto next_b = tgui::Button::create("Next");
    next_b->setSize(100, 50);
    next_b->setPosition(900, 720);
    next_b->setTextSize(TEXT_SIZE_14);
    gui.add(next_b, "next");

    // Skip
    auto skip_b = tgui::Button::create("Skip");
    skip_b->setSize(100, 50);
    skip_b->setPosition(1050, 720);
    skip_b->setTextSize(TEXT_SIZE_14);
    gui.add(skip_b, "skip");

    /* Graphs */

    auto graph = tgui::Canvas::create({1200, 470});
    graph->clear(tgui::Color(240, 240, 240));
    graph->display();
    gui.add(graph, "graph");
}

void GUI::start(sf::Sprite& g1, sf::Sprite& g2)
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            gui.handleEvent(event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear({240, 240, 240});
        auto graph = gui.get<tgui::Canvas> ("graph");
        graph->clear(tgui::Color(240, 240, 240));
        graph->draw(g1);
        graph->draw(g2);
        graph->display();
        gui.draw();
        window.display();
        sf::sleep (sf::seconds (0.01));
    }
}

tgui::Gui &GUI::getGui()
{
    return gui;
}
