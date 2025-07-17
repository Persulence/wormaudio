// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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
