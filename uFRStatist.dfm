object FRStatist: TFRStatist
  Left = 0
  Top = 0
  Width = 365
  Height = 39
  TabOrder = 0
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 365
    Height = 39
    Align = alClient
    Caption = #1057#1090#1072#1090#1080#1089#1090#1080#1082#1072
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object Label1: TLabel
      Left = 204
      Top = 17
      Width = 35
      Height = 13
      Caption = #1042#1089#1077#1075#1086': '
    end
    object Label2: TLabel
      Left = 3
      Top = 17
      Width = 43
      Height = 13
      Caption = #1043#1086#1076#1085#1099#1093':'
    end
    object Label3: TLabel
      Left = 108
      Top = 17
      Width = 28
      Height = 13
      Caption = #1041#1088#1072#1082':'
    end
    object STTubes: TStaticText
      Left = 239
      Top = 17
      Width = 55
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
    object STGood: TStaticText
      Left = 47
      Top = 17
      Width = 55
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
    object STBrak: TStaticText
      Left = 139
      Top = 17
      Width = 55
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
    object Button1: TButton
      Left = 300
      Top = 15
      Width = 59
      Height = 19
      Caption = #1054#1073#1085#1091#1083#1080#1090#1100
      TabOrder = 3
      OnClick = Button1Click
    end
  end
end
