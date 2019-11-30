#include "backend/SDL2.hpp"
#include "components/components.hpp"

using namespace MTK;
using namespace Components;
using namespace MTK::Layout::Units;

#include <iostream>

int main() {
  Backend::SDL2 b;

  Window w(&b);
  w.setBackgroundColor(0, 0, 1, 1).setPadding(15_px, 15_px, 15_px, 15_px);

  Container black_box;
  black_box.setBackgroundColor(0, 0, 0, 1)
      .setSize(480_px, 400_px)
      .setPadding(5_px, 5_px, 5_px, 5_px);
  w.addChildren(&black_box);

  Container white_box;
  white_box.setBackgroundColor(1, 1, 1, 1)
      .setSize(100_percent, 100_percent)
      .setPadding(5_px, 5_px, 5_px, 5_px)
      .setMajorAxis(Layout::Y);
  black_box.addChildren(&white_box);

  Container top_graphs;
  top_graphs.setSize(100_percent, 280_px);
  white_box.addChildren(&top_graphs);

  Container black_box_L;
  black_box_L.setBackgroundColor(0, 0, 0, 1)
      .setSize(70_px, 100_percent)
      .setPadding(5_px, 5_px, 5_px, 5_px);
  top_graphs.addChildren(&black_box_L);

  Container red_box_L;
  red_box_L.setBackgroundColor(1, 0, 0, 1);
  black_box_L.addChildren(&red_box_L);

  Container top_gap;
  top_gap.setSize(10_px, 100_percent);
  top_graphs.addChildren(&top_gap);

  Container black_box_R;
  black_box_R.setBackgroundColor(0, 0, 0, 1).setPadding(10_px, 10_px, 10_px, 10_px);
  top_graphs.addChildren(&black_box_R);

  Container white_box_R;
  white_box_R.setBackgroundColor(1, 1, 1, 1);
  black_box_R.addChildren(&white_box_R);

  w.run();

  return 0;
}