#include "../../include/model/Facade.hpp"
#include <matplot/matplot.h>
#include <thread>
#include <wait.h>

Facade::Facade(tgui::Gui & _g) : gui(_g), parent_selection(NULL), recombination(new IntermediateRecombination), is_solver_init(false), stats(0)
{
    h = matplot::figure(true);
}

Facade::~Facade()
{
    delete recombination;
    if (parent_selection != NULL)
        delete parent_selection;
}

void Facade::updateStatsLabels()
{
    gui.get<tgui::Label>("generation")->setText(tgui::String(current_generation));

    gui.get<tgui::Label>("current_min")->setText(tgui::String (stats[0].best_individ[0]) + "\n" + tgui::String(config.calculatePolinom(stats[0].best_individ[0])));
    gui.get<tgui::Label>("current_max")->setText(tgui::String (stats[0].best_individ[1]) + "\n" + tgui::String(config.calculatePolinom(stats[0].best_individ[1])));
    gui.get<tgui::Label>("next1_min")  ->setText(tgui::String (stats[1].best_individ[0]) + "\n" + tgui::String(config.calculatePolinom(stats[1].best_individ[0])));
    gui.get<tgui::Label>("next1_max")  ->setText(tgui::String (stats[1].best_individ[1]) + "\n" + tgui::String(config.calculatePolinom(stats[1].best_individ[1])));
    gui.get<tgui::Label>("next2_min")  ->setText(tgui::String (stats[2].best_individ[0]) + "\n" + tgui::String(config.calculatePolinom(stats[2].best_individ[0])));
    gui.get<tgui::Label>("next2_max")  ->setText(tgui::String (stats[2].best_individ[1]) + "\n" + tgui::String(config.calculatePolinom(stats[2].best_individ[1])));
}

void Facade::updateGraphs()
{

    // polinom
    h->ioff();
    double min, max;
    config.getRange(&min, &max);

    std::vector<double> x = matplot::linspace(min, max);
    matplot::plot(x, config.calculatePolinom(x));
    matplot::hold(true);
    matplot::grid(true);

    // individuals
    x = stats[0].found_mins;
    matplot::plot(x, config.calculatePolinom(x), "ro");
    x = stats[0].found_maxs;
    matplot::plot(x, config.calculatePolinom(x), "bo");

    while (!h->save("graph1.png")) {}
    matplot::hold(false);

    // Metric function
    std::vector<double> inds;
    for (int i = 1; i <= number_of_generations; i++)
        inds.push_back(i);

    matplot::plot(inds, g_data.solutions, "b-o");
    matplot::hold(true);
    matplot::plot(inds, g_data.average_solutions, "r-x");

    while (!h->save("graph2.png")) {}
    matplot::hold(false);

    while (!g_data.g1_tx.loadFromFile("graph1.png"))
    {
    }
    while (!g_data.g2_tx.loadFromFile("graph2.png"))
    {
    }

    // Drawing
    g_data.g1_spr.setTexture(g_data.g1_tx);
    // g_data.g1_spr.setScale (573. / g_data.g1_tx.getSize().x, 430. / g_data.g1_tx.getSize().y);
    g_data.g2_spr.setTexture(g_data.g2_tx);
    // g_data.g2_spr.setScale (573. / g_data.g2_tx.getSize().x, 430. / g_data.g2_tx.getSize().y);
    g_data.g2_spr.setPosition(600, 0);

}

void Facade::start_button()
{

    /* Generating config */

    // Range

    tgui::EditBox::Ptr range_min = gui.get<tgui::EditBox>("range_min");
    tgui::EditBox::Ptr range_max = gui.get<tgui::EditBox>("range_max");

    double min = range_min->getText().toFloat();
    double max = range_max->getText().toFloat();

    if (min >= max)
    {
        range_min->getRenderer()->setBorderColor(tgui::Color::Red);
        range_max->getRenderer()->setBorderColor(tgui::Color::Red);
        return;
    }
    else
    {
        range_min->getRenderer()->setBorderColor(tgui::Color::Black);
        range_max->getRenderer()->setBorderColor(tgui::Color::Black);
    }

    config.setRange(min, max);


    // Polinomial parametrs

    std::vector<double> par;
    for (int i = 0; i < 11; i++)
    {
        par.push_back(gui.get<tgui::EditBox>(tgui::String(i))->getText().toFloat(0));
    }
    config.setPolinomialParametrs(par);

    // Number of individuals

    config.setIndividualsNumber(gui.get<tgui::ComboBox>("number_of_individuals")->getSelectedItem().toInt());

    // Number of generations

    number_of_generations = gui.get<tgui::ComboBox>("number_of_generations")->getSelectedItem().toInt();

    // Mutation parametrs

    config.setMutationParametrs(gui.get<tgui::ListBox>("mutation_parametr")->getSelectedItem().toInt(),
                                gui.get<tgui::ListBox>("mutation_probability")->getSelectedItem().toFloat() / 100);

    // Parent selection and recombination

    if (parent_selection != NULL)
        delete parent_selection;

    tgui::String ps = gui.get<tgui::ComboBox>("parent_selection")->getSelectedItem();
    if (ps == "Panmixia")
        parent_selection = new Panmixia;
    else if (ps == "Inbreeding")
        parent_selection = new Inbreeding;
    else if (ps == "Outbreeding")
        parent_selection = new Outbreeding;

    config.setParentSelection(parent_selection);
    config.setRecombination(recombination);

    // Solver initialization

    solver.init(&config);
    is_solver_init = true;


    /* Update stats */

    g_data.average_solutions.clear();
    g_data.solutions.clear();

    // Update steps
    current_generation = 1;
    gui.get<tgui::Label>("generation")->setText("1");

    // Getting stats
    stats.clear();

    struct Generation_stats tmp;
    tmp.found_mins = solver.getGensMin();
    tmp.found_maxs = solver.getGensMax();
    tmp.best_individ = solver.getBestIndivid();
    tmp.average_adaptability = solver.getAverageAdaptability();

    stats.push_back(tmp);

    for (int i = 0; i < 2; i++)
    {
        solver.calculateStep();
        tmp.found_mins = solver.getGensMin();
        tmp.found_maxs = solver.getGensMax();
        tmp.best_individ = solver.getBestIndivid();
        tmp.average_adaptability = solver.getAverageAdaptability();
        stats.push_back(tmp);
    }

    g_data.solutions.push_back(config.calculatePolinom(stats[0].best_individ[1]) - config.calculatePolinom(stats[0].best_individ[0]));
    g_data.average_solutions.push_back(stats[0].average_adaptability);

    g_data.solutions.push_back(config.calculatePolinom(stats[1].best_individ[1]) - config.calculatePolinom(stats[1].best_individ[0]));
    g_data.average_solutions.push_back(stats[1].average_adaptability);

    // Update labels
    updateStatsLabels();

    // Update graphs
    updateGraphs();
}

void disableButtons (tgui::Gui & gui, bool flag) 
{
    gui.get<tgui::Button>("start")->setEnabled (flag);
    gui.get<tgui::Button>("next")-> setEnabled (flag);
    gui.get<tgui::Button>("skip")->setEnabled (flag);
}

void Facade::next_button(bool update)
{

    // Calculate step and update stats

    if (current_generation == number_of_generations)
        return;
    
    stats.erase(stats.begin());

    struct Generation_stats tmp;

    solver.calculateStep();

    tmp.found_mins = solver.getGensMin();
    tmp.found_maxs = solver.getGensMax();
    tmp.best_individ = solver.getBestIndivid();
    tmp.average_adaptability = solver.getAverageAdaptability();

    stats.push_back(tmp);

    current_generation += 1;

    g_data.average_solutions.push_back(stats[1].average_adaptability);
    g_data.solutions.push_back(config.calculatePolinom(stats[1].best_individ[1]) - config.calculatePolinom(stats[1].best_individ[0]));

    if (update)
    {
        updateStatsLabels();
        updateGraphs();
    }
}

void Facade::calculatingSkip ()
{
    disableButtons (gui, false);

    tgui::ProgressBar::Ptr progress = gui.get<tgui::ProgressBar> ("progress");
    progress->setVisible (true);
    progress->setValue (0);

    while (current_generation != number_of_generations) 
    {
        next_button (false);
        progress->setValue (current_generation * 100 / number_of_generations);
    }

    updateStatsLabels();
    updateGraphs();

    disableButtons (gui, true);
}


void Facade::skip_button () 
{
    if (current_generation == number_of_generations)
        return;
    std::thread thrd (&Facade::calculatingSkip, this);
    thrd.detach();
}


void Facade::init_buttons()
{
    gui.get<tgui::Button>("start")->onPress(&Facade::start_button, this);
    gui.get<tgui::Button>("next")->onPress(&Facade::next_button, this, true);
    gui.get<tgui::Button>("skip")->onPress(&Facade::skip_button, this);
}


sf::Sprite & Facade::getg1_spr () {
    return g_data.g1_spr;
}

sf::Sprite & Facade::getg2_spr () {
    return g_data.g2_spr;
}