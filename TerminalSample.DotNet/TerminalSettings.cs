using Microsoft.Terminal.Control;
using Microsoft.Terminal.Core;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Media;
using System;
using System.Collections.Generic;
using Windows.UI.Text;

namespace TerminalSample.DotNet;

internal sealed partial class TerminalSettings(bool isDark = true) : IControlSettings
{
    // ==================== Color Tables (ICoreScheme) ====================

    /// <summary>
    /// One Half Dark scheme — from Terminal defaults.json:196.
    /// </summary>
    private static readonly Color[] OneHalfDarkColorTable =
    [
        // 0..7:  normal
        new Color(40,  44,  52,  255),   // Black       #282C34
        new Color(224, 108, 117, 255),   // Red         #E06C75
        new Color(152, 195, 121, 255),   // Green       #98C379
        new Color(229, 192, 123, 255),   // Yellow      #E5C07B
        new Color(97,  175, 239, 255),   // Blue        #61AFEF
        new Color(198, 120, 221, 255),   // Purple      #C678DD
        new Color(86,  182, 194, 255),   // Cyan        #56B6C2
        new Color(220, 223, 228, 255),   // White       #DCDFE4
        // 8..15: bright
        new Color(90,  99,  116, 255),   // BrightBlack #5A6374
        new Color(224, 108, 117, 255),   // BrightRed   #E06C75
        new Color(152, 195, 121, 255),   // BrightGreen #98C379
        new Color(229, 192, 123, 255),   // BrightYellow#E5C07B
        new Color(97,  175, 239, 255),   // BrightBlue  #61AFEF
        new Color(198, 120, 221, 255),   // BrightPurple#C678DD
        new Color(86,  182, 194, 255),   // BrightCyan  #56B6C2
        new Color(220, 223, 228, 255),   // BrightWhite #DCDFE4
    ];

    /// <summary>
    /// One Half Light scheme — from Terminal defaults.json:218.
    /// Light terminal theme that pairs well with the system light mode.
    /// </summary>
    private static readonly Color[] OneHalfLightColorTable =
    [
        // 0..7:  normal
        new Color(56,  58,  66,  255),   // Black       #383A42
        new Color(228, 86,  73,  255),   // Red         #E45649
        new Color(80,  161, 79,  255),   // Green       #50A14F
        new Color(193, 131, 1,   255),   // Yellow      #C18301
        new Color(1,   132, 188, 255),   // Blue        #0184BC
        new Color(166, 38,  164, 255),   // Purple      #A626A4
        new Color(9,   151, 179, 255),   // Cyan        #0997B3
        new Color(250, 250, 250, 255),   // White       #FAFAFA
        // 8..15: bright
        new Color(79,  82,  93,  255),   // BrightBlack #4F525D
        new Color(223, 108, 117, 255),   // BrightRed   #DF6C75
        new Color(152, 195, 121, 255),   // BrightGreen #98C379
        new Color(228, 192, 122, 255),   // BrightYellow#E4C07A
        new Color(97,  175, 239, 255),   // BrightBlue  #61AFEF
        new Color(197, 119, 221, 255),   // BrightPurple#C577DD
        new Color(86,  181, 193, 255),   // BrightCyan  #56B5C1
        new Color(255, 255, 255, 255),   // BrightWhite #FFFFFF
    ];

    /// <summary>
    /// Gets or sets the theme. TermControl reads color properties on every
    /// render frame, so flipping this flag immediately switches between
    /// Campbell (dark) and One Half Light (light) color schemes.
    /// </summary>
    public bool IsDark
    {
        get => isDark;
        set => isDark = value;
    }

    // ==================== ICoreScheme ====================

    public void GetColorTable(out Color[] table)
    {
        table = isDark ? OneHalfDarkColorTable : OneHalfLightColorTable;
    }

    public Color CursorColor => isDark
        ? new Color(255, 255, 255, 255)   // #FFFFFF
        : new Color(79,  82,  93,  255);  // One Half Light #4F525D

    public Color DefaultForeground => isDark
        ? new Color(220, 223, 228, 255)   // One Half Dark #DCDFE4
        : new Color(56,  58,  66,  255);  // One Half Light #383A42

    public Color DefaultBackground => isDark
        ? new Color(40,  44,  52,  255)   // One Half Dark #282C34
        : new Color(250, 250, 250, 255);  // One Half Light #FAFAFA

    public Color SelectionBackground => isDark
        ? new Color(220, 223, 228, 255)   // One Half Dark foreground
        : new Color(56,  58,  66,  255);  // One Half Light #383A42

    // ==================== ICoreAppearance ====================

    public AdjustTextMode AdjustIndistinguishableColors { get; set; } = AdjustTextMode.Automatic;

    public uint CursorHeight { get; set; } = 25;

    public CursorStyle CursorShape { get; set; } = CursorStyle.Vintage;

    public bool IntenseIsBold { get; set; } = false;

    public bool IntenseIsBright { get; set; } = true;

    // ==================== IControlAppearance ====================

    public string BackgroundImage { get; set; } = string.Empty;

    public HorizontalAlignment BackgroundImageHorizontalAlignment { get; set; } = HorizontalAlignment.Center;

    public float BackgroundImageOpacity { get; set; } = 1.0f;

    public Stretch BackgroundImageStretchMode { get; set; } = Stretch.UniformToFill;

    public VerticalAlignment BackgroundImageVerticalAlignment { get; set; } = VerticalAlignment.Center;

    public float Opacity { get; set; } = 1.0f;

    public string PixelShaderImagePath { get; set; } = string.Empty;

    public string PixelShaderPath { get; set; } = string.Empty;

    public bool RetroTerminalEffect { get; set; } = false;

    public bool UseAcrylic { get; set; } = false;

    // ==================== ICoreSettings ====================

    public bool AllowKittyKeyboardMode { get; set; } = true;

    public bool AllowVtChecksumReport { get; set; } = false;

    public bool AllowVtClipboardWrite { get; set; } = true;

    public bool AltGrAliasing { get; set; } = true;

    public string AnswerbackMessage { get; set; } = string.Empty;

    public bool AutoMarkPrompts { get; set; } = false;

    public bool DetectURLs { get; set; } = true;

    public bool ForceVTInput { get; set; } = false;

    public int HistorySize { get; set; } = 9001;

    public int InitialCols { get; set; } = 80;

    public int InitialRows { get; set; } = 30;

    public bool RainbowSuggestions { get; set; } = true;

    public bool SnapOnInput { get; set; } = true;

    public Color? StartingTabColor { get; set; } = null;

    public string StartingTitle { get; set; } = string.Empty;

    public bool SuppressApplicationTitle { get; set; } = false;

    public Color? TabColor { get; set; } = null;

    public bool TrimBlockSelection { get; set; } = true;

    public string WordDelimiters { get; set; } = " ./\\()\"'-:,.;<>~!@#$%^&*|+=[]{}~?│";

    // ==================== IControlSettings ====================

    public AmbiguousWidth AmbiguousWidth { get; set; } = AmbiguousWidth.Narrow;

    public TextAntialiasingMode AntialiasingMode { get; set; } = TextAntialiasingMode.Grayscale;

    public string CellHeight { get; set; } = string.Empty;

    public string CellWidth { get; set; } = string.Empty;

    public string Commandline { get; set; } = string.Empty;

    public CopyFormat CopyFormatting { get; set; } = CopyFormat.None;

    public bool CopyOnSelect { get; set; } = true;

    public DefaultInputScope DefaultInputScope { get; set; } = DefaultInputScope.Default;

    public bool DisablePartialInvalidation { get; set; } = false;

    public string DragDropDelimiter { get; set; } = " ";

    public bool EnableBuiltinGlyphs { get; set; } = true;

    public bool EnableColorGlyphs { get; set; } = true;

    public bool EnableUnfocusedAcrylic { get; set; } = false;

    public bool FocusFollowMouse { get; set; } = false;

    public IDictionary<string, float> FontAxes { get; set; } = new Dictionary<string, float>();

    public string FontFace { get; set; } = "Cascadia Mono";

    public IDictionary<string, float> FontFeatures { get; set; } = new Dictionary<string, float>();

    public float FontSize { get; set; } = 12.0f;

    public FontWeight FontWeight { get; set; } = new FontWeight { Weight = 400 };

    public GraphicsAPI GraphicsAPI { get; set; } = GraphicsAPI.Automatic;

    public string Padding { get; set; } = "8, 8, 8, 8";

    public PathTranslationStyle PathTranslationStyle { get; set; } = PathTranslationStyle.None;

    public bool RepositionCursorWithMouse { get; set; } = false;

    public bool RightClickContextMenu { get; set; } = false;

    public ScrollbarState ScrollState { get; set; } = ScrollbarState.Visible;

    public bool ScrollToChangeOpacity { get; set; } = true;

    public bool ScrollToZoom { get; set; } = true;

    public Guid SessionId { get; set; } = Guid.NewGuid();

    public bool ShowMarks { get; set; } = false;

    public bool SoftwareRendering { get; set; } = false;

    public string StartingDirectory { get; set; } = string.Empty;

    public TextMeasurement TextMeasurement { get; set; } = TextMeasurement.Graphemes;

    public bool UseBackgroundImageForWindow { get; set; } = false;
}
