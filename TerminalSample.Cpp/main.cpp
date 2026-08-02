#include "pch.h"
#include "App.xaml.h"
#include <winrt/Microsoft.UI.Xaml.Settings.h>

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow)
{
    winrt::init_apartment(winrt::apartment_type::single_threaded);

    using namespace winrt::Microsoft::UI::Xaml;
    using namespace winrt::Microsoft::UI::Xaml::Settings;

    XamlOptionalChanges::EnableChange(XamlChangeId::DefaultStyleOptimizations);
    XamlOptionalChanges::EnableChange(XamlChangeId::DeferContextFlyoutInit);
    XamlOptionalChanges::EnableChange(XamlChangeId::IconNoGridOptimization);
    XamlOptionalChanges::EnableChange(XamlChangeId::OptimizeApplyStyles);

    Application::Start([](auto&&) static
    { 
        winrt::make<winrt::TerminalSample::Cpp::implementation::App>(); 
    });

    return 0;
}