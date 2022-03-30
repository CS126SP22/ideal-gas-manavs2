#include <catch2/catch.hpp>

#include <gas_container.h>

using idealgas::GasContainer;

TEST_CASE("Wall collusion tests") {
    SECTION("Particle collides with left vertical wall") {
        GasContainer container = GasContainer(10, 20,std::vector<idealgas::Particle>
                {idealgas::Particle(vec2(11, 15), vec2(-1,0), 1)});
        container.AdvanceOneFrame();
        REQUIRE(container.GetParticle()[0].GetVelocity().x == 1);
        REQUIRE(container.GetParticle()[0].GetPosition().x == 12);
    }
    SECTION("Particle collides with right vertical wall") {
        GasContainer container = GasContainer(10, 20, std::vector<idealgas::Particle>
                {idealgas::Particle(vec2(19, 15), vec2(1,0), 1)});
        container.AdvanceOneFrame();
        REQUIRE(container.GetParticle()[0].GetVelocity().x == -1);
        REQUIRE(container.GetParticle()[0].GetPosition().x == 18);
    }

    SECTION("Particle collides with top horizontal wall") {
        GasContainer container = GasContainer(10, 20, std::vector<idealgas::Particle>
                {idealgas::Particle(vec2(15, 11), vec2(0,-1), 1)});
        container.AdvanceOneFrame();
        REQUIRE(container.GetParticle()[0].GetVelocity().y == 1);
        REQUIRE(container.GetParticle()[0].GetPosition().y == 12);
    }

    SECTION("Particle collides with bottom horizontal wall") {
        GasContainer container = GasContainer(10, 20, std::vector<idealgas::Particle>
                {idealgas::Particle(vec2(15, 29), vec2(0,1), 1)});
        container.AdvanceOneFrame();
        REQUIRE(container.GetParticle()[0].GetVelocity().y == -1);
        REQUIRE(container.GetParticle()[0].GetPosition().y == 28);
    }

}

TEST_CASE("Particle collusion tests") {
    SECTION("Particle collides with another particle both head-on horizontally with same mass") {
        GasContainer container = GasContainer(10, 20,std::vector<idealgas::Particle>
                {idealgas::Particle("Small", vec2(15, 15), vec2(-1,0), 5.0, 1, ci::Color ("green")),
                 idealgas::Particle("Small", vec2(14, 15), vec2(1,0), 5.0, 1, ci::Color ("green"))});
        container.AdvanceOneFrame();
        REQUIRE(container.GetParticle()[0].GetPosition().x == 16);
        REQUIRE(container.GetParticle()[1].GetPosition().x == 13);
        REQUIRE(container.GetParticle()[0].GetVelocity().x == 1);
        REQUIRE(container.GetParticle()[1].GetVelocity().x == -1);
    }

    SECTION("Particle collides with another particle both head-on horizontally with different masses") {
        GasContainer container = GasContainer(10, 20,std::vector<idealgas::Particle>
                {idealgas::Particle("Small", vec2(15, 15), vec2(-1,0), 5.0, 1, ci::Color ("green")),
                 idealgas::Particle("Medium", vec2(14, 15), vec2(1,0), 10.0, 1, ci::Color ("red"))});
        container.AdvanceOneFrame();
        REQUIRE(16.66667 - container.GetParticle()[0].GetPosition().x < 1e-5);
        REQUIRE(13.66667 - container.GetParticle()[1].GetPosition().x < 1e-5);
        REQUIRE(1.66667 - container.GetParticle()[0].GetVelocity().x < 1e-5);
        REQUIRE(-0.3333 + container.GetParticle()[1].GetVelocity().x < 1e-5);
    }

    SECTION("Particle collides with another particle both head-on horizontally with significantly different masses") {
        GasContainer container = GasContainer(10, 20,std::vector<idealgas::Particle>
                {idealgas::Particle("Small", vec2(15, 15), vec2(-1,0), 1.0, 1, ci::Color ("green")),
                 idealgas::Particle("Large", vec2(14, 15), vec2(1,0), 20.0, 1, ci::Color ("blue"))});
        container.AdvanceOneFrame();
        REQUIRE(17.80952 - container.GetParticle()[0].GetPosition().x < 1e-5 );
        REQUIRE(14.80952 - container.GetParticle()[1].GetPosition().x < 1e-5);
        REQUIRE(2.80952 - container.GetParticle()[0].GetVelocity().x < 1e-5);
        REQUIRE(0.80952 - container.GetParticle()[1].GetVelocity().x < 1e-5);
    }

    SECTION("Particle collides with another particle both head-on vertically with same mass") {
        GasContainer container = GasContainer(10, 20,std::vector<idealgas::Particle>
                {idealgas::Particle("Small", vec2(15, 15), vec2(0,-1), 5.0, 1, ci::Color ("green")),
                 idealgas::Particle("Small", vec2(15, 14), vec2(0,1), 5.0, 1, ci::Color("green"))});
        container.AdvanceOneFrame();
        REQUIRE(container.GetParticle()[0].GetPosition().y == 16);
        REQUIRE(container.GetParticle()[1].GetPosition().y == 13);
        REQUIRE(container.GetParticle()[0].GetVelocity().y == 1);
        REQUIRE(container.GetParticle()[1].GetVelocity().y == -1);
    }

    SECTION("Particle collides with another particle both head-on vertically with different masses") {
        GasContainer container = GasContainer(10, 20,std::vector<idealgas::Particle>
                {idealgas::Particle("Small", vec2(15, 15), vec2(0,-1), 5.0, 1, ci::Color ("green")),
                 idealgas::Particle("Medium", vec2(15, 14), vec2(0,1), 10.0, 1, ci::Color("red"))});
        container.AdvanceOneFrame();
        REQUIRE(16.66667 - container.GetParticle()[0].GetPosition().y < 1e-5);
        REQUIRE(13.66667 - container.GetParticle()[1].GetPosition().y < 1e-5);
        REQUIRE(1.66667 - container.GetParticle()[0].GetVelocity().y < 1e-5);
        REQUIRE(-0.3333 + container.GetParticle()[1].GetVelocity().x < 1e-5);
    }

    SECTION("Particle collides with another particle both head-on vertically with significantly different masses") {
        GasContainer container = GasContainer(10, 20,std::vector<idealgas::Particle>
                {idealgas::Particle("Small", vec2(15, 15), vec2(0,-1), 1.0, 1, ci::Color ("green")),
                 idealgas::Particle("Large", vec2(15, 14), vec2(0,1), 20.0, 1, ci::Color("blue"))});
        container.AdvanceOneFrame();
        REQUIRE(17.8095 - container.GetParticle()[0].GetPosition().y < 1e-5);
        REQUIRE(14.80952 - container.GetParticle()[1].GetPosition().y < 1e-5);
        REQUIRE(2.80952 - container.GetParticle()[0].GetVelocity().y < 1e-5);
        REQUIRE(0.0 - container.GetParticle()[1].GetVelocity().x < 1e-5);
    }

    SECTION("Particle collides with another particle diagonally with same mass") {
        GasContainer container = GasContainer(10, 20,std::vector<idealgas::Particle>
                {idealgas::Particle("Small", vec2(15, 15), vec2(1,1), 5.0, 1, ci::Color ("green")),
                 idealgas::Particle("Small",vec2(16, 16), vec2(-1,-1), 5.0, 1, ci::Color ("green"))});
        container.AdvanceOneFrame();
        REQUIRE(14 -container.GetParticle()[0].GetPosition().x < 1e-6);
        REQUIRE(14 - container.GetParticle()[0].GetPosition().y < 1e-6);
        REQUIRE(17 - container.GetParticle()[1].GetPosition().x < 1e-6);
        REQUIRE(17 - container.GetParticle()[1].GetPosition().y < 1e-6);
        REQUIRE(-1.0 - container.GetParticle()[0].GetVelocity().x < 1e-6);
        REQUIRE(-1.0 - container.GetParticle()[0].GetVelocity().y < 1e-6);
        REQUIRE(1.0 - container.GetParticle()[1].GetVelocity().x < 1e-6);
        REQUIRE(1.0 - container.GetParticle()[1].GetVelocity().y < 1e-6);
    }

    SECTION("Particle collides with another particle diagonally with different masses") {
        GasContainer container = GasContainer(10, 20,std::vector<idealgas::Particle>
                {idealgas::Particle("Small", vec2(15, 15), vec2(1,1), 5.0, 1, ci::Color ("green")),
                 idealgas::Particle("Medium",vec2(16, 16), vec2(-1,-1), 10.0, 1, ci::Color ("red"))});
        container.AdvanceOneFrame();
        REQUIRE(13.3333 - container.GetParticle()[0].GetPosition().x < 1e-6);
        REQUIRE(13.3333 - container.GetParticle()[0].GetPosition().y < 1e-6);
        REQUIRE(16.33333 - container.GetParticle()[1].GetPosition().x < 1e-6);
        REQUIRE(16.33333 - container.GetParticle()[1].GetPosition().y < 1e-6);
        REQUIRE(-1.666666 + container.GetParticle()[0].GetVelocity().x < 1e-6);
        REQUIRE(-1.66666 + container.GetParticle()[0].GetVelocity().y < 1e-6);
        REQUIRE(0.333333 - container.GetParticle()[1].GetVelocity().x < 1e-6 );
        REQUIRE(0.33333 - container.GetParticle()[1].GetVelocity().y < 1e-6);
    }

    SECTION("Particle collides with another particle diagonally with significantly different masses") {
        GasContainer container = GasContainer(10, 20,std::vector<idealgas::Particle>
                {idealgas::Particle("Small", vec2(15, 15), vec2(1,1), 1.0, 1, ci::Color ("green")),
                 idealgas::Particle("Medium",vec2(16, 16), vec2(-1,-1), 20.0, 1, ci::Color ("blue"))});
        container.AdvanceOneFrame();
        REQUIRE(12.19048 - container.GetParticle()[0].GetPosition().x < 1e-5);
        REQUIRE(12.19048 -container.GetParticle()[0].GetPosition().y < 1e-5);
        REQUIRE(15.19048 - container.GetParticle()[1].GetPosition().x < 1e-5);
        REQUIRE(15.19048 - container.GetParticle()[1].GetPosition().y < 1e-5);
        REQUIRE(-2.80952 + container.GetParticle()[0].GetVelocity().x < 1e-5);
        REQUIRE(-2.80952 + container.GetParticle()[0].GetVelocity().y < 1e-5);
        REQUIRE(-0.80952 + container.GetParticle()[1].GetVelocity().x < 1e-5);
        REQUIRE(-0.80952 + container.GetParticle()[1].GetVelocity().y < 1e-5);
    }

}

TEST_CASE("No collusion") {
    SECTION("Two particles aren't touching") {
        GasContainer container = GasContainer(10, 20,std::vector<idealgas::Particle>
                {idealgas::Particle("Small", vec2(15, 12), vec2(1,0), 5.0, 1, ci::Color ("green")),
                 idealgas::Particle("Medium", vec2(12, 15), vec2(-1,0), 10.0, 1, ci::Color ("red"))});
        container.AdvanceOneFrame();
        REQUIRE(container.GetParticle()[0].GetPosition().x == 16);
        REQUIRE(container.GetParticle()[1].GetPosition().x == 11);
        REQUIRE(container.GetParticle()[0].GetVelocity().x == 1);
        REQUIRE(container.GetParticle()[1].GetVelocity().x == -1);

    }

    SECTION("Two particles are touching, but already moving away from each other") {
        GasContainer container = GasContainer(10, 20,std::vector<idealgas::Particle>
                {idealgas::Particle("Small", vec2(15, 15), vec2(0,-1), 5.0, 1, ci::Color ("green")),
                 idealgas::Particle("Medium", vec2(12, 15), vec2(0,1), 10.0, 1, ci::Color ("red"))});
        container.AdvanceOneFrame();
        REQUIRE(container.GetParticle()[0].GetPosition().y == 14);
        REQUIRE(container.GetParticle()[1].GetPosition().y == 16);
        REQUIRE(container.GetParticle()[0].GetVelocity().y == -1);
        REQUIRE(container.GetParticle()[1].GetVelocity().y == 1);
    }
}
