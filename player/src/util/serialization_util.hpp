#pragma once

#define FRIEND_CEREAL friend class cereal::access;

#define PRIVATE_SERIALIZE(ClassName)\
    ClassName() = default;\
    FRIEND_CEREAL

#define INTERNAL_SERIALIZE\
    template<class Archive>\
    void serialize(Archive& ar, const std::uint32_t version)

#define INTERNAL_SPLIT_SAVE\
    template<class Archive>\
    void save(Archive& ar, const std::uint32_t version) const

#define INTERNAL_SPLIT_LOAD\
    template<class Archive>\
    void load(Archive& ar, const std::uint32_t version)

#define EXTERNAL_SPLIT_SAVE(ClassName)\
    template<class Archive>\
    void save(Archive& ar, const ClassName& m)

#define EXTERNAL_SPLIT_LOAD(ClassName)\
    template<class Archive>\
    void load(Archive& ar, ClassName& m)