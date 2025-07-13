// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include <memory>

#include "util/Time.hpp"

namespace element
{
    class Element;

    class ElementInstanceContext
    {
    public:
        ElementInstanceContext() = default;

        virtual ~ElementInstanceContext() = default;

        virtual ElementInstancePtr createInstance(Element &element) = 0;
        virtual void stageHandoff(player::Sample sample) = 0;
    };
}
