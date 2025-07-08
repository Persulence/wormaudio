#include "EventDefFiller.hpp"

#include "panel/ChoicePropertyWidget.hpp"
#include "panel/MyPropertyPanel.hpp"
#include "panel/SliderPropertyWidget.hpp"

namespace ui
{
    class AttenuationWidget : public PropertyMember
    {
    public:
        const event::EventProperties& properties;

        explicit AttenuationWidget(const event::EventProperties &properties) :
            properties(properties) {}

        void paint(juce::Graphics &g) override
        {
            using namespace juce;

            // Normal border
            float thickness = 1;
            const auto bounds = getLocalBounds().toFloat().expanded(-thickness / 2);
            g.setColour(Colours::black);
            g.drawRoundedRectangle(bounds, 5, thickness);

            Path path;

            constexpr float plotThickness = 1;
            constexpr float points = 20;

            const float distIncrement = properties.maxDistance / points;
            const float xIncrement = getWidth() / points;
            float f = 5;
            const float h = getHeight() - f;

            float value = properties.attenuate(0);
            for (int i = 1; i < points + 1; i++)
            {
                float newValue = properties.attenuate(i * distIncrement);

                const Line l{(i - 1) * xIncrement, (1 - value) * h + f,
                    i * xIncrement, (1 - newValue) * h + f};

                path.addLineSegment(l, plotThickness);

                value = newValue;
            }

            PathStrokeType type = PathStrokeType{plotThickness};

            g.strokePath(path, type, AffineTransform{});
        }

        int getDesiredHeight() const override
        {
            return 2 * settings::browserEntryHeight;
        }
    };

    EventDefFiller::EventDefFiller(resource::Handle<event::EventDef> eventDef_):
        eventDef(std::move(eventDef_)),
        attenuationPreview(std::make_shared<AttenuationWidget>(eventDef->getProperties()))
    {
        eventDef->nameValue().setupListener(this, [this](auto&){ refresh(); });
    }

    void EventDefFiller::initProperties()
    {
        setHeader(std::make_unique<SectionHeader>("Event: " + eventDef->nameValue().getValue()));

        auto& choice = add(ChoicePropertyWidget<player::Attenuation>::create("Attenuation function",
            {
                {"None", player::Attenuation::NONE},
                {"Linear", player::Attenuation::LINEAR},
                {"Linear Rolloff", player::Attenuation::LINEAR_ROLLOFF},
                {"Inverse Distance", player::Attenuation::INVERSE_DISTANCE}
            },
            &eventDef->properties.attenuation));
        choice.onChange = [this]
        {
            attenuationPreview->repaint();
        };

        auto& min = add(std::make_unique<EntryPropertyWidget<float>>("Min distance", parse::parseFloat));
        min.setValue(eventDef->properties.minDistance);
        min.listener = [this](auto value)
        {
            eventDef->properties.minDistance = value;
            attenuationPreview->repaint();
        };

        auto& max = add(std::make_unique<EntryPropertyWidget<float>>("Max distance", parse::parseFloat));
        max.setValue(eventDef->properties.maxDistance);
        max.listener = [this](auto value)
        {
            eventDef->properties.maxDistance = value;
            attenuationPreview->repaint();
        };

        auto& falloff = add(std::make_unique<SliderPropertyWidget>("Rolloff"));
        falloff.slider.setRange(0, 2, 0.01);
        falloff.slider.setValue(eventDef->properties.falloff, false);
        falloff.slider.onChanged.setup(&falloffListener, [this](auto val)
        {
            eventDef->properties.falloff = val;
            attenuationPreview->repaint();
        });

        add(std::dynamic_pointer_cast<AttenuationWidget>(attenuationPreview));
    }
}
