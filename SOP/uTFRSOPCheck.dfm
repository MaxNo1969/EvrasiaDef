object FRSOPCheck: TFRSOPCheck
  Left = 0
  Top = 0
  Width = 221
  Height = 338
  TabOrder = 0
  OnResize = FrameResize
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 221
    Height = 338
    Align = alClient
    Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090' '#1089#1074#1077#1088#1082#1080
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    object bSave: TButton
      Left = 3
      Top = 235
      Width = 171
      Height = 24
      Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = bSaveClick
    end
    object mCheckedDefects: TMemo
      Left = 3
      Top = 76
      Width = 171
      Height = 157
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      Lines.Strings = (
        'mCheckedDefects')
      ParentFont = False
      ScrollBars = ssVertical
      TabOrder = 1
    end
    object pResultBit: TPanel
      Left = 3
      Top = 46
      Width = 171
      Height = 24
      BorderStyle = bsSingle
      Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentBackground = False
      ParentFont = False
      TabOrder = 2
    end
    object pResultNum: TPanel
      Left = 3
      Top = 16
      Width = 171
      Height = 24
      BorderStyle = bsSingle
      Caption = #1063#1080#1089#1083#1086' '#1089#1086#1074#1087#1072#1074#1096#1080#1093
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentBackground = False
      ParentFont = False
      TabOrder = 3
    end
  end
end
