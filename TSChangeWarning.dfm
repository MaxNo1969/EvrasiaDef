object TSChangeWarningForm: TTSChangeWarningForm
  Left = 0
  Top = 0
  Caption = #1057#1084#1077#1085#1072' '#1090#1080#1087#1086#1088#1072#1079#1084#1077#1088#1072
  ClientHeight = 136
  ClientWidth = 430
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 24
    Top = 16
    Width = 374
    Height = 23
    Caption = #1053#1045' '#1047#1040#1041#1059#1044#1068#1058#1045'!!! '#1055#1045#1056#1045#1042#1045#1057#1058#1048' '#1052#1054#1044#1059#1051#1071
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -19
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
  end
  object Label3: TLabel
    Left = 24
    Top = 46
    Width = 374
    Height = 23
    Caption = #1053#1040' '#1042#1067#1041#1056#1040#1053#1053#1067#1049' '#1058#1048#1055#1054#1056#1040#1047#1052#1045#1056' '#1053#1050#1058'!!!'
    Color = clBtnFace
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -19
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
  end
  object bOK: TButton
    Left = 46
    Top = 83
    Width = 121
    Height = 40
    Caption = #1054#1050
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    OnClick = bOKClick
  end
  object bCancel: TButton
    Left = 260
    Top = 83
    Width = 121
    Height = 40
    Caption = #1054#1058#1052#1045#1053#1040
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    OnClick = bCancelClick
  end
end
