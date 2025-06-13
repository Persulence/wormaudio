#pragma once

#include "util/selection/SelectionManager.hpp"

namespace ui
{
    // To be accessed via Component::findParentOfClass. Requires janky multiple inheritance.
    class CanvasSelectionManager : public SelectionManager
    {
    };
}
