#pragma once

#include "juce_gui_basics/juce_gui_basics.h"

namespace ui
{
    struct CommandCategory
    {
        static constexpr std::string APP{"app"};
        static constexpr std::string FILE{"file"};
        static constexpr std::string EDIT{"edit"};
    };

    struct CommandDef
    {
        juce::CommandID id;
        std::string name;
        std::string desc;
        std::string category;
        int flags{0};

        void apply(juce::ApplicationCommandInfo& info) const
        {
            info.setInfo(name, desc, category, flags);
        }

        // void setupKeyPress()
    };

    struct CommandAction : public CommandDef
    {
        using Action = std::function<void(const juce::ApplicationCommandTarget::InvocationInfo& info)>;
        Action action;

        CommandAction(const CommandDef &def, Action action_):
            CommandDef(def), action(action_)
        {

        }

        void perform(const juce::ApplicationCommandTarget::InvocationInfo& info) const
        {
            action(info);
        }
    };

    class Commands : public juce::ApplicationCommandManager, public juce::DeletedAtShutdown
    {
    public:
        // static constexpr juce::CommandID QUIT = juce::StandardApplicationCommandIDs::quit;
        // static constexpr juce::CommandID DEL = juce::StandardApplicationCommandIDs::del;
        static inline CommandDef QUIT{juce::StandardApplicationCommandIDs::quit, "Quit", "Quit the application", CommandCategory::APP, 0};
        static inline CommandDef DEL{juce::StandardApplicationCommandIDs::del, "Delete", "Delete current selection", CommandCategory::EDIT, 0};

        static inline CommandDef SAVE_PROJECT{0x2001, "Save", "Save current project", CommandCategory::FILE, 0};
        static inline CommandDef SAVE_PROJECT_AS{0x2002, "Save As", "Save current project as new file", CommandCategory::FILE, 0};
        static inline CommandDef OPEN_PROJECT{0x2003, "Open", "Open project", CommandCategory::FILE, 0};

        static inline CommandDef OPEN_PROJECT_SETTINGS{0x2010, "Project Settings", "Open project settings", CommandCategory::FILE, 0};

        static Commands& getInstance()
        {
            static std::mutex mutex;
            // static std::unique_ptr<CommandManager> instance;
            static Commands* instance;

            std::lock_guard lock{mutex};
            if (!instance)
            {
                // instance = std::make_unique<CommandManager>();
                // Deleted by DeletedAtShutdown
                instance = new Commands{};
            }
            return *instance;
        }

    private:
        Commands()
        {
        }
    };

    // class Commands : public juce::DeletedAtShutdown
    // {
    // public:

        // juce::ApplicationCommandInfo quit{QUIT};
        //
        // juce::ApplicationCommandInfo del{DEL};
        // juce::ApplicationCommandInfo copy{juce::StandardApplicationCommandIDs::copy};
        // juce::ApplicationCommandInfo cut{juce::StandardApplicationCommandIDs::cut};
        // juce::ApplicationCommandInfo paste{juce::StandardApplicationCommandIDs::paste};
        //
        // juce::ApplicationCommandInfo undo{juce::StandardApplicationCommandIDs::undo};
        // juce::ApplicationCommandInfo redo{juce::StandardApplicationCommandIDs::redo};
    // };

}