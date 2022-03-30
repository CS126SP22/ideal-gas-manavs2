#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "gas_container.h"

namespace idealgas {

/**
 * An app for visualizing the behavior of an ideal gas.
 */
class IdealGasApp : public ci::app::App {
 public:
  IdealGasApp();

  void draw() override;
  void update() override;

  const int kWindowSizeX = 1400;
  const int kWindowSizeY = 875;
  const size_t kWidth = 600;
  const size_t kHeight = 400;
  const size_t kNumberOfParticles = 50;

  const std::vector<Particle> kTypeParticles = std::vector<Particle>({
      Particle("Small", vec2(0, 0), vec2(0, 0), 10, 5, ci::Color ("green")),
      Particle("Medium", vec2(0, 0), vec2(0, 0), 15, 5, ci::Color ("red")),
      Particle("Large", vec2(0, 0), vec2(0, 0), 20, 5, ci::Color ("blue")),
                                                             });

 private:
  GasContainer container_ = GasContainer(kWidth, kHeight, kNumberOfParticles, kTypeParticles);

};

}  // namespace idealgas
