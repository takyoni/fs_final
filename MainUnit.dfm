object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 527
  ClientWidth = 597
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object SearchTimeResultLabel: TLabel
    Left = 461
    Top = 293
    Width = 6
    Height = 15
    Caption = '0'
  end
  object CountResultLabel: TLabel
    Left = 542
    Top = 314
    Width = 6
    Height = 15
    Caption = '0'
  end
  object FileFormatLabel: TLabel
    Left = 355
    Top = 91
    Width = 145
    Height = 15
    Caption = #1060#1086#1088#1084#1072#1090' '#1092#1072#1081#1083#1072' '#1076#1083#1103' '#1087#1086#1080#1089#1082#1072
  end
  object SearchTimeLabel: TLabel
    Left = 355
    Top = 293
    Width = 93
    Height = 15
    Caption = #1042#1088#1077#1084#1103' '#1085#1072' '#1087#1086#1080#1089#1082': '
  end
  object CountLabel: TLabel
    Left = 355
    Top = 314
    Width = 165
    Height = 15
    Caption = #1050#1086#1083'-'#1074#1086' '#1085#1072#1081#1076#1077#1085#1085#1099#1093' '#1082#1083#1072#1089#1090#1077#1088#1086#1074':'
  end
  object DetectLabel: TLabel
    Left = 355
    Top = 272
    Width = 109
    Height = 15
    Caption = #1054#1073#1085#1072#1088#1091#1078#1077#1085#1085#1072#1103' '#1060'C: '
  end
  object DetectResultLabel: TLabel
    Left = 473
    Top = 272
    Width = 53
    Height = 15
    Caption = 'Underfind'
  end
  object DiskNameLabel: TLabel
    Left = 355
    Top = 25
    Width = 102
    Height = 15
    Caption = #1042#1074#1077#1076#1080#1090#1077' '#1080#1084#1103' '#1076#1080#1089#1082#1072
  end
  object Panel1: TPanel
    Left = 355
    Top = 112
    Width = 225
    Height = 129
    TabOrder = 7
  end
  object Button3: TButton
    Left = 16
    Top = 440
    Width = 321
    Height = 25
    Caption = #1053#1072#1081#1090#1080' '#1082#1083#1072#1089#1090#1077#1088#1099
    TabOrder = 0
    OnClick = Button3Click
  end
  object MainStringTree: TVirtualStringTree
    Left = 16
    Top = 8
    Width = 321
    Height = 417
    ClipboardFormats.Strings = (
      'Plain text'
      'Unicode text')
    DefaultNodeHeight = 19
    Header.AutoSizeIndex = 0
    Header.Options = [hoColumnResize, hoDrag, hoShowSortGlyphs, hoVisible]
    ScrollBarOptions.AlwaysVisible = True
    TabOrder = 1
    OnGetText = MainStringTreeGetText
    Touch.InteractiveGestures = [igPan, igPressAndTap]
    Touch.InteractiveGestureOptions = [igoPanSingleFingerHorizontal, igoPanSingleFingerVertical, igoPanInertia, igoPanGutter, igoParentPassthrough]
    Columns = <
      item
        Options = [coAllowClick, coDraggable, coEnabled, coParentBidiMode, coParentColor, coResizable, coShowDropMark, coVisible, coSmartResize, coAllowFocus, coEditable, coStyleColor]
        Position = 0
        Text = 'ClusterNum'
        Width = 84
      end
      item
        Options = [coAllowClick, coDraggable, coEnabled, coParentBidiMode, coParentColor, coResizable, coShowDropMark, coVisible, coSmartResize, coAllowFocus, coEditable, coStyleColor]
        Position = 1
        Text = 'First 10 bytes'
        Width = 95
      end>
  end
  object JpegButton: TRadioButton
    Left = 371
    Top = 131
    Width = 113
    Height = 17
    Caption = 'jpeg'
    Checked = True
    TabOrder = 2
    TabStop = True
  end
  object PdfButton: TRadioButton
    Left = 371
    Top = 154
    Width = 113
    Height = 17
    Caption = 'pdf'
    TabOrder = 3
  end
  object ExeButton: TRadioButton
    Left = 371
    Top = 177
    Width = 113
    Height = 17
    Caption = 'exe'
    TabOrder = 4
  end
  object ElfButton: TRadioButton
    Left = 371
    Top = 200
    Width = 113
    Height = 17
    Caption = 'elf'
    TabOrder = 5
  end
  object StopButton: TButton
    Left = 16
    Top = 480
    Width = 321
    Height = 25
    Caption = #1054#1089#1090#1072#1085#1086#1074#1080#1090#1100' '#1087#1086#1080#1089#1082
    TabOrder = 6
    OnClick = StopButtonClick
  end
  object Edit1: TEdit
    Left = 355
    Top = 46
    Width = 205
    Height = 23
    TabOrder = 8
    Text = '\\.\C:'
  end
end
