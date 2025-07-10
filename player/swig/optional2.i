%{
#include <optional>
%}

namespace std
{
    template<typename T>
    class optional
    {
    public:
        bool has_value() const noexcept;
    };
}

%define JOPT(OptT, T)

%template(OptT) std::optional<T>;

%typemap(javaout) std::optional<T>, const std::optional<T>& {
    OptT optvalue = new OptT($jnicall, $owner);
    optvalue.has_value();
    return null;
}

%enddef
