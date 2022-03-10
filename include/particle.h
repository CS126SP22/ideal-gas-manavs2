#pragma once
#include "cinder/gl/gl.h"
using glm::vec2;


namespace idealgas {
    class Particle {
    public:
        /**
         * Constructs a particle with a given position, velocity, and radius
         */
        Particle(const vec2 & position, const vec2 & velocity, double radius);
        /**
         * Changes the position of a particle based on particle's velocity
         */
        void AdvancePosition();
        vec2 GetPosition() const;
        vec2 GetVelocity() const;
        double GetRadius() const;
        void SetVelocity(const vec2 & velocity);
        /**
         * Checks if a particle collides another given particle
         */
        bool CheckForCollision(const Particle & otherParticle) const;
        void Draw() const;
        /**
         * Updates the velocity of the two particles that have collided
         */
        void UpdateVelocityAfterCollusion(Particle & otherParticle);

    private:
        vec2 position_;
        vec2 velocity_;
        double radius_;
    };

}
