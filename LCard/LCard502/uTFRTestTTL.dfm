object FRTestTTL: TFRTestTTL
  Left = 0
  Top = 0
  Width = 320
  Height = 240
  TabOrder = 0
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 320
    Height = 240
    Align = alClient
    BevelInner = bvRaised
    BevelKind = bkTile
    BevelOuter = bvNone
    TabOrder = 0
    object Label1: TLabel
      Left = 1
      Top = 1
      Width = 66
      Height = 18
      Align = alTop
      Alignment = taCenter
      Caption = #1058#1077#1089#1090' TTL'
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
    object StatusBarBottom: TStatusBar
      AlignWithMargins = True
      Left = 4
      Top = 211
      Width = 308
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
      ExplicitTop = 213
    end
  end
end
