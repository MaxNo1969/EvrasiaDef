object FRSOP: TFRSOP
  Left = 0
  Top = 0
  Width = 461
  Height = 22
  TabOrder = 0
  object lEtalon: TLabel
    Left = 3
    Top = 3
    Width = 22
    Height = 13
    Caption = #1057#1054#1055
  end
  object cbEtalonView: TCheckBox
    Left = 311
    Top = 3
    Width = 145
    Height = 17
    Caption = #1055#1086#1082#1072#1079#1099#1074#1072#1090#1100' '#1085#1072' '#1075#1088#1072#1092#1080#1082#1077
    TabOrder = 0
    OnClick = cbEtalonViewClick
  end
  object cbSelectEtalon: TComboBox
    Left = 31
    Top = 0
    Width = 274
    Height = 21
    Color = clBtnFace
    TabOrder = 1
    OnChange = cbSelectEtalonChange
  end
end
