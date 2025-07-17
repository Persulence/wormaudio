// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "cereal/cereal.hpp"

#define FRIEND_CEREAL friend class cereal::access;

#define PRIVATE_SERIALIZE(ClassName)\
    ClassName() = default;\
    FRIEND_CEREAL

#define INTERNAL_SERIALIZE\
    template<class Archive>\
    void serialize(Archive& ar, const std::uint32_t version)

#define INTERNAL_SERIALIZE_SPECIALIZE(Archive)\
    void serialize(Archive& ar, const std::uint32_t version)

#define INTERNAL_SPLIT_SAVE\
    template<class Archive>\
    void save(Archive& ar, const std::uint32_t version) const

#define INTERNAL_SPLIT_LOAD\
    template<class Archive>\
    void load(Archive& ar, const std::uint32_t version)


#define EXTERNAL_SERIALIZE(ClassName)\
    template<class Archive>\
    void serialize(Archive& ar, const ClassName& m, const std::uint32_t version)

#define EXTERNAL_SPLIT_SAVE(ClassName)\
    template<class Archive>\
    void save(Archive& ar, const ClassName& m)

#define EXTERNAL_SPLIT_LOAD(ClassName)\
    template<class Archive>\
    void load(Archive& ar, ClassName& m)


#define LOAD_AND_CONSTRUCT(ClassName)\
    template <class Archive>\
    static void load_and_construct(Archive& ar, cereal::construct<ClassName>& construct)
