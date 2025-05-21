export module ElementInstance;

namespace element
{
//    export template <class T>
    export class ElementInstance
    {
    public:
        virtual void activate() = 0;

        virtual ~ElementInstance() = default;
    };
}

