object FRDeads: TFRDeads
  Left = 0
  Top = 0
  Width = 271
  Height = 23
  TabOrder = 0
  object Label13: TLabel
    Left = 140
    Top = 3
    Width = 88
    Height = 14
    Caption = #1052#1105#1088#1090#1074#1072#1103' '#1079#1086#1085#1072' 2'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMenuHighlight
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 3
    Top = 3
    Width = 88
    Height = 14
    Caption = #1052#1105#1088#1090#1074#1072#1103' '#1079#1086#1085#1072' 1'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clMenuHighlight
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object EFinish: TEdit
    Left = 230
    Top = 0
    Width = 40
    Height = 22
    Hint = #1053#1077#1082#1086#1085#1090#1088#1086#1083#1080#1088#1091#1077#1084#1072#1103' '#1079#1086#1085#1072' '#1074' '#1082#1086#1085#1094#1077' '#1090#1088#1091#1073#1099', '#1074' '#1084#1084
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = []
    NumbersOnly = True
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 0
    OnExit = EStartExit
    OnKeyDown = EStartKeyDown
  end
  object EStart: TEdit
    Left = 92
    Top = 0
    Width = 40
    Height = 22
    Hint = #1053#1077#1082#1086#1085#1090#1088#1086#1083#1080#1088#1091#1077#1084#1072#1103' '#1079#1086#1085#1072' '#1074' '#1085#1072#1095#1072#1083#1077' '#1090#1088#1091#1073#1099', '#1074' '#1084#1084
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = []
    NumbersOnly = True
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 1
    OnExit = EStartExit
    OnKeyDown = EStartKeyDown
  end
end
