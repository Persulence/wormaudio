// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

%{
#include <optional>
%}

%include <std_string.i>

%include "Nullable.hpp"

%define JOPT(OptT, T)

//%template(OptT) binding::Nullable<T>;
%typemap(jstype) binding::Nullable<T> "$typemap(jboxtype, T)"

%typemap(out) binding::Nullable<T>, const binding::Nullable<T>& {
        if ($1.hasValue())
        {
            // I would like to delegate to T's already defined typemap here, but it doesn't seem possible as the argument is hardcoded to 'result', which is the wrong type.
            // $typemap(out, T)
            *(T**)& $result = (new T{$1.value()});
        }
        else
        {
            return $null;
        }
    }

%typemap(javaout) binding::Nullable<T>, const binding::Nullable<T>& {
        var cPtr = $jnicall;
        if (cPtr == 0)
            return null;

        // This will fail for some types, such as std::string
        // There is no way to recursively include
        // std::string refers to $jnicall, which generates the top level JNI call, rather than the one that creates a String.
        // Assuming the object is owning. $owned is always false, even when it shouldn't be.
        return new $typemap(jboxtype, T)(cPtr, true);
    }

%enddef
