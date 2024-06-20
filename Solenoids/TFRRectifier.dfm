object FRRectifier: TFRRectifier
  Left = 0
  Top = 0
  Width = 163
  Height = 197
  TabOrder = 0
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 163
    Height = 197
    Align = alClient
    BevelInner = bvRaised
    BevelKind = bkTile
    BevelOuter = bvNone
    TabOrder = 0
    ExplicitHeight = 174
    object Label1: TLabel
      Left = 1
      Top = 1
      Width = 107
      Height = 18
      Align = alTop
      Alignment = taCenter
      Caption = #1042#1099#1087#1088#1103#1084#1080#1090#1077#1083#1100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -15
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object SpeedButton1: TSpeedButton
      Left = 4
      Top = 25
      Width = 151
      Height = 28
      AllowAllUp = True
      GroupIndex = 1
      Caption = #1042#1082#1083#1102#1095#1080#1090#1100
      OnClick = SpeedButton1Click
    end
    object lLinearVoltage: TLabel
      Left = 4
      Top = 98
      Width = 76
      Height = 13
      Caption = #1053#1072#1087#1088#1103#1078#1077#1085#1080#1077', '#1042
      Color = clBtnFace
      ParentColor = False
    end
    object lLinearAmperage: TLabel
      Left = 4
      Top = 75
      Width = 66
      Height = 13
      Caption = #1057#1080#1083#1072' '#1090#1086#1082#1072', '#1040
      Color = clBtnFace
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentColor = False
      ParentFont = False
    end
    object Label2: TLabel
      Left = 4
      Top = 121
      Width = 100
      Height = 13
      Caption = #1057#1086#1087#1088#1086#1090#1080#1074#1083#1077#1085#1080#1077', '#1054#1084
      Color = clBtnFace
      ParentColor = False
    end
    object Label3: TLabel
      Left = 4
      Top = 144
      Width = 68
      Height = 13
      Caption = #1054#1089#1090#1072#1074'. '#1074#1088#1077#1084#1103
      Color = clBtnFace
      ParentColor = False
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
      TabOrder = 0
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
    object StatusBarBottom: TStatusBar
      AlignWithMargins = True
      Left = 4
      Top = 168
      Width = 151
      Height = 21
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      Panels = <
        item
          Width = 600
        end>
      ParentColor = True
      SimplePanel = True
      UseSystemFont = False
      ExplicitTop = 164
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
      TabOrder = 3
    end
    object ST_Time: TStaticText
      Left = 96
      Top = 140
      Width = 57
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
