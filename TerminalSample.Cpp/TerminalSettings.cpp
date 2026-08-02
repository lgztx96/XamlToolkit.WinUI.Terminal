#include "pch.h"
#include "TerminalSettings.h"

namespace winrt::TerminalSample::Cpp::implementation
{
    // ==================== Color Tables ====================

    const std::array<Color, 16>& TerminalSettings::DarkColorTable()
    {
        static const std::array<Color, 16> table =
        {
            Color{ 40,  44,  52,  255 },   // Black       #282C34
            Color{ 224, 108, 117, 255 },   // Red         #E06C75
            Color{ 152, 195, 121, 255 },   // Green       #98C379
            Color{ 229, 192, 123, 255 },   // Yellow      #E5C07B
            Color{ 97,  175, 239, 255 },   // Blue        #61AFEF
            Color{ 198, 120, 221, 255 },   // Purple      #C678DD
            Color{ 86,  182, 194, 255 },   // Cyan        #56B6C2
            Color{ 220, 223, 228, 255 },   // White       #DCDFE4
            Color{ 90,  99,  116, 255 },   // BrightBlack #5A6374
            Color{ 224, 108, 117, 255 },   // BrightRed   #E06C75
            Color{ 152, 195, 121, 255 },   // BrightGreen #98C379
            Color{ 229, 192, 123, 255 },   // BrightYellow#E5C07B
            Color{ 97,  175, 239, 255 },   // BrightBlue  #61AFEF
            Color{ 198, 120, 221, 255 },   // BrightPurple#C678DD
            Color{ 86,  182, 194, 255 },   // BrightCyan  #56B6C2
            Color{ 220, 223, 228, 255 },   // BrightWhite #DCDFE4
        };
        return table;
    }

    const std::array<Color, 16>& TerminalSettings::LightColorTable()
    {
        static const std::array<Color, 16> table =
        {
            Color{ 56,  58,  66,  255 },   // Black       #383A42
            Color{ 228, 86,  73,  255 },   // Red         #E45649
            Color{ 80,  161, 79,  255 },   // Green       #50A14F
            Color{ 193, 131, 1,   255 },   // Yellow      #C18301
            Color{ 1,   132, 188, 255 },   // Blue        #0184BC
            Color{ 166, 38,  164, 255 },   // Purple      #A626A4
            Color{ 9,   151, 179, 255 },   // Cyan        #0997B3
            Color{ 250, 250, 250, 255 },   // White       #FAFAFA
            Color{ 79,  82,  93,  255 },   // BrightBlack #4F525D
            Color{ 223, 108, 117, 255 },   // BrightRed   #DF6C75
            Color{ 152, 195, 121, 255 },   // BrightGreen #98C379
            Color{ 228, 192, 122, 255 },   // BrightYellow#E4C07A
            Color{ 97,  175, 239, 255 },   // BrightBlue  #61AFEF
            Color{ 197, 119, 221, 255 },   // BrightPurple#C577DD
            Color{ 86,  181, 193, 255 },   // BrightCyan  #56B5C1
            Color{ 255, 255, 255, 255 },   // BrightWhite #FFFFFF
        };
        return table;
    }

    // ==================== Construction ====================

    TerminalSettings::TerminalSettings(bool isDark) : IsDark(isDark)
    {
    }

    // ==================== ICoreScheme ====================

    void TerminalSettings::GetColorTable(winrt::com_array<Color>& table)
    {
        auto const& src = IsDark() ? DarkColorTable() : LightColorTable();
        table = winrt::com_array<Color>(src.begin(), src.end());
    }

    Color TerminalSettings::CursorColor() const
    {
        return IsDark()
            ? Color{ 255, 255, 255, 255 }
            : Color{ 79,  82,  93,  255 };
    }

    Color TerminalSettings::DefaultBackground() const
    {
        return IsDark()
            ? Color{ 40,  44,  52,  255 }
            : Color{ 250, 250, 250, 255 };
    }

    Color TerminalSettings::DefaultForeground() const
    {
        return IsDark()
            ? Color{ 220, 223, 228, 255 }
            : Color{ 56,  58,  66,  255 };
    }

    Color TerminalSettings::SelectionBackground() const
    {
        return IsDark()
            ? Color{ 220, 223, 228, 255 }
            : Color{ 56,  58,  66,  255 };
    }
}
