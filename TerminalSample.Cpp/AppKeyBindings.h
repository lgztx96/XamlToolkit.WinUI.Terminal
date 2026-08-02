#pragma once
#include <winrt/Microsoft.Terminal.Core.h>
#include <winrt/Microsoft.Terminal.Control.h>
#include <winrt/Microsoft.Terminal.Settings.Model.h>
#include <winrt/Microsoft.Terminal.TerminalConnection.h>

namespace winrt::TerminalSample::Cpp::implementation
{
    struct AppKeyBindings : winrt::implements<AppKeyBindings,
        Microsoft::Terminal::Control::IKeyBindings>
    {
        AppKeyBindings(Microsoft::Terminal::Control::TermControl const& termControl);

        bool TryKeyChord(Microsoft::Terminal::Control::KeyChord const& kc);
        bool IsKeyChordExplicitlyUnbound(Microsoft::Terminal::Control::KeyChord const& kc);

    private:
        bool HandleCopy(Windows::System::VirtualKeyModifiers mods);
        bool HandlePaste(Windows::System::VirtualKeyModifiers mods);

        Microsoft::Terminal::Control::TermControl m_termControl{ nullptr };

        static constexpr int VK_C = 67;
        static constexpr int VK_V = 86;
    };
}
