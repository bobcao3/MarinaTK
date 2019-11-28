#pragma once

#include "geometry.hpp"

namespace MTK::Backend {

struct Event {
  void *target;
};

enum ButtonAction {
  DOWN,
  UP,
  HOVER
};

struct EventKey : public Event {
  std::string key;
  ButtonAction action;
};

struct EventPointer : public Event {
  std::string button;
  ButtonAction action;
  int x, y;
};

typedef void (*eventCallback)(Event *);

class Backend {
public:
  virtual void fillRect(float x, float y, float width, float height) = 0;
  virtual void strokeRect(float x, float y, float width, float height) = 0;
  virtual void clearRect(float x, float y, float width, float height) = 0;
  virtual void clear() = 0;

  virtual void presentBuffer() = 0;
  virtual void presentRegion(float x, float y, float width, float height) = 0;

  virtual void font(const char *name, int size) = 0;
  virtual void fillText(const char *str, float x, float y) = 0;

  virtual void fillColor(float r, float g, float b, float a) = 0;

  virtual void waitEvents() = 0;
  virtual bool isTerminated() = 0;

  virtual void setKeyCallback(eventCallback cb) = 0;
  virtual void setPointerCallback(eventCallback cb) = 0;

  virtual ~Backend() {}
};

} // namespace MTK::Backend