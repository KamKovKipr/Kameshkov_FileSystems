object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 451
  ClientWidth = 649
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object VirtualStringTree1: TVirtualStringTree
    Left = 247
    Top = 24
    Width = 378
    Height = 353
    DefaultNodeHeight = 19
    Header.AutoSizeIndex = 0
    Header.Options = [hoColumnResize, hoDrag, hoShowSortGlyphs, hoVisible]
    TabOrder = 0
    OnGetText = VirtualStringTree1GetText
    Touch.InteractiveGestures = [igPan, igPressAndTap]
    Touch.InteractiveGestureOptions = [igoPanSingleFingerHorizontal, igoPanSingleFingerVertical, igoPanInertia, igoPanGutter, igoParentPassthrough]
    Columns = <
      item
        Position = 0
        Text = #8470
      end
      item
        Position = 1
        Text = #1055#1091#1090#1100
        Width = 152
      end
      item
        Position = 2
        Text = #1056#1072#1089#1096#1080#1088#1077#1085#1080#1077
        Width = 83
      end
      item
        Position = 3
        Text = #8470' '#1050#1083#1072#1089#1090#1077#1088#1072
        Width = 84
      end>
  end
  object Button1: TButton
    Left = 88
    Top = 344
    Width = 75
    Height = 25
    Caption = #1055#1086#1080#1089#1082
    TabOrder = 1
    OnClick = Button1Click
  end
  object ComboBox1: TComboBox
    Left = 24
    Top = 24
    Width = 209
    Height = 23
    TabOrder = 2
    Text = #1042#1099#1073#1077#1088#1080#1090#1077' '#1073#1091#1082#1074#1091' '#1090#1086#1084#1072
    OnChange = ComboBox1Change
  end
  object ComboBox2: TComboBox
    Left = 24
    Top = 96
    Width = 209
    Height = 23
    Color = clWhite
    TabOrder = 3
    Text = #1042#1099#1073#1077#1088#1080#1090#1077' '#1080#1089#1082#1086#1084#1086#1077' '#1088#1072#1089#1096#1080#1088#1077#1085#1080#1077'...'
    Items.Strings = (
      'exe'
      'msoffice'
      'pdf'
      'rar'
      'vmdk')
  end
  object Edit1: TEdit
    Left = 24
    Top = 24
    Width = 209
    Height = 23
    TabOrder = 4
    Text = #1042#1099#1073#1077#1088#1080#1090#1077' '#1092#1072#1081#1083' '#1076#1083#1103' '#1072#1085#1072#1083#1080#1079#1072'...'
    OnClick = Edit1Click
  end
end
