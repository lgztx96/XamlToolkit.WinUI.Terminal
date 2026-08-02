using Microsoft.Terminal.Control;
using Microsoft.Terminal.TerminalConnection;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Media;
using System;
using System.Collections.Generic;
using Windows.ApplicationModel.DataTransfer;

namespace TerminalSample.DotNet;

public sealed partial class MainWindow : Window
{
    private readonly TerminalSettings _terminalSettings;

    public MainWindow()
    {
        InitializeComponent();

        ExtendsContentIntoTitleBar = true;
        SetTitleBar(AppTitleBar);

        _terminalSettings = new(App.Current.RequestedTheme is ApplicationTheme.Dark);
    }

    private void OnActualThemeChanged(FrameworkElement sender, object args)
    {
        _terminalSettings.IsDark =
            sender.ActualTheme == ElementTheme.Dark ||
            (sender.ActualTheme == ElementTheme.Default 
            && App.Current.RequestedTheme is ApplicationTheme.Dark);
        
        foreach (var item in TerminalHost.TabItems) 
        {
            if (item is TabViewItem { Content: TermControl tc })
            {
                tc.UpdateControlSettings(_terminalSettings);
            } 
        }
    }

    private void OnWindowClosed(object sender, WindowEventArgs args)
    {
        CloseAllTabs();
    }

    private void OnAddTabButtonClick(TabView sender, object args)
    {
        var tab = CreateTerminalTab();
        sender.TabItems.Add(tab);
        sender.SelectedItem = tab;
    }

    /// <summary>
    /// Creates a new terminal tab with the current theme.
    /// </summary>
    private TabViewItem CreateTerminalTab()
    {
        var connectionSettings = ConptyConnection.CreateSettings(
            cmdline: "cmd.exe /k echo Welcome to Windows Terminal && echo Running in-proc with WinUI 3",
            startingDirectory: "C:\\",
            startingTitle: string.Empty,
            reloadEnvironmentVariables: false,
            initialEnvironment: string.Empty,
            environmentOverrides: new Dictionary<string, string>(),
            rows: 32,
            columns: 80,
            guid: Guid.NewGuid(),
            profileGuid: Guid.NewGuid()
        );

        var hWnd = WinRT.Interop.WindowNative.GetWindowHandle(this);
        var conn = new ConptyConnection();
        conn.Initialize(connectionSettings);
        conn.ReparentWindow((ulong)hWnd);

        var termControl = new TermControl(_terminalSettings, _terminalSettings, conn)
        {
            OwningHwnd = (ulong)hWnd
        };

        termControl.WriteToClipboard += OnWriteToClipboard;

        termControl.PasteFromClipboard += OnPasteFromClipboard;

        termControl.KeyBindings(new AppKeyBindings(termControl));

        termControl.CloseTerminalRequested += (_, _) =>
        {
            termControl.Close();
            RemoveTerminalTab(termControl);
        };

        var tabItem = new TabViewItem
        {
            Content = termControl,
            Header = "cmd",
            IconSource = new FontIconSource { FontFamily = new FontFamily("Segoe Fluent Icons"), Glyph = "\uE756" }
        };

        termControl.TitleChanged += (_, args) =>
        {
            if (!string.IsNullOrEmpty(args.Title))
            {
                DispatcherQueue.TryEnqueue(() => tabItem.Header = args.Title);
            }
        };

        termControl.OpenHyperlink += (_, args) => 
        {
            _ = Windows.System.Launcher.LaunchUriAsync(new Uri(args.Uri));
        };

        return tabItem;
    }

    private void OnWriteToClipboard(object sender, WriteToClipboardEventArgs args)
    {
        var dataPackage = new DataPackage();

        if (args.Plain != null)
        {
            dataPackage.SetText(args.Plain);
        }

        if (args.Html != null)
        {
            dataPackage.SetHtmlFormat(System.Text.Encoding.UTF8.GetString(args.Html));
        }

        if (args.Rtf != null)
        {
            dataPackage.SetRtf(System.Text.Encoding.UTF8.GetString(args.Rtf));
        }

        Clipboard.SetContent(dataPackage);
    }

    private void CloseAllTabs()
    {
        foreach (var tab in TerminalHost.TabItems)
        {
            if (tab is TabViewItem { Content: TermControl tc })
            {
                tc.Close();
            }
        }
        TerminalHost.TabItems.Clear();
    }

    private static async void OnPasteFromClipboard(object sender, PasteFromClipboardEventArgs args)
    {
        try
        {
            var content = Clipboard.GetContent();
            if (content.Contains(StandardDataFormats.Text))
            {
                var text = await content.GetTextAsync();
                if (!string.IsNullOrEmpty(text))
                {
                    args.HandleClipboardData(text);
                }
            }
        }
        catch
        {

        }
    }

    private void RemoveTerminalTab(TermControl termControl)
    {
        for (int i = TerminalHost.TabItems.Count - 1; i >= 0; i--)
        {
            if (TerminalHost.TabItems[i] is TabViewItem { Content: TermControl tc }
                && tc == termControl)
            {
                TerminalHost.TabItems.RemoveAt(i);
                break;
            }
        }
    }

#pragma warning disable CA1822
    private void OnTabCloseRequested(TabView sender, TabViewTabCloseRequestedEventArgs args)
#pragma warning restore CA1822
    {
        if (args.Tab is TabViewItem { Content: TermControl tc })
        {
            tc.Close();
        }
        sender.TabItems.Remove(args.Tab);
    }
}

