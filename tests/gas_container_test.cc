#include <catch2/catch.hpp>

#include <gas_container.h>

using idealgas::GasContainer;

TEST_CASE("Wall collusion tests") {
    SECTION("Particle collides with left vertical wall") {
        GasContainer container = GasContainer(10, 20,std::vector<idealgas::Particle>
                {idealgas::Particle(vec2(101, 105), vec2(-1,0), 1)});
        container.AdvanceOneFrame();
        REQUIRE(container.GetParticle()[0].GetVelocity().x == 1);
        REQUIRE(container.GetParticle()[0].GetPosition().x == 102);
    }
    SECTION("Particle collides with right vertical wall") {
        GasContainer container = GasContainer(10, 20, std::vector<idealgas::Particle>
                {idealgas::Particle(vec2(109, 105), vec2(1,0), 1)});
        container.AdvanceOneFrame();
        REQUIRE(container.GetParticle()[0].GetVelocity().x == -1);
        REQUIRE(container.GetParticle()[0].GetPosition().x == 108);
    }

    SECTION("Particle collides with top horizontal wall") {
        GasContainer container = GasContainer(10, 20, std::vector<idealgas::Particle>
                {idealgas::Particle(vec2(105, 101), vec2(0,-1), 1)});
        container.AdvanceOneFrame();
        REQUIRE(container.GetParticle()[0].GetVelocity().y == 1);
        REQUIRE(container.GetParticle()[0].GetPosition().y == 102);
    }

    SECTION("Particle collides with bottom horizontal wall") {
        GasContainer container = GasContainer(10, 20, std::vector<idealgas::Particle>
                {idealgas::Particle(vec2(105, 119), vec2(0,1), 1)});
        container.AdvanceOneFrame();
        REQUIRE(container.GetParticle()[0].GetVelocity().y == -1);
        REQUIRE(container.GetParticle()[0].GetPosition().y == 118);
    }

}

TEST_CASE("Particle collusion tests") {
    SECTION("Particle collides with another particle both head-on horizontally") {
        GasContainer container = GasContainer(10, 20,std::vector<idealgas::Particle>
                {idealgas::Particle(vec2(105, 105), vec2(-1,0), 1),
                 idealgas::Particle(vec2(104, 105), vec2(1,0), 1)});
        container.AdvanceOneFrame();
        REQUIRE(container.GetParticle()[0].GetPosition().x == 106);
        REQUIRE(container.GetParticle()[1].GetPosition().x == 103);
        REQUIRE(container.GetParticle()[0].GetVelocity().x == 1);
        REQUIRE(container.GetParticle()[1].GetVelocity().x == -1);
    }

    SECTION("Particle collides with another particle both head-on vertically") {
        GasContainer container = GasContainer(10, 20,std::vector<idealgas::Particle>
                {idealgas::Particle(vec2(105, 105), vec2(0,-1), 1),
                 idealgas::Particle(vec2(105, 104), vec2(0,1), 1)});
        container.AdvanceOneFrame();
        REQUIRE(container.GetParticle()[0].GetPosition().y == 106);
        REQUIRE(container.GetParticle()[1].GetPosition().y == 103);
        REQUIRE(container.GetParticle()[0].GetVelocity().y == 1);
        REQUIRE(container.GetParticle()[1].GetVelocity().y == -1);
    }

    SECTION("Particle collides with another particle diagonally") {
        GasContainer container = GasContainer(10, 20,std::vector<idealgas::Particle>
                {idealgas::Particle(vec2(105, 105), vec2(1,1), 1),
                 idealgas::Particle(vec2(106, 106), vec2(-1,-1), 1)});
        container.AdvanceOneFrame();
        REQUIRE(104 -container.GetParticle()[0].GetPosition().x < 1e-6);
        REQUIRE(104 - container.GetParticle()[0].GetPosition().y < 1e-6);
        REQUIRE(107 - container.GetParticle()[1].GetPosition().x < 1e-6);
        REQUIRE(107 - container.GetParticle()[1].GetPosition().y < 1e-6);
        REQUIRE(-1.0 - container.GetParticle()[0].GetVelocity().x < 1e-6);
        REQUIRE(-1.0 - container.GetParticle()[0].GetVelocity().y < 1e-6);
        REQUIRE(1.0 - container.GetParticle()[1].GetVelocity().x < 1e-6);
        REQUIRE(1.0 - container.GetParticle()[1].GetVelocity().y < 1e-6);
    }

}
