object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 404
  ClientWidth = 761
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Label1: TLabel
    Left = 16
    Top = 248
    Width = 34
    Height = 15
    Caption = 'Label1'
  end
  object Label2: TLabel
    Left = 16
    Top = 269
    Width = 34
    Height = 15
    Caption = 'Label2'
  end
  object Button1: TButton
    Left = 16
    Top = 24
    Width = 321
    Height = 25
    Caption = #1041#1077#1079' '#1087#1086#1090#1086#1082#1086#1074
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 16
    Top = 72
    Width = 321
    Height = 25
    Caption = #1055#1086#1090#1086#1082' '#1086#1073#1088#1072#1073#1086#1090#1082#1080
    TabOrder = 1
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 16
    Top = 120
    Width = 321
    Height = 25
    Caption = #1055#1086#1090#1086#1082#1080' '#1095#1090#1077#1085#1080#1103' '#1080' '#1072#1085#1072#1083#1080#1079#1072
    TabOrder = 2
    OnClick = Button3Click
  end
  object ProgressBar1: TProgressBar
    Left = 8
    Top = 208
    Width = 329
    Height = 17
    TabOrder = 3
  end
  object MainStringTree: TVirtualStringTree
    Left = 368
    Top = 24
    Width = 353
    Height = 361
    ClipboardFormats.Strings = (
      'Plain text'
      'Unicode text')
    DefaultNodeHeight = 19
    Header.AutoSizeIndex = 0
    Header.Options = [hoColumnResize, hoDrag, hoShowSortGlyphs, hoVisible]
    ScrollBarOptions.AlwaysVisible = True
    TabOrder = 4
    OnGetText = MainStringTreeGetText
    Touch.InteractiveGestures = [igPan, igPressAndTap]
    Touch.InteractiveGestureOptions = [igoPanSingleFingerHorizontal, igoPanSingleFingerVertical, igoPanInertia, igoPanGutter, igoParentPassthrough]
    Columns = <
      item
        Options = [coAllowClick, coDraggable, coEnabled, coParentBidiMode, coParentColor, coResizable, coShowDropMark, coVisible, coSmartResize, coAllowFocus, coEditable, coStyleColor]
        Position = 0
        Text = 'Id'
      end
      item
        Options = [coAllowClick, coDraggable, coEnabled, coParentBidiMode, coParentColor, coResizable, coShowDropMark, coVisible, coSmartResize, coAllowFocus, coEditable, coStyleColor]
        Position = 1
        Text = 'Name'
      end>
  end
end
