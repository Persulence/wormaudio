// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

%include "enums.swg"
%javaconst(1);

%include "util.i"
%include "juce.i"

%ignore player::TransportControl::signal;
%include "player/transport.hpp"
UNIGNORE_ALL