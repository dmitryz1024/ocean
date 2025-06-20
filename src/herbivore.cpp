#include "herbivore.hpp"
#include "ocean.hpp"
#include "utils/logger.hpp"
#include "utils/random.hpp"
#include <vector>

HerbivoreFish::HerbivoreFish(int x, int y)
    : Entity(x, y, 100), _hunger(0)
{}

HerbivoreFish::HerbivoreFish(const HerbivoreFish& o) = default;
HerbivoreFish::HerbivoreFish(HerbivoreFish&& o) noexcept = default;
HerbivoreFish& HerbivoreFish::operator=(const HerbivoreFish& o) = default;
HerbivoreFish& HerbivoreFish::operator=(HerbivoreFish&& o) noexcept = default;
HerbivoreFish::~HerbivoreFish() = default;

void HerbivoreFish::tick(Ocean& ocean) {
    _age++; _hunger++;
    if (_age>=_lifespan || _hunger>20) {
        ocean.set(_x,_y,nullptr);
        Logger<HerbivoreFish>::log(std::string("Died at ") + std::to_string(_x)+","+std::to_string(_y));
        return;
    }

    for (int dx=-1; dx<=1; ++dx) for (int dy=-1; dy<=1; ++dy) {
        int nx=_x+dx, ny=_y+dy;
        if (nx<0||ny<0||nx>=ocean.width()||ny>=ocean.height()) continue;
        auto e=ocean.at(nx,ny);
        if (e && e->type()==Type::Algae) {
            ocean.set(_x,_y,nullptr);
            ocean.set(nx,ny, std::make_shared<HerbivoreFish>(nx,ny));
            _hunger=0;
            Logger<HerbivoreFish>::log(std::string("Ate algae at ")+std::to_string(nx)+","+std::to_string(ny));
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
        ocean.set(nx,ny, std::make_shared<HerbivoreFish>(nx,ny));
        Logger<HerbivoreFish>::log(std::string("Moved to ") + std::to_string(nx)+","+std::to_string(ny));
    }
}

Entity::Type HerbivoreFish::type() const {
    return Entity::Type::Herbivore;
}