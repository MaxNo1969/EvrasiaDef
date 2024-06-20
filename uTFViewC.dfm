object FViewC: TFViewC
  Left = 0
  Top = 0
  Caption = #1055#1088#1086#1089#1084#1086#1090#1088' '#1088#1077#1079#1091#1083#1100#1090#1072#1090#1072
  ClientHeight = 631
  ClientWidth = 1110
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDefault
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 209
    Width = 21
    Height = 13
    Caption = #1064#1072#1075
  end
  object CBStep: TComboBox
    Left = 35
    Top = 206
    Width = 54
    Height = 22
    Style = csOwnerDrawFixed
    TabOrder = 0
    OnChange = CBStepChange
    Items.Strings = (
      '1'
      '0,1'
      '0,01'
      '0,001')
  end
  inline FRViewDevC: TFRViewDev
    Left = 0
    Top = 234
    Width = 457
    Height = 363
    TabOrder = 1
    Visible = False
    ExplicitTop = 234
    ExplicitWidth = 457
  end
  inline FRViewLDevC: TFRViewLDev
    Left = 0
    Top = 0
    Width = 1097
    Height = 200
    TabOrder = 2
    ExplicitWidth = 1097
    ExplicitHeight = 200
    inherited Chart1: TChart
      Width = 1097
      Height = 200
      ExplicitWidth = 1097
      ExplicitHeight = 200
      PrintMargins = (
        15
        47
        15
        47)
    end
  end
end
