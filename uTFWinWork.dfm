object FWinWork: TFWinWork
  Left = 0
  Top = 0
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = #1042#1085#1080#1084#1072#1085#1080#1077'!'
  ClientHeight = 158
  ClientWidth = 484
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object lWinWorkMessage: TLabel
    Left = 17
    Top = 15
    Width = 439
    Height = 46
    Alignment = taCenter
    Caption = 
      #1056#1077#1082#1086#1084#1077#1085#1076#1091#1077#1084' '#1074#1072#1084' '#1087#1077#1088#1077#1079#1072#1075#1088#1091#1079#1080#1090#1100' '#1082#1086#1084#1087#1100#1102#1090#1077#1088' - '#1086#1085' '#1088#1072#1073#1086#1090#1072#1077#1090' '#1089#1083#1080#1096#1082#1086#1084' '#1076#1086 +
      #1083#1075#1086
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -19
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    WordWrap = True
  end
  object bWinWorkOk: TButton
    Left = 188
    Top = 87
    Width = 117
    Height = 49
    Caption = 'OK'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    OnClick = bWinWorkOkClick
  end
end
