#pragma once

#include <winrt/Windows.UI.Text.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Microsoft.Terminal.Core.h>
#include <winrt/Microsoft.Terminal.Control.h>
#include <winrt/Microsoft.Terminal.Settings.Model.h>
#include <winrt/Microsoft.Terminal.TerminalConnection.h>
#include <wil/wistd_type_traits.h>
#include <wil/cppwinrt_authoring.h>

namespace winrt::TerminalSample::Cpp::implementation
{
    using namespace Microsoft::Terminal::Core;
    using namespace Microsoft::Terminal::Control;
    using namespace Microsoft::UI::Xaml;
    using namespace Microsoft::UI::Xaml::Media;
    using namespace Windows::Foundation;
    using namespace Windows::Foundation::Collections;
    using namespace Windows::UI::Text;

    struct TerminalSettings : winrt::implements<TerminalSettings,
        Microsoft::Terminal::Control::IControlSettings,
        Microsoft::Terminal::Core::ICoreSettings,
        Microsoft::Terminal::Control::IControlAppearance,
        Microsoft::Terminal::Core::ICoreAppearance,
        Microsoft::Terminal::Core::ICoreScheme>
    {
        TerminalSettings(bool isDark = true);

        wil::single_threaded_rw_property<bool> IsDark;

        // ==================== ICoreScheme ====================
        void GetColorTable(winrt::com_array<Color>& table);
        Color CursorColor() const;
        Color DefaultBackground() const;
        Color DefaultForeground() const;
        Color SelectionBackground() const;

        // ==================== ICoreAppearance ====================
        wil::single_threaded_rw_property<AdjustTextMode> AdjustIndistinguishableColors = AdjustTextMode::Automatic;
        wil::single_threaded_rw_property<uint32_t> CursorHeight = 25;
        wil::single_threaded_rw_property<CursorStyle> CursorShape = CursorStyle::Vintage;
        wil::single_threaded_rw_property<bool> IntenseIsBold = false;
        wil::single_threaded_rw_property<bool> IntenseIsBright = true;

        // ==================== IControlAppearance ====================
        wil::single_threaded_rw_property<winrt::hstring> BackgroundImage;
        wil::single_threaded_rw_property<HorizontalAlignment> BackgroundImageHorizontalAlignment = HorizontalAlignment::Center;
        wil::single_threaded_rw_property<float> BackgroundImageOpacity = 1.0f;
        wil::single_threaded_rw_property<Stretch> BackgroundImageStretchMode = Stretch::UniformToFill;
        wil::single_threaded_rw_property<VerticalAlignment> BackgroundImageVerticalAlignment = VerticalAlignment::Center;
        wil::single_threaded_rw_property<float> Opacity = 1.0f;
        wil::single_threaded_rw_property<winrt::hstring> PixelShaderImagePath;
        wil::single_threaded_rw_property<winrt::hstring> PixelShaderPath;
        wil::single_threaded_rw_property<bool> RetroTerminalEffect = false;
        wil::single_threaded_rw_property<bool> UseAcrylic = false;

        // ==================== ICoreSettings ====================
        wil::single_threaded_rw_property<bool> AllowKittyKeyboardMode = true;
        wil::single_threaded_rw_property<bool> AllowVtChecksumReport = false;
        wil::single_threaded_rw_property<bool> AllowVtClipboardWrite = true;
        wil::single_threaded_rw_property<bool> AltGrAliasing = true;
        wil::single_threaded_rw_property<winrt::hstring> AnswerbackMessage;
        wil::single_threaded_rw_property<bool> AutoMarkPrompts = false;
        wil::single_threaded_rw_property<bool> DetectURLs = true;
        wil::single_threaded_rw_property<bool> ForceVTInput = false;
        wil::single_threaded_rw_property<int32_t> HistorySize = 9001;
        wil::single_threaded_rw_property<int32_t> InitialCols = 80;
        wil::single_threaded_rw_property<int32_t> InitialRows = 30;
        wil::single_threaded_rw_property<bool> RainbowSuggestions = true;
        wil::single_threaded_rw_property<bool> SnapOnInput = true;
        wil::single_threaded_rw_property<IReference<Color>> StartingTabColor = nullptr;
        wil::single_threaded_rw_property<winrt::hstring> StartingTitle;
        wil::single_threaded_rw_property<bool> SuppressApplicationTitle = false;
        wil::single_threaded_rw_property<IReference<Color>> TabColor = nullptr;
        wil::single_threaded_rw_property<bool> TrimBlockSelection = true;
        wil::single_threaded_rw_property<winrt::hstring> WordDelimiters = L" ./\\()\"'-:,.;<>~!@#$%^&*|+=[]{}~?│";

        // ==================== IControlSettings ====================
        wil::single_threaded_rw_property<AmbiguousWidth> AmbiguousWidth = AmbiguousWidth::Narrow;
        wil::single_threaded_rw_property<TextAntialiasingMode> AntialiasingMode = TextAntialiasingMode::Grayscale;
        wil::single_threaded_rw_property<winrt::hstring> CellHeight;
        wil::single_threaded_rw_property<winrt::hstring> CellWidth;
        wil::single_threaded_rw_property<winrt::hstring> Commandline;
        wil::single_threaded_rw_property<CopyFormat> CopyFormatting = CopyFormat::None;
        wil::single_threaded_rw_property<bool> CopyOnSelect = true;
        wil::single_threaded_rw_property<DefaultInputScope> DefaultInputScope = DefaultInputScope::Default;
        wil::single_threaded_rw_property<bool> DisablePartialInvalidation = false;
        wil::single_threaded_rw_property<winrt::hstring> DragDropDelimiter = L" ";
        wil::single_threaded_rw_property<bool> EnableBuiltinGlyphs = true;
        wil::single_threaded_rw_property<bool> EnableColorGlyphs = true;
        wil::single_threaded_rw_property<bool> EnableUnfocusedAcrylic = false;
        wil::single_threaded_rw_property<bool> FocusFollowMouse = false;
        wil::single_threaded_rw_property<IMap<winrt::hstring, float>> FontAxes = nullptr;
        wil::single_threaded_rw_property<winrt::hstring> FontFace = L"Cascadia Mono";
        wil::single_threaded_rw_property<IMap<winrt::hstring, float>> FontFeatures = nullptr;
        wil::single_threaded_rw_property<float> FontSize = 12.0f;
        wil::single_threaded_rw_property<FontWeight> FontWeight = Windows::UI::Text::FontWeight{ 400 };
        wil::single_threaded_rw_property<GraphicsAPI> GraphicsAPI = GraphicsAPI::Automatic;
        wil::single_threaded_rw_property<winrt::hstring> Padding = L"8, 8, 8, 8";
        wil::single_threaded_rw_property<PathTranslationStyle> PathTranslationStyle = PathTranslationStyle::None;
        wil::single_threaded_rw_property<bool> RepositionCursorWithMouse = false;
        wil::single_threaded_rw_property<bool> RightClickContextMenu = false;
        wil::single_threaded_rw_property<ScrollbarState> ScrollState = ScrollbarState::Visible;
        wil::single_threaded_rw_property<bool> ScrollToChangeOpacity = true;
        wil::single_threaded_rw_property<bool> ScrollToZoom = true;
        wil::single_threaded_rw_property<winrt::guid> SessionId;
        wil::single_threaded_rw_property<bool> ShowMarks = false;
        wil::single_threaded_rw_property<bool> SoftwareRendering = false;
        wil::single_threaded_rw_property<winrt::hstring> StartingDirectory;
        wil::single_threaded_rw_property<TextMeasurement> TextMeasurement = TextMeasurement::Graphemes;
        wil::single_threaded_rw_property<bool> UseBackgroundImageForWindow = false;

    private:
        static const std::array<Color, 16>& DarkColorTable();
        static const std::array<Color, 16>& LightColorTable();
    };
}
