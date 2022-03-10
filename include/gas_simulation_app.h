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

  const int kWindowSize = 875;
  const size_t kWidth = 600;
  const size_t kHeight = 400;
  const size_t kNumberOfParticles = 50;

 private:
  GasContainer container_ = GasContainer(kWidth, kHeight, kNumberOfParticles);

};

}  // namespace idealgas
