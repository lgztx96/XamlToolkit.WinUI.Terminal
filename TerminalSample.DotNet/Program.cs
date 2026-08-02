using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Settings;
using System;

#if DISABLE_XAML_GENERATED_MAIN

namespace TerminalSample.DotNet;

file static class Program
{
    [STAThread]
    public static void Main()
    {
        XamlOptionalChanges.EnableChange(XamlChangeId.DefaultStyleOptimizations);
        XamlOptionalChanges.EnableChange(XamlChangeId.DeferContextFlyoutInit);
        XamlOptionalChanges.EnableChange(XamlChangeId.IconNoGridOptimization);
        XamlOptionalChanges.EnableChange(XamlChangeId.OptimizeApplyStyles);

        Application.Start(static (p) => _ = new App());
    }
}
#endif