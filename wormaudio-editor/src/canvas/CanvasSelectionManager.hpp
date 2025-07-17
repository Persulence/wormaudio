// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "util/selection/SelectionManager.hpp"

namespace ui
{
    // To be accessed via Component::findParentOfClass. Requires janky multiple inheritance.
    class CanvasSelectionManager : public SelectionManager
    {
    };
}
