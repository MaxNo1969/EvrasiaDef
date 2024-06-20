object FRTestInverter: TFRTestInverter
  Left = 0
  Top = 0
  Width = 203
  Height = 253
  TabOrder = 0
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 203
    Height = 253
    Align = alClient
    BevelInner = bvRaised
    BevelKind = bkTile
    BevelOuter = bvNone
    TabOrder = 0
    object SpeedButton1: TSpeedButton
      Left = 9
      Top = 38
      Width = 51
      Height = 32
      AllowAllUp = True
      GroupIndex = 1
      Caption = #1055#1091#1089#1082
      OnClick = SpeedButton1Click
    end
    object SpeedButton2: TSpeedButton
      Left = 9
      Top = 76
      Width = 118
      Height = 22
      Caption = #1042#1099#1089#1090#1072#1074#1080#1090#1100' '#1095#1072#1089#1090#1086#1090#1091
      OnClick = SpeedButton2Click
    end
    object SpeedButton3: TSpeedButton
      Left = 9
      Top = 104
      Width = 118
      Height = 22
      Caption = #1055#1086#1083#1091#1095#1080#1090#1100' '#1095#1072#1089#1090#1086#1090#1091
      OnClick = SpeedButton3Click
    end
    object SpeedButton4: TSpeedButton
      Left = 9
      Top = 146
      Width = 118
      Height = 22
      Caption = #1047#1072#1087#1088#1086#1089#1080#1090#1100' '#1089#1086#1089#1090#1086#1103#1085#1080#1077
      OnClick = SpeedButton4Click
    end
    object SpeedButton5: TSpeedButton
      Left = 9
      Top = 202
      Width = 118
      Height = 22
      Caption = #1057#1073#1088#1086#1089#1080#1090#1100' '#1086#1096#1080#1073#1082#1080
      OnClick = SpeedButton5Click
    end
    object SpeedButton6: TSpeedButton
      Left = 9
      Top = 174
      Width = 118
      Height = 22
      Caption = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100' '#1089#1077#1090#1100
      OnClick = SpeedButton6Click
    end
    object Label1: TLabel
      Left = 84
      Top = 48
      Width = 43
      Height = 13
      Caption = #1040#1073#1086#1085#1077#1085#1090
    end
    object Title: TLabel
      Left = 9
      Top = 8
      Width = 69
      Height = 16
      Caption = #1063#1072#1089#1090#1086#1090#1085#1080#1082
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object StatusBar1: TStatusBar
      Left = 1
      Top = 229
      Width = 197
      Height = 19
      Panels = <>
      SimplePanel = True
    end
    object Edit1: TEdit
      Left = 133
      Top = 76
      Width = 51
      Height = 21
      TabOrder = 1
      Text = '0'
    end
  end
end
