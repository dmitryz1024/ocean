#pragma once
#include "entity.hpp"

class Algae : public Entity {
public:
    Algae(int x, int y);
    ~Algae() override;
    void tick(Ocean& ocean) override;
    Type type() const override;
    static const char* name() noexcept { return "Algae"; }
};
