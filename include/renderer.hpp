#pragma once

#include "geometry.hpp"

class Renderer {
public:
  virtual void fillRect(float x, float y, float width, float height) = 0;
  virtual void strokeRect(float x, float y, float width, float height) = 0;
  virtual void clearRect(float x, float y, float width, float height) = 0;

  virtual void presentBuffer() = 0;
  virtual void presentRegion(float x, float y, float width, float height) = 0;

  virtual ~Renderer() {}
};
