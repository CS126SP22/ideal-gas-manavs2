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

        void AdvancePosition();
        vec2 GetPosition() const;
        vec2 GetVelocity() const;
        double GetRadius() const;
        void SetVelocity(const vec2 & velocity);
        bool CheckForCollision(const Particle & otherParticle) const;
        void Draw() const;

        void UpdateVelocityAfterCollusion(Particle & otherParticle);

    private:
        vec2 position_;
        vec2 velocity_;
        double radius_;
    };

}
