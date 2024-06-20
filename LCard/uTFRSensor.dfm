object FRSensor: TFRSensor
  Left = 0
  Top = 0
  Width = 321
  Height = 24
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  object LName: TLabel
    Left = 3
    Top = 3
    Width = 49
    Height = 19
    Caption = #1044#1072#1090#1095#1080#1082
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object CBRange: TComboBox
    Left = 127
    Top = 0
    Width = 46
    Height = 23
    Style = csDropDownList
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    PopupMenu = PopupMenu1
    TabOrder = 0
    Items.Strings = (
      #177'10'
      #177'5'
      #177'2'
      #177'1'
      #177'0.5'
      #177'0.2')
  end
  object SEChannel: TCSpinEdit
    Left = 81
    Top = 0
    Width = 40
    Height = 24
    AutoSize = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = []
    MaxValue = 31
    ParentFont = False
    TabOrder = 1
  end
  object CBMode: TComboBox
    Left = 179
    Top = 0
    Width = 141
    Height = 23
    Style = csDropDownList
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Times New Roman'
    Font.Style = []
    ItemIndex = 0
    ParentFont = False
    PopupMenu = PopupMenu2
    TabOrder = 2
    Text = #1057' '#1086#1073#1097#1077#1081' '#1079#1077#1084#1083#1077#1081
    Items.Strings = (
      #1057' '#1086#1073#1097#1077#1081' '#1079#1077#1084#1083#1077#1081
      #1044#1080#1092#1092#1077#1088#1077#1085#1094#1080#1072#1083#1100#1085#1099#1081
      #1048#1079#1084#1077#1088#1077#1085#1080#1077' '#1085#1091#1083#1103)
  end
  object PopupMenu1: TPopupMenu
    Left = 40
    Top = 2
    object N1: TMenuItem
      Caption = #1044#1083#1103' '#1074#1089#1077#1093
      OnClick = N1Click
    end
  end
  object PopupMenu2: TPopupMenu
    Left = 40
    Top = 2
    object N2: TMenuItem
      Caption = #1044#1083#1103' '#1074#1089#1077#1093
      OnClick = N2Click
    end
  end
end
