// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

/// Include this file before cereal polymorphic registration

#include "cereal/types/polymorphic.hpp"

/// Archive types that will be used.
#include "cereal/archives/json.hpp"
#include "cereal/archives/portable_binary.hpp"
