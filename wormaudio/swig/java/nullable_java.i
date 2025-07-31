// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
