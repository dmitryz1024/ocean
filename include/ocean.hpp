#pragma once
#include <vector>
#include <memory>
#include "entity.hpp"

class Ocean {
public:
    Ocean(int width, int height);
    ~Ocean();
    Ocean(const Ocean&) = delete;
    Ocean& operator=(const Ocean&) = delete;

    void tick();
    void render();

    std::shared_ptr<Entity> at(int x, int y) const;
    void set(int x, int y, std::shared_ptr<Entity> e);

    int width() const;
    int height() const;

private:
    struct Impl;
    std::unique_ptr<Impl> pimpl;
};