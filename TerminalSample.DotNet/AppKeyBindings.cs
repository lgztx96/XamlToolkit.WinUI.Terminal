using Microsoft.Terminal.Control;
using Windows.System;

namespace TerminalSample.DotNet;

internal sealed partial class AppKeyBindings(TermControl termControl) : IKeyBindings
{
    private const int VK_C = 67;
    private const int VK_V = 86;

    private const VirtualKeyModifiers Ctrl = VirtualKeyModifiers.Control;
    private const VirtualKeyModifiers CtrlShift = VirtualKeyModifiers.Control | VirtualKeyModifiers.Shift;

    public bool TryKeyChord(KeyChord kc)
    {
        return kc.Vkey switch
        {
            VK_C => HandleCopy(kc.Modifiers),
            VK_V => HandlePaste(kc.Modifiers),
            _ => false
        };
    }

    private bool HandleCopy(VirtualKeyModifiers mods)
    {
        bool dismissSelection;

        if (mods == Ctrl)
            dismissSelection = true;
        else if (mods == CtrlShift)
            dismissSelection = false;
        else
            return false;

        var text = termControl.SelectedText(trimTrailingWhitespace: false);

        if (string.IsNullOrEmpty(text))
            return false; // No selection — let ^C through as SIGINT

        termControl.CopySelectionToClipboard(
               dismissSelection: dismissSelection,
               singleLine: false,
               withControlSequences: false,
               formats: CopyFormat.None);

        return true;
    }

    private bool HandlePaste(VirtualKeyModifiers mods)
    {
        if (mods is Ctrl or CtrlShift)
        {
            termControl.PasteTextFromClipboard();
            return true;
        }

        return false;
    }

    public bool IsKeyChordExplicitlyUnbound(KeyChord kc) => false;
}
