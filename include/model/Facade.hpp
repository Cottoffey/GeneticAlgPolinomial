#ifndef FACADE_H
#define FACADE_H

#include <TGUI/TGUI.hpp>
#include "Solver.hpp"
#include "../GUI/GUI.hpp"
#include <matplot/matplot.h>

class Facade {
private:

    struct Generation_stats {
        std::vector<double> found_mins;
        std::vector<double> found_maxs;
        std::vector<double> best_individ;
        double              average_adaptability;
    };

    struct Graph_data {
        std::vector<double> solutions;
        std::vector<double> average_solutions;
        sf::Texture         g1_tx;
        sf::Sprite          g1_spr;
        sf::Texture         g2_tx;
        sf::Sprite          g2_spr;
    };

    AlgConfig config;
    Solver    solver;

    IParentSelection* parent_selection;
    IRecombination*   recombination;

    int current_generation;
    int number_of_generations;
    bool is_solver_init;

    std::vector<struct Generation_stats> stats;
    struct Graph_data                    g_data;
    matplot::figure_handle               h; // matplot figure for drawing

    tgui::Gui &gui;

    void calculatingSkip ();

public:

    Facade(tgui::Gui & gui);
    ~Facade();

    void start_button   ();
    void next_button    (bool update);
    void skip_button ();

    void init_buttons ();

    void updateStatsLabels  ();
    void updateGraphs       ();

    sf::Sprite & getg1_spr ();
    sf::Sprite & getg2_spr ();
};

#endif