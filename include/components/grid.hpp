#pragma once

#include "container.hpp"

namespace MTK {

namespace Components {

class Grid : public Container {
public:
  Grid();

  void setGap(Layout::Length l);
};

} // namespace Components

} // namespace MTK
