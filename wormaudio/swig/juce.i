// Copyright (c)  2025 Thomas Paley-Menzies
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

// SWIG does not recursively traverse headers, so these must be defined to prevent syntax errors.
#define JUCE_DECLARE_NON_COPYABLE(c)
#define JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(c)

// I will gradually migrate to these macros which don't have any other header dependencies
#define DISABLE_COPY(ClassName)\
    ClassName(const ClassName&) = delete;\
    ClassName& operator=(const ClassName&) = delete;

#define DISABLE_MOVE(ClassName)\
    ClassName(ClassName&&) = delete;\
    ClassName& operator=(ClassName&&) = delete;

#define ENABLE_DEFAULT_MOVE(ClassName)\
    ClassName(ClassName&&) = default;\
    ClassName& operator=(ClassName&&) = default;\
