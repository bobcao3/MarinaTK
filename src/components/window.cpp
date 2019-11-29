#include "components/window.hpp"

using namespace MTK;
using namespace MTK::Components;

Window::Window(Backend::Backend *b)
    : Container(
          new Layout::Box({{100.0, Layout::Percent}, {100.0, Layout::Percent}},
                          {
                              {0.0, Layout::Pixel},
                              {0.0, Layout::Pixel},
                              {0.0, Layout::Pixel},
                              {0.0, Layout::Pixel},
                          },
                          Layout::X, {}, NULL)) {
  size = b->getSize();

  backend = b;

  auto cb = std::bind(&Window::onPointer, this, std::placeholders::_1);
  backend->setPointerCallback(cb);

  backgroundColor = glm::vec4(1.0);
}

void Window::onPointer(Backend::Event *_e) {
  Backend::EventPointer *e = (Backend::EventPointer *)_e;

  Layout::Extent2 hit_pos = {Layout::Length(Layout::standardDPI, e->x),
                             Layout::Length(Layout::standardDPI, e->y)};
  PointerEvent new_ev = {this, hit_pos, e->action};
  onPointerEvent(&new_ev);
}

void Window::run() {
  while (!backend->isTerminated()) {
    backend->clear();

    backend->waitEvents();

    layout_node->layout(0, 0, size.x, size.y);

    backend->presentBuffer();
  }
}