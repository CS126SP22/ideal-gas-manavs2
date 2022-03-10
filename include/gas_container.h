#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"
#include "cinder/Rand.h"
#include <math.h>

using glm::vec2;

// Should I have a default constructor for particle, what should the default values for the object variables be?
// Should radius be set to a default value or let it be passed in as a parameter in constructor to be set?
// What constructors should I have? How should I construct a new Gas container (what are parameters and what should instance variables be for this class)
// Should I start off with a certain number of particles in the gas container? Do i pass a particle vector into the parameter? Instructions unclear
// How would I add more particles as time goes by? I have a method called AddParticles but where would I call it from?
// What should I do for display method? How do I display the container and the particles?
// Do I need to make changes to gas_simulation_app?
namespace idealgas {

/**
 * The container in which all of the gas particles are contained. This class
 * stores all of the particles and updates them on each frame of the simulation.
 */
class GasContainer {
 public:
  /**
   * TODO: Add more parameters to this constructor, and add documentation.
   */
  GasContainer();

  GasContainer(size_t width, size_t height, size_t numberOfParticles);

  GasContainer(size_t width, size_t height, std::vector<Particle> particles);


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

  void WallCollisionCheck(Particle & particle);

  const size_t kTopLeftX = 100;
  const size_t kTopLeftY = 100;
  const size_t kDefaultWidth = 600;
  const size_t kDefaultHeight = 400;
  const size_t kParticleRadii = 5;

 private:
  /**
   * This variable is just for the purposes of demonstrating how to make a shape move
   * across a screen. Please remove it once you start working on your code.
   */

  size_t width_;
  size_t height_;
  std::vector<Particle> particles_;
};

}  // namespace idealgas
