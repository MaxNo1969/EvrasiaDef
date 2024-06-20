object FRSG: TFRSG
  Left = 0
  Top = 0
  Width = 250
  Height = 39
  Color = clBtnFace
  ParentBackground = False
  ParentColor = False
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 250
    Height = 39
    Align = alClient
    Caption = #1043#1088#1091#1087#1087#1072' '#1087#1088#1086#1095#1085#1086#1089#1090#1080' '
    TabOrder = 0
    object pSolidGroup: TPanel
      Left = 79
      Top = 15
      Width = 59
      Height = 21
      ParentCustomHint = False
      BiDiMode = bdLeftToRight
      Caption = #1043#1055
      Ctl3D = True
      DoubleBuffered = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentBiDiMode = False
      ParentBackground = False
      ParentCtl3D = False
      ParentDoubleBuffered = False
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 0
      Visible = False
    end
    object CheckBox1: TCheckBox
      Left = 144
      Top = 17
      Width = 97
      Height = 17
      Caption = #1060#1080#1082#1089#1080#1088#1086#1074#1072#1085#1085#1072#1103
      TabOrder = 1
      OnClick = CheckBox1Click
    end
    object Edit1: TEdit
      Left = 77
      Top = 15
      Width = 61
      Height = 21
      TabOrder = 2
      Text = 'Edit1'
      OnChange = Edit1Change
    end
    object CheckBox2: TCheckBox
      Left = 5
      Top = 17
      Width = 66
      Height = 17
      Caption = #1042' '#1088#1072#1073#1086#1090#1077
      TabOrder = 3
      OnClick = CheckBox2Click
    end
  end
end
