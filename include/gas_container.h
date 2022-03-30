#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"
#include "cinder/Rand.h"
#include <math.h>

using glm::vec2;

namespace idealgas {

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
class GasContainer {
 public:
  /**
   * Constructs a container with default width and height.
   */
  GasContainer();
  /**
   * Constructs a container with given width, height, and randomly generates particles based on type.
   */
  GasContainer(size_t width, size_t height, size_t numberOfParticles, std::vector<Particle> particle_types);

  /**
   * Constructs a container with given width, height, and randomly generates particles based on type.
   */
  GasContainer(size_t width, size_t height, std::vector<Particle> particles);

  /**
   * Adds a particle to the container.
   */
  void AddParticle(const Particle & particle);

  /**
   * Displays the container walls and the current positions of the particles.
   */
  void Display() const;

  /**
   * Updates the positions and velocities of all particles (based on the rules
   * described in the assignment documentation).
   */
  void AdvanceOneFrame();

  /**
   * Checks if a given particle collides with any of the container walls and updates velocity accordingly.
   */
  void WallCollisionCheck(Particle & particle);

  std::vector<Particle> GetParticle();

  const size_t kTopLeftX = 10;
  const size_t kTopLeftY = 10;
  const size_t kDefaultWidth = 300;
  const size_t kDefaultHeight = 200;
  const size_t kParticleRadii = 5;

 private:
  size_t width_;
  size_t height_;
  std::vector<Particle> particles_;
};

}  // namespace idealgas
