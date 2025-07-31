// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
