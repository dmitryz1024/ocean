#include "ocean.hpp"
#include <curses.h>

struct Ocean::Impl {
    int w, h;
    std::vector<std::shared_ptr<Entity>> grid;
    Impl(int width, int height) : w(width), h(height), grid(width * height) {}
};

Ocean::Ocean(int width, int height)
    : pimpl(std::make_unique<Impl>(width, height))
{}

Ocean::~Ocean() = default;

void Ocean::tick() {
    auto snapshot = pimpl->grid;
    for (auto& e : snapshot) {
        if (e) {
            e->tick(*this);
        }
    }
}

void Ocean::render() {
    erase();
    for (int y = 0; y < pimpl->h; ++y) {
        for (int x = 0; x < pimpl->w; ++x) {
            auto e = at(x, y);
            char ch;
            switch (e ? e->type() : Entity::Type::Sand) {
                case Entity::Type::Algae:    ch = 'A'; break;
                case Entity::Type::Herbivore: ch = 'H'; break;
                case Entity::Type::Predator:  ch = 'P'; break;
                default:                      ch = '~'; break;
            }
            mvaddch(y, x, ch);
        }
    }
    refresh();
}

std::shared_ptr<Entity> Ocean::at(int x, int y) const {
    if (x < 0 || y < 0 || x >= pimpl->w || y >= pimpl->h)
        return nullptr;
    return pimpl->grid[y * pimpl->w + x];
}

void Ocean::set(int x, int y, std::shared_ptr<Entity> e) {
    if (x < 0 || y < 0 || x >= pimpl->w || y >= pimpl->h)
        return;
    pimpl->grid[y * pimpl->w + x] = std::move(e);
}

int Ocean::width()  const { return pimpl->w; }
int Ocean::height() const { return pimpl->h; }