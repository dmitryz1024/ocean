#pragma once
#include "entity.hpp"

class PredatorFish : public Entity {
public:
    explicit PredatorFish(int x, int y);
    PredatorFish(const PredatorFish&);
    PredatorFish(PredatorFish&&) noexcept;
    PredatorFish& operator=(const PredatorFish&);
    PredatorFish& operator=(PredatorFish&&) noexcept;
    ~PredatorFish() override;
    void tick(Ocean& ocean) override;
    Type type() const override;
    static const char* name() noexcept { return "PredatorFish"; }
private:
    class Impl;
    std::unique_ptr<Impl> pimpl;
};