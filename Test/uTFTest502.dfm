object FTest502: TFTest502
  Left = 0
  Top = 0
  Caption = #1053#1072#1083#1072#1076#1082#1072
  ClientHeight = 476
  ClientWidth = 594
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  inline FRTestInverters1: TFRTestInverters
    Left = 5
    Top = 203
    Width = 308
    Height = 256
    TabOrder = 0
    ExplicitLeft = 5
    ExplicitTop = 203
    ExplicitWidth = 308
    inherited ThickInverter: TFRTestInverter
      inherited Panel1: TPanel
        ExplicitWidth = 307
        inherited StatusBar1: TStatusBar
          ExplicitWidth = 301
        end
      end
    end
  end
  inline FRRectCross: TFRRectifier
    Left = 4
    Top = 4
    Width = 163
    Height = 197
    TabOrder = 1
    ExplicitLeft = 4
    ExplicitTop = 4
    inherited Panel1: TPanel
      ExplicitHeight = 197
      inherited Label1: TLabel
        Width = 157
        Caption = #1042#1099#1087#1088'. '#1055#1086#1087#1077#1088#1077#1095#1085#1099#1081
        ExplicitWidth = 146
      end
      inherited StatusBarBottom: TStatusBar
        ExplicitTop = 168
      end
    end
  end
  inline FRRectThick: TFRRectifier
    Left = 169
    Top = 4
    Width = 163
    Height = 197
    TabOrder = 2
    ExplicitLeft = 169
    ExplicitTop = 4
    inherited Panel1: TPanel
      ExplicitHeight = 197
      inherited Label1: TLabel
        Width = 157
        Caption = #1042#1099#1087#1088'. '#1058#1086#1083#1097#1080#1085#1086#1084#1077#1088
        ExplicitWidth = 148
      end
      inherited StatusBarBottom: TStatusBar
        ExplicitTop = 168
      end
    end
  end
  inline FRTestTTL1: TFRTestTTL
    Left = 318
    Top = 203
    Width = 320
    Height = 253
    TabOrder = 3
    ExplicitLeft = 318
    ExplicitTop = 203
    ExplicitHeight = 253
    inherited Panel1: TPanel
      Height = 253
      ExplicitHeight = 253
      inherited Label1: TLabel
        Width = 314
      end
      inherited StatusBarBottom: TStatusBar
        Top = 224
        ExplicitTop = 224
      end
    end
  end
  object Timer1: TTimer
    Interval = 500
    OnTimer = Timer1Timer
    Left = 342
    Top = 8
  end
end
