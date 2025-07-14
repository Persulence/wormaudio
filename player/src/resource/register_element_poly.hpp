// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#undef Null

#include "ChoiceElement.hpp"
#include "ClipElement.hpp"

#include "cereal/types/string.hpp"
#include "cereal/types/polymorphic.hpp"
#include "cereal/archives/json.hpp"
#include "cereal/archives/portable_binary.hpp"

CEREAL_REGISTER_TYPE(element::ClipElement)
CEREAL_REGISTER_TYPE(element::ChoiceElement)
