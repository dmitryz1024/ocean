#include "predator.hpp"
#include "ocean.hpp"
#include "utils/logger.hpp"
#include "utils/random.hpp"
#include <vector>

class PredatorFish::Impl {
public:
    int hunger = 0;
};

PredatorFish::PredatorFish(int x, int y)
    : Entity(x, y, 120)
    , pimpl(std::make_unique<Impl>())
{}

PredatorFish::PredatorFish(const PredatorFish& o)
    : Entity(o._x, o._y, o._lifespan)
    , pimpl(std::make_unique<Impl>(*o.pimpl))
{}

PredatorFish::PredatorFish(PredatorFish&&) noexcept = default;

PredatorFish& PredatorFish::operator=(const PredatorFish& o) {
    if (this!=&o) {
        _x = o._x; _y = o._y; _lifespan = o._lifespan;
        pimpl = std::make_unique<Impl>(*o.pimpl);
    }
    return *this;
}

PredatorFish& PredatorFish::operator=(PredatorFish&&) noexcept = default;

PredatorFish::~PredatorFish() = default;

void PredatorFish::tick(Ocean& ocean) {
    _age++; ++pimpl->hunger;
    if (_age>=_lifespan || pimpl->hunger>30) {
        ocean.set(_x,_y,nullptr);
        Logger<PredatorFish>::log(std::string("Died at ")+std::to_string(_x)+","+std::to_string(_y));
        return;
    }

    for (int dx=-1; dx<=1; ++dx) for (int dy=-1; dy<=1; ++dy) {
        int nx=_x+dx, ny=_y+dy;
        if (nx<0||ny<0||nx>=ocean.width()||ny>=ocean.height()) continue;
        auto e = ocean.at(nx, ny);
        if (e && e->type()==Type::Herbivore) {
            ocean.set(_x,_y,nullptr);
            ocean.set(nx,ny, std::make_shared<PredatorFish>(nx,ny));
            pimpl->hunger = 0;
            Logger<PredatorFish>::log(std::string("Ate fish at ")+std::to_string(nx)+","+std::to_string(ny));
            return;
        }
    }
    
    std::vector<std::pair<int,int>> empties;
    for (int dx=-1; dx<=1; ++dx) for (int dy=-1; dy<=1; ++dy) {
        if (dx==0 && dy==0) continue;
        int nx=_x+dx, ny=_y+dy;
        if (nx<0||ny<0||nx>=ocean.width()||ny>=ocean.height()) continue;
        if (!ocean.at(nx,ny)) empties.emplace_back(nx,ny);
    }
    if (!empties.empty()) {
        auto& rng = global_rng();
        std::uniform_int_distribution<> dist(0, (int)empties.size()-1);
        auto [nx,ny] = empties[dist(rng)];
        ocean.set(_x,_y,nullptr);
        ocean.set(nx,ny, std::make_shared<PredatorFish>(nx,ny));
        Logger<PredatorFish>::log(std::string("Moved to ")+std::to_string(nx)+","+std::to_string(ny));
    }
}

Entity::Type PredatorFish::type() const {
    return Entity::Type::Predator;
}