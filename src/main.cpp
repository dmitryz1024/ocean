#include "ocean.hpp"
#include "algae.hpp"
#include "herbivore.hpp"
#include "predator.hpp"
#include "utils/random.hpp"
#include <memory>
#include <chrono>
#include <thread>
#include <curses.h>
#include <vector>

template<typename Factory>
void place_random(Ocean& ocean, Factory factory, int count) {
    auto& rng = global_rng();
    std::uniform_int_distribution<> dx(0, ocean.width() - 1);
    std::uniform_int_distribution<> dy(0, ocean.height() - 1);

    int placed = 0;
    int attempts = 0;
    const int max_attempts = count * 10;

    while (placed < count && attempts < max_attempts) {
        ++attempts;
        int x = dx(rng), y = dy(rng);
        if (!ocean.at(x, y)) {
            ocean.set(x, y, factory(x, y));
            ++placed;
        }
    }
}

int main() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);

    int term_h = 0, term_w = 0;
    getmaxyx(stdscr, term_h, term_w);
    Ocean ocean(term_w, term_h);

    place_random(ocean,
        [](int x, int y){ return std::make_shared<Algae>(x, y); },
        50
    );
    place_random(ocean,
        [](int x, int y){ return std::make_shared<HerbivoreFish>(x, y); },
        20
    );
    place_random(ocean,
        [](int x, int y){ return std::make_shared<PredatorFish>(x, y); },
        10
    );

    try {
        while (true) {
            int ch = getch();
            if (ch == 'q' || ch == 'Q') break;

            ocean.tick();
            ocean.render();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    } catch (...) {
        endwin();
        throw;
    }

    endwin();
    return 0;
}