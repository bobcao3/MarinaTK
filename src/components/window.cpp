#include "components/window.hpp"

using namespace MTK;
using namespace MTK::Components;

Window::Window(Backend::Backend *b) {
  size = b->getSize();

  backend = b;

  layout_node = new Layout::Box({Layout::Length(Layout::standardDPI, size.x),
                                 Layout::Length(Layout::standardDPI, size.y)},
                                {
                                    {0.0, Layout::Pixel},
                                    {0.0, Layout::Pixel},
                                    {0.0, Layout::Pixel},
                                    {0.0, Layout::Pixel},
                                },
                                Layout::X, {}, NULL);

  auto cb = std::bind(&Window::onPointer, this, std::placeholders::_1);
  backend->setPointerCallback(cb);
}

bool Window::onPointerEvent(Event *ev) { return true; }

bool Window::onKeyboardEvent(Event *ev) { return true; }

Layout::Node *Window::getLayoutNode() { return layout_node; }

Component *Window::getParent() { return nullptr; }

std::vector<Component *> Window::getChildren() {}

void Window::removeChildren(Component *c) {}

void Window::onPointer(Backend::Event *_e) {
  Backend::EventPointer *e = (Backend::EventPointer *)_e;

  if (e->action == Backend::HOVER) {
    mouseX = e->x;
    mouseY = e->y;
  }
}

void Window::run() {
  while (!backend->isTerminated()) {
    backend->waitEvents();

    backend->clear();
    backend->fillColor(0.0, 0.0, 0.0, 1.0);
    backend->fillRect(50, 50, 100, 50);
    backend->fillColor(1.0, 0.0, 0.0, 1.0);
    backend->strokeRect(25, 25, 150, 100);
    backend->clearRect(100, 75, 50, 50);

    backend->font("/usr/share/fonts/truetype/NotoSans-Regular.ttf", 20);
    backend->fillText("Test FONT!", 50, 200);

    backend->font("/usr/share/fonts/truetype/NotoSans-Regular.ttf", 30);
    backend->fillText("Test FONT BIG!", 50, 250);

    backend->fillColor(0.0, 1.0, 1.0, 1.0);
    backend->font("/usr/share/fonts/truetype/NotoSans-Regular.ttf", 20);
    backend->fillText("Test FONT cache", 50, 300);

    backend->fillColor(0.2, 1.0, 0.6, 0.5);
    backend->fillRect(0, mouseY, 800, 1);
    backend->fillRect(mouseX, 0, 1, 600);

    backend->presentBuffer();
  }
}

Window::~Window() {
  delete layout_node;
  delete backend;
}