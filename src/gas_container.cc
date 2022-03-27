#include <random>
#include "gas_container.h"
#include <iostream>


namespace idealgas {

using glm::vec2;
using ci::Rand;

GasContainer::GasContainer() {
    width_ = kDefaultWidth;
    height_ = kDefaultHeight;
}



GasContainer::GasContainer(size_t width, size_t height, size_t numberOfParticles, std::vector<Particle> types) {
    width_ = width;
    height_ = height;

    for (size_t i = 0; i <numberOfParticles; i++) {
        Particle particle = types[i % types.size()];
        particle.SetPosition(vec2(Rand::randFloat(kTopLeftX + particle.GetRadius() + 1,
                                                  (width_ + kTopLeftX) - particle.GetRadius()),
                                  Rand::randFloat(kTopLeftY + particle.GetRadius() + 1,
                                                  (height_ + kTopLeftY) - particle.GetRadius())));
        particle.SetVelocity(vec2(Rand::randFloat(particle.GetRadius() * -1.0, particle.GetRadius()),
                                  Rand::randFloat(particle.GetRadius() * -1.0, particle.GetRadius())));

        particles_.push_back(particle);
    }
}

GasContainer::GasContainer(size_t width, size_t height, std::vector<Particle> particles) {
    width_ = width;
    height_ = height;
    particles_ = particles;
}

    std::vector<Particle> GasContainer::GetParticle() {
    return particles_;
}

void GasContainer::AddParticle(const Particle &particle) {
    particles_.push_back(particle);
}

// display particles
void GasContainer::Display() const {
  ci::gl::color(ci::Color("white"));
  ci::gl::drawStrokedRect(ci::Rectf(vec2(kTopLeftX, kTopLeftY), vec2(kTopLeftX + width_, kTopLeftY + height_)));

  for (size_t i = 0; i < particles_.size(); ++i) {
      ci::gl::color(particles_[i].GetColor());
      ci::gl::drawSolidCircle(particles_[i].GetPosition(), particles_[i].GetRadius());
  }
}

void GasContainer::WallCollisionCheck(Particle & particle) {
    bool leftWallCollision = particle.GetPosition().x - particle.GetRadius() <= kTopLeftX;
    bool rightWallCollision = particle.GetPosition().x + particle.GetRadius() >= kTopLeftX + width_;
    bool bottomWallCollision = particle.GetPosition().y - particle.GetRadius() <= kTopLeftY;
    bool topWallCollision = particle.GetPosition().y + particle.GetRadius() >= kTopLeftY + height_;

    if ((particle.GetVelocity().x < 0) && leftWallCollision) {
        vec2 particle_vel = particle.GetVelocity();
        particle_vel.x *= -1;
        particle.SetVelocity(particle_vel);
    }
    if ((particle.GetVelocity().x > 0) && rightWallCollision) {
        vec2 particle_vel = particle.GetVelocity();
        particle_vel.x *= -1;
        particle.SetVelocity(particle_vel);
    }
    if ((particle.GetVelocity().y < 0) && bottomWallCollision) {
        vec2 particle_vel = particle.GetVelocity();
        particle_vel.y *= -1;
        particle.SetVelocity(particle_vel);
    }
    if ((particle.GetVelocity().y > 0) && topWallCollision) {
        vec2 particle_vel = particle.GetVelocity();
        particle_vel.y *= -1;
        particle.SetVelocity(particle_vel);
    }
}

void GasContainer::AdvanceOneFrame() {
    for (size_t i = 0; i < particles_.size(); ++i) {
        WallCollisionCheck(particles_[i]);
        for (size_t j = i + 1; j < particles_.size(); ++j) {
            if (particles_[i].CheckForCollision(particles_[j])) {
                particles_[i].UpdateVelocityAfterCollusion(particles_[j]);
            }
        }
        particles_[i].AdvancePosition();
    }
}

}  // namespace idealgas
