#include "components/grid.hpp"

using namespace MTK;
using namespace MTK::Components;

Grid::Grid()
    : Container(
          new Layout::Grid({{100.0, Layout::Percent}, {100.0, Layout::Percent}},
                           {
                               {0.0, Layout::Pixel},
                               {0.0, Layout::Pixel},
                               {0.0, Layout::Pixel},
                               {0.0, Layout::Pixel},
                           },
                           Layout::X, {0, Layout::Pixel}, {}, NULL)) {}

void Grid::setGap(Layout::Length l) { ((Layout::Grid *)layout_node)->gap = l; }