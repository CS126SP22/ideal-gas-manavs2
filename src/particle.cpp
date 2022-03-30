#include "particle.h"
namespace idealgas {
    Particle::Particle(const vec2 &position, const vec2 &velocity, double radius) {
        position_ = position;
        velocity_ = velocity;
        radius_ = radius;
        mass_ = 1.0;
    }

    Particle::Particle(std::string type, const vec2 &position, const vec2 &velocity, const double mass, const double radius,
                       const ci::Color color) {
        type_ = type;
        position_ = position;
        velocity_ = velocity;
        mass_ = mass;
        radius_ = radius;
        color_ = color;
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

    void Particle::SetPosition(const vec2 &position) {
        position_ = position;
    }

    ci::Color Particle::GetColor() const {
        return color_;
    }

    void Particle::Draw() const {
        ci::gl::drawSolidCircle(position_, radius_);
    }

    void Particle::InvertXVelocity() {
        velocity_.x *= -1;
    }

    void Particle::InvertYVelocity() {
        velocity_.y *= -1;
    }



    bool Particle::CheckForCollision(const Particle & otherParticle) const {
        double distance = glm::distance(position_, otherParticle.position_);
        double movement_towards = glm::dot(velocity_ - otherParticle.velocity_, position_ - otherParticle.position_);
        if ((distance <= (radius_ + otherParticle.radius_)) && (movement_towards < 0)) {
            return true;
        }

        return false;
    }

    void Particle::UpdateVelocityAfterCollusion(Particle &otherParticle) {
        vec2 x1 = position_;
        vec2 x2 = otherParticle.position_;
        vec2 v1 = velocity_;
        vec2 v2 = otherParticle.velocity_;
        float m1 = mass_;
        float m2 = otherParticle.mass_;

        velocity_ = v1 - (2 * m2 /(m1+m2) * (glm::dot((v1 - v2), (x1 - x2)) / (length(x1 - x2) * length(x1 - x2)))) * (x1 - x2);

        otherParticle.velocity_ =  v2 - (2 * m1 /(m1+m2) * (glm::dot((v2 - v1), (x2 - x1)) / (length(x2 - x1)
                                                                                      * length(x2 - x1)))) * (x2 - x1);
    }

    double Particle::GetMass() const {
        return mass_;
    }


}

