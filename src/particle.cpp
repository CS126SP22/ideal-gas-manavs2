#include "particle.h"
namespace idealgas {
    Particle::Particle(const vec2 &position, const vec2 &velocity, double radius) {
        position_ = position;
        velocity_ = velocity;
        radius_ = radius;
    }

    void Particle::AdvancePosition() {
        position_ += velocity_;
    }

    vec2 Particle::GetPosition() const {
        return position_;
    }
    double Particle::GetRadius() const {
        return radius_;
    }

    vec2 Particle::GetVelocity() const {
        return velocity_;
    }

    void Particle::SetVelocity(const vec2 &velocity) {
        velocity_ = velocity;
    }

    void Particle::Draw() const {
        ci::gl::drawSolidCircle(position_, radius_);
    }

    bool Particle::CheckForCollision(const Particle & otherParticle) const {
        double distance = glm::distance(position_, otherParticle.position_);
        double product = glm::dot(velocity_ - otherParticle.velocity_, position_ - otherParticle.position_);
        if ((distance <= (radius_ + otherParticle.radius_)) && (product < 0)) {
            return true;
        }

        return false;
    }

    void Particle::UpdateVelocityAfterCollusion(Particle &otherParticle) {
        vec2 x1 = position_;
        vec2 x2 = otherParticle.position_;
        vec2 v1 = velocity_;
        vec2 v2 = otherParticle.velocity_;

        velocity_ = v1 - (glm::dot((v1 - v2), (x1 - x2)) / (length(x1 - x2) * length(x1 - x2))) * (x1 - x2);

        otherParticle.velocity_ =  v2 - (glm::dot((v2 - v1), (x2 - x1)) / (length(x2 - x1)
                                                                                      * length(x2 - x1))) * (x2 - x1);
    }



}

