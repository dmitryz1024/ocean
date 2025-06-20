#include "algae.hpp"
#include "ocean.hpp"
#include "utils/logger.hpp"
#include "utils/random.hpp"
#include <vector>
#include <memory>
#include <random>

Algae::Algae(int x, int y)
    : Entity(x, y, 50)
{}

Algae::~Algae() = default;

void Algae::tick(Ocean& ocean) {
    _age++;
    if (_age >= _lifespan) {
        ocean.set(_x, _y, nullptr);
        Logger<Algae>::log("Died at " + std::to_string(_x) + "," + std::to_string(_y));
        return;
    }

    auto& rng = global_rng();
    std::uniform_real_distribution<> chance(0.0, 1.0);
    if (chance(rng) > 0.025)
        return;

    std::vector<std::pair<int,int>> empties;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            int nx = _x + dx, ny = _y + dy;
            if (nx < 0 || ny < 0 || nx >= ocean.width() || ny >= ocean.height()) continue;
            if (!ocean.at(nx, ny))
                empties.emplace_back(nx, ny);
        }
    }

    if (!empties.empty()) {
        std::uniform_int_distribution<> dist(0, (int)empties.size() - 1);
        auto [nx, ny] = empties[dist(rng)];
        ocean.set(nx, ny, std::make_shared<Algae>(nx, ny));
        Logger<Algae>::log("Spread to " + std::to_string(nx) + "," + std::to_string(ny));
    }
}

Entity::Type Algae::type() const {
    return Entity::Type::Algae;
}