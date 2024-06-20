object FRCross: TFRCross
  Left = 0
  Top = 0
  Width = 833
  Height = 252
  TabOrder = 0
  object Chart1: TChart
    Left = 0
    Top = 46
    Width = 833
    Height = 206
    Legend.Visible = False
    MarginBottom = 0
    MarginLeft = 10
    MarginRight = 5
    MarginTop = 0
    MarginUnits = muPixels
    Title.Text.Strings = (
      'TChart')
    Title.Visible = False
    BottomAxis.Automatic = False
    BottomAxis.AutomaticMaximum = False
    BottomAxis.AutomaticMinimum = False
    BottomAxis.Maximum = 5.000000000000000000
    BottomAxis.MinorTicks.Visible = False
    LeftAxis.Automatic = False
    LeftAxis.AutomaticMaximum = False
    LeftAxis.AutomaticMinimum = False
    LeftAxis.ExactDateTime = False
    LeftAxis.Increment = 1.000000000000000000
    LeftAxis.LabelsOnAxis = False
    LeftAxis.Maximum = 12.000000000000000000
    LeftAxis.MinorTicks.Visible = False
    View3D = False
    Zoom.Allow = False
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 0
    DefaultCanvas = 'TGDIPlusCanvas'
    ColorPaletteIndex = 13
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 833
    Height = 46
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 1
    object Label2: TLabel
      Left = 10
      Top = -1
      Width = 205
      Height = 19
      Caption = #1055#1086#1087#1077#1088#1077#1095#1085#1072#1103' '#1076#1077#1092#1077#1082#1090#1086#1089#1082#1086#1087#1080#1103
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMenuHighlight
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object cbCross: TCheckBox
      Left = 222
      Top = 4
      Width = 72
      Height = 15
      Caption = #1042' '#1088#1072#1073#1086#1090#1077
      Checked = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      State = cbChecked
      TabOrder = 0
      OnClick = cbCrossClick
    end
    inline FRBordersCross: TFRBorders
      Left = 10
      Top = 21
      Width = 311
      Height = 22
      TabOrder = 1
      ExplicitLeft = 10
      ExplicitTop = 21
    end
    inline FRDeads1: TFRDeads
      Left = 470
      Top = 20
      Width = 296
      Height = 23
      TabOrder = 2
      ExplicitLeft = 470
      ExplicitTop = 20
      ExplicitWidth = 296
      inherited Label13: TLabel
        Top = 6
        Visible = False
        ExplicitTop = 6
      end
      inherited Label5: TLabel
        Left = 0
        Top = 5
        Visible = False
        ExplicitLeft = 0
        ExplicitTop = 5
      end
      inherited EFinish: TEdit
        Visible = False
      end
      inherited EStart: TEdit
        Visible = False
      end
    end
    inline FRDefects1: TFRDefects
      Left = 326
      Top = 21
      Width = 137
      Height = 20
      TabOrder = 3
      ExplicitLeft = 326
      ExplicitTop = 21
      inherited Label1: TLabel
        Visible = False
      end
      inherited Panel1: TPanel
        Visible = False
      end
    end
  end
end
