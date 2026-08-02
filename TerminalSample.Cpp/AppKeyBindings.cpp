#include "pch.h"
#include "AppKeyBindings.h"

namespace winrt::TerminalSample::Cpp::implementation
{
    using namespace Microsoft::Terminal::Control;
    using namespace Windows::System;

    constexpr VirtualKeyModifiers operator|(
        VirtualKeyModifiers lhs,
        VirtualKeyModifiers rhs) noexcept
    {
        return static_cast<VirtualKeyModifiers>(
            std::to_underlying(lhs) |
            std::to_underlying(rhs));
    }

    AppKeyBindings::AppKeyBindings(TermControl const& termControl)
        : m_termControl(termControl)
    {
    }

    bool AppKeyBindings::TryKeyChord(KeyChord const& kc)
    {
        switch (kc.Vkey())
        {
        case VK_C: return HandleCopy(kc.Modifiers());
        case VK_V: return HandlePaste(kc.Modifiers());
        default:   return false;
        }
    }

    bool AppKeyBindings::HandleCopy(VirtualKeyModifiers mods)
    {
        constexpr auto Ctrl = VirtualKeyModifiers::Control;
        constexpr auto CtrlShift = VirtualKeyModifiers::Control | VirtualKeyModifiers::Shift;

        bool dismissSelection;

        if (mods == Ctrl)
            dismissSelection = true;
        else if (mods == CtrlShift)
            dismissSelection = false;
        else
            return false;

        auto text = m_termControl.SelectedText(false);

        if (text.empty())
            return false;

        m_termControl.CopySelectionToClipboard(
            dismissSelection,
            false,   // singleLine
            false,   // withControlSequences
            CopyFormat::None);

        return true;
    }

    bool AppKeyBindings::HandlePaste(VirtualKeyModifiers mods)
    {
        constexpr auto Ctrl = VirtualKeyModifiers::Control;
        constexpr auto CtrlShift = VirtualKeyModifiers::Control | VirtualKeyModifiers::Shift;

        if (mods == Ctrl || mods == CtrlShift)
        {
            m_termControl.PasteTextFromClipboard();
            return true;
        }

        return false;
    }

    bool AppKeyBindings::IsKeyChordExplicitlyUnbound(KeyChord const& /*kc*/)
    {
        return false;
    }
}
