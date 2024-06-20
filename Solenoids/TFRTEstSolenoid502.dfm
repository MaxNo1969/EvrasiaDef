object FRTEstSolenoid502: TFRTEstSolenoid502
  Left = 0
  Top = 0
  Width = 163
  Height = 186
  TabOrder = 0
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 163
    Height = 186
    Align = alClient
    BevelInner = bvRaised
    BevelKind = bkTile
    BevelOuter = bvNone
    TabOrder = 0
    object Label1: TLabel
      Left = 1
      Top = 1
      Width = 76
      Height = 18
      Align = alTop
      Alignment = taCenter
      Caption = #1057#1086#1083#1077#1085#1086#1080#1076
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lLinearTemperature: TLabel
      Left = 4
      Top = 121
      Width = 80
      Height = 13
      Caption = #1058#1077#1084#1087#1077#1088#1072#1090#1091#1088#1072', '#1057
    end
    object lLinearResistance: TLabel
      Left = 4
      Top = 121
      Width = 100
      Height = 13
      Caption = #1057#1086#1087#1088#1086#1090#1080#1074#1083#1077#1085#1080#1077', '#1054#1084
    end
    object lLinearVoltage: TLabel
      Left = 4
      Top = 98
      Width = 76
      Height = 13
      Caption = #1053#1072#1087#1088#1103#1078#1077#1085#1080#1077', '#1042
    end
    object lLinearAmperage: TLabel
      Left = 4
      Top = 75
      Width = 66
      Height = 13
      Caption = #1057#1080#1083#1072' '#1090#1086#1082#1072', '#1040
      Color = clCream
      ParentColor = False
    end
    object SpeedButton1: TSpeedButton
      Left = 4
      Top = 25
      Width = 145
      Height = 28
      AllowAllUp = True
      GroupIndex = 1
      Caption = #1042#1082#1083#1102#1095#1080#1090#1100
      OnClick = SpeedButton1Click
    end
    object StatusBarBottom: TStatusBar
      AlignWithMargins = True
      Left = 4
      Top = 147
      Width = 151
      Height = 31
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      Panels = <
        item
          Width = 600
        end>
      ParentColor = True
      SimplePanel = True
      UseSystemFont = False
    end
    object ST_I: TStaticText
      Left = 110
      Top = 71
      Width = 43
      Height = 17
      Alignment = taRightJustify
      AutoSize = False
      BorderStyle = sbsSunken
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
    end
    object ST_U: TStaticText
      Left = 110
      Top = 94
      Width = 43
      Height = 17
      Alignment = taRightJustify
      AutoSize = False
      BorderStyle = sbsSunken
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
    end
    object ST_T: TStaticText
      Left = 110
      Top = 117
      Width = 43
      Height = 17
      Alignment = taRightJustify
      AutoSize = False
      BorderStyle = sbsSunken
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
    end
    object ST_R: TStaticText
      Left = 110
      Top = 117
      Width = 43
      Height = 17
      Alignment = taRightJustify
      AutoSize = False
      BorderStyle = sbsSunken
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
    end
  end
end
