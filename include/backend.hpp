#pragma once

#include "geometry.hpp"

namespace MTK::Backend {

class Backend {
public:
  virtual void fillRect(float x, float y, float width, float height) = 0;
  virtual void strokeRect(float x, float y, float width, float height) = 0;
  virtual void clearRect(float x, float y, float width, float height) = 0;

  virtual void presentBuffer() = 0;
  virtual void presentRegion(float x, float y, float width, float height) = 0;

  virtual void font(const char* name, int size) = 0;
  virtual void fillText(const char* str, float x, float y) = 0;

  virtual void fillColor(float r, float g, float b, float a) = 0;

  virtual ~Backend() {}
};

}