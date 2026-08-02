#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include <microsoft.ui.xaml.window.h>
#include <winrt/Microsoft.UI.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.ApplicationModel.DataTransfer.h>
#include "AppKeyBindings.h"

using namespace winrt::Windows::Foundation;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls;
using namespace winrt::Microsoft::UI::Xaml::Media;
using namespace winrt::Microsoft::Terminal::Control;
using namespace winrt::Microsoft::Terminal::TerminalConnection;
using namespace winrt::Windows::ApplicationModel::DataTransfer;

namespace winrt::TerminalSample::Cpp::implementation
{
    void MainWindow::InitializeComponent()
    {
        MainWindowT::InitializeComponent();

        ExtendsContentIntoTitleBar(true);
        SetTitleBar(AppTitleBar());

        bool isDark = Application::Current().RequestedTheme() == ApplicationTheme::Dark;
        m_terminalSettings = winrt::make_self<TerminalSettings>(isDark);
    }

    void MainWindow::OnWindowClosed(IInspectable const& /*sender*/, WindowEventArgs const& /*args*/)
    {
        CloseAllTabs();
    }

    void MainWindow::OnActualThemeChanged(FrameworkElement const& sender, IInspectable const& /*args*/)
    {
        bool isDark = sender.ActualTheme() == ElementTheme::Dark ||
                      (sender.ActualTheme() == ElementTheme::Default &&
                       Application::Current().RequestedTheme() == ApplicationTheme::Dark);

        m_terminalSettings->IsDark(isDark);

        for (const auto& item : TerminalHost().TabItems())
        {
            if (auto tabItem = item.try_as<TabViewItem>())
            {
                if (auto tc = tabItem.Content().try_as<TermControl>())
                {
                    tc.UpdateControlSettings(*m_terminalSettings);
                }
            }
        }
    }

    void MainWindow::OnAddTabButtonClick(TabView const& sender, IInspectable const& /*args*/)
    {
        auto tab = CreateTerminalTab();
        sender.TabItems().Append(tab);
        sender.SelectedItem(tab);
    }

    void MainWindow::OnTabCloseRequested(TabView const& sender, TabViewTabCloseRequestedEventArgs const& args)
    {
        if (auto tc = args.Tab().Content().try_as<TermControl>())
        {
            tc.Close();
        }

        uint32_t index;
        if (auto items = sender.TabItems(); items.IndexOf(args.Tab(), index))
        {
            items.RemoveAt(index);
        }
    }

    TabViewItem MainWindow::CreateTerminalTab()
    {
        auto connectionSettings = ConptyConnection::CreateSettings(
            L"cmd.exe /k echo Welcome to Windows Terminal && echo Running in-proc with WinUI 3 (C++/WinRT)",
            L"C:\\",
            L"",
            false,   // reloadEnvironmentVariables
            L"",
            nullptr, // environmentOverrides
            32,      // rows
            80,      // columns
            winrt::guid(),  // profileGuid
            winrt::guid()   // guid
        );

        auto windowNative{ this->m_inner.as<::IWindowNative>() };
        HWND hWnd{ 0 };
        windowNative->get_WindowHandle(&hWnd);

        ConptyConnection conn;
        conn.Initialize(connectionSettings);
        conn.ReparentWindow(reinterpret_cast<std::uintptr_t>(hWnd));

        TermControl termControl(*m_terminalSettings, *m_terminalSettings, conn);
        termControl.OwningHwnd(reinterpret_cast<std::uintptr_t>(hWnd));

        termControl.WriteToClipboard({ this, &MainWindow::OnWriteToClipboard });

        termControl.PasteFromClipboard(&MainWindow::OnPasteFromClipboard);

        auto keyBindings = winrt::make<AppKeyBindings>(termControl);
        termControl.KeyBindings(keyBindings);

        termControl.CloseTerminalRequested([this, termControl](auto&&, auto&&)
        {
            termControl.Close();
            this->RemoveTerminalTab(termControl);
        });

        TabViewItem tabItem;
        tabItem.Content(termControl);
        tabItem.Header(box_value(L"cmd"));

        FontIconSource iconSource;
        iconSource.FontFamily(FontFamily(L"Segoe Fluent Icons"));
        iconSource.Glyph(L"\uE756");
        tabItem.IconSource(iconSource);

        // 10. Sync terminal title to tab header
        termControl.TitleChanged([tabItem](auto const&, auto const& args) 
        {
            if (auto title = args.Title(); !title.empty())
            {
                tabItem.DispatcherQueue().TryEnqueue([tabItem, title]() 
                {
                    tabItem.Header(box_value(title));
                });
            }
        });

        termControl.OpenHyperlink([](auto const&, auto const& args)
        {
            Windows::System::Launcher::LaunchUriAsync(Uri(args.Uri()));
        });

        return tabItem;
    }

    void MainWindow::CloseAllTabs()
    {
        auto tabs = TerminalHost().TabItems();
        for (auto const& tab : tabs)
        {
            if (auto tabItem = tab.try_as<TabViewItem>())
            {
                if (auto tc = tabItem.Content().try_as<TermControl>())
                {
                    tc.Close();
                }
            }
        }
        tabs.Clear();
    }

    void MainWindow::RemoveTerminalTab(TermControl const& termControl)
    {
        auto tabs = TerminalHost().TabItems();
        for (int32_t i = static_cast<int32_t>(tabs.Size()) - 1; i >= 0; --i)
        {
            auto tab = tabs.GetAt(static_cast<uint32_t>(i));
            if (auto tabItem = tab.try_as<TabViewItem>())
            {
                if (auto tc = tabItem.Content().try_as<TermControl>())
                {
                    if (tc == termControl)
                    {
                        tabs.RemoveAt(static_cast<uint32_t>(i));
                        break;
                    }
                }
            }
        }
    }

    // ==================== Clipboard Handlers ====================

    void MainWindow::OnWriteToClipboard(IInspectable const& /*sender*/, WriteToClipboardEventArgs const& args)
    {
        DataPackage dataPackage;

        if (auto plain = args.Plain(); !plain.empty())
        {
            dataPackage.SetText(plain);
        }

        if (auto html = args.Html(); !html.empty())
        {
            std::string htmlStr(html.begin(), html.end());
            dataPackage.SetHtmlFormat(winrt::to_hstring(htmlStr));
        }

        if (auto rtf = args.Rtf(); !rtf.empty())
        {
            std::string rtfStr(rtf.begin(), rtf.end());
            dataPackage.SetRtf(winrt::to_hstring(rtfStr));
        }

        Clipboard::SetContent(dataPackage);
    }

    winrt::fire_and_forget MainWindow::OnPasteFromClipboard(IInspectable const& /*sender*/, PasteFromClipboardEventArgs args)
    {
        try
        {
            auto content = Clipboard::GetContent();
            if (content.Contains(StandardDataFormats::Text()))
            {
                auto text = co_await content.GetTextAsync();
                if (!text.empty())
                {
                    args.HandleClipboardData(text);
                }
            }
        }
        catch (...)
        {

        }
    }
}
