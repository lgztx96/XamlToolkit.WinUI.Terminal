#pragma once

#include "MainWindow.g.h"
#include "TerminalSettings.h"

namespace winrt::TerminalSample::Cpp::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow() = default;

        void InitializeComponent();

        void OnWindowClosed(winrt::Windows::Foundation::IInspectable const& sender,
                            winrt::Microsoft::UI::Xaml::WindowEventArgs const& args);
        void OnActualThemeChanged(winrt::Microsoft::UI::Xaml::FrameworkElement const& sender,
                                  winrt::Windows::Foundation::IInspectable const& args);
        void OnAddTabButtonClick(winrt::Microsoft::UI::Xaml::Controls::TabView const& sender,
                                 winrt::Windows::Foundation::IInspectable const& args);
        void OnTabCloseRequested(winrt::Microsoft::UI::Xaml::Controls::TabView const& sender,
                                 winrt::Microsoft::UI::Xaml::Controls::TabViewTabCloseRequestedEventArgs const& args);

    private:
        winrt::Microsoft::UI::Xaml::Controls::TabViewItem CreateTerminalTab();
        void CloseAllTabs();
        void RemoveTerminalTab(winrt::Microsoft::Terminal::Control::TermControl const& termControl);

        void OnWriteToClipboard(winrt::Windows::Foundation::IInspectable const& sender,
                                winrt::Microsoft::Terminal::Control::WriteToClipboardEventArgs const& args);
        static winrt::fire_and_forget OnPasteFromClipboard(winrt::Windows::Foundation::IInspectable const& sender,
                                                     winrt::Microsoft::Terminal::Control::PasteFromClipboardEventArgs args);

        winrt::com_ptr<TerminalSettings> m_terminalSettings;
    };
}

namespace winrt::TerminalSample::Cpp::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
