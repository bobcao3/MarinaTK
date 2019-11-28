#include <layout.hpp>
#include <mtk.hpp>
#include <backend/SDL2.hpp>

#include <iostream>
#include <chrono>

using namespace MTK;

Backend::SDL2 *r;

class LayoutVisualizer : public Layout::LayoutInterface {
public:
  void layout(float x, float y, float w, float h) { r->strokeRect(x, y, w, h); }
};

int main() {
  r = new Backend::SDL2();

  LayoutVisualizer rd;

  Layout::Box box0({{50.0, Layout::Pixel}, {50.0, Layout::Pixel}},
                   {
                       {0.0, Layout::Pixel},
                       {0.0, Layout::Pixel},
                       {0.0, Layout::Pixel},
                       {0.0, Layout::Pixel},
                   },
                   Layout::Y, {}, &rd);

  Layout::Box box1_0({{100.0, Layout::Percent}, {100.0, Layout::Percent}},
                     {
                         {0.0, Layout::Pixel},
                         {0.0, Layout::Pixel},
                         {0.0, Layout::Pixel},
                         {0.0, Layout::Pixel},
                     },
                     Layout::Y, {}, &rd);

  Layout::Grid box1 = {{{300.0, Layout::Pixel}, {100.0, Layout::Pixel}},
                       {
                           {10.0, Layout::Pixel},
                           {10.0, Layout::Pixel},
                           {10.0, Layout::Pixel},
                           {10.0, Layout::Pixel},
                       },
                       Layout::X,
                       {5, Layout::Pixel},
                       {&box1_0, &box1_0, &box1_0},
                       &rd};

  Layout::Box box2 = {{{0.0, Layout::Pixel}, {100.0, Layout::Pixel}},
                      {
                          {0.0, Layout::Pixel},
                          {0.0, Layout::Pixel},
                          {0.0, Layout::Pixel},
                          {0.0, Layout::Pixel},
                      },
                      Layout::Y,
                      {},
                      &rd};

  Layout::Box root = {{{800.0, Layout::Pixel}, {600.0, Layout::Pixel}},
                      {
                          {10.0, Layout::Pixel},
                          {10.0, Layout::Pixel},
                          {50.0, Layout::Pixel},
                          {50.0, Layout::Pixel},
                      },
                      Layout::Y,
                      {&box0, &box1, &box2},
                      &rd};

  auto start = std::chrono::steady_clock::now();

  while (!r->isTerminated()) {
    r->clear();
    r->waitEvents();

    auto end = std::chrono::steady_clock::now();
    float time =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
            .count();

    box1.size.width.value = sin(time * 0.001) * 200 + 400;

    root.layout(&root, 0, 0, 0, 0);

    r->presentBuffer();
  }

  return 0;
}