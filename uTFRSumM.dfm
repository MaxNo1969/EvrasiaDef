object FRSumM: TFRSumM
  Left = 0
  Top = 0
  Width = 1124
  Height = 240
  TabOrder = 0
  OnResize = FrameResize
  object Chart1: TChart
    Left = 0
    Top = 49
    Width = 1124
    Height = 191
    Legend.Visible = False
    MarginBottom = 0
    MarginLeft = 26
    MarginRight = 5
    MarginTop = 5
    MarginUnits = muPixels
    Title.Text.Strings = (
      'TChart')
    Title.Visible = False
    BottomAxis.Automatic = False
    BottomAxis.AutomaticMaximum = False
    BottomAxis.AutomaticMinimum = False
    BottomAxis.ExactDateTime = False
    BottomAxis.Increment = 1.000000000000000000
    BottomAxis.Maximum = 12.000000000000000000
    BottomAxis.MinorGrid.Color = clGray
    BottomAxis.MinorGrid.Style = psDot
    BottomAxis.MinorGrid.Visible = True
    BottomAxis.MinorTickCount = 4
    BottomAxis.TicksInner.Visible = False
    LeftAxis.Automatic = False
    LeftAxis.AutomaticMaximum = False
    LeftAxis.AutomaticMinimum = False
    LeftAxis.ExactDateTime = False
    LeftAxis.Increment = 1.000000000000000000
    LeftAxis.Labels = False
    LeftAxis.LabelsFormat.Visible = False
    LeftAxis.Maximum = 1.000000000000000000
    View3D = False
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 0
    DefaultCanvas = 'TGDIPlusCanvas'
    ColorPaletteIndex = 13
    object Series1: TBarSeries
      BarPen.Color = -1
      ColorEachPoint = True
      Marks.Visible = False
      Marks.Callout.Length = 8
      BarWidthPercent = 100
      OffsetPercent = 50
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Bar'
      YValues.Order = loNone
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1124
    Height = 49
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 1
    object Label7: TLabel
      Left = 171
      Top = 23
      Width = 52
      Height = 23
      Caption = #1056#1077#1079' 1:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Label8: TLabel
      Left = 742
      Top = 29
      Width = 60
      Height = 14
      Caption = #1052#1080#1085' '#1075#1086#1076#1085#1086
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMenuHighlight
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Label9: TLabel
      Left = 607
      Top = 22
      Width = 52
      Height = 23
      Caption = #1056#1077#1079' 2:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object lCut1: TLabel
      Left = 229
      Top = 20
      Width = 49
      Height = 23
      AutoSize = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = [fsUnderline]
      ParentFont = False
    end
    object lCut2: TLabel
      Left = 676
      Top = 20
      Width = 52
      Height = 23
      AutoSize = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = [fsUnderline]
      ParentFont = False
    end
    object lNN: TLabel
      Left = 10
      Top = 29
      Width = 35
      Height = 14
      Alignment = taRightJustify
      Caption = #1044#1083#1080#1085#1072
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      Layout = tlCenter
      Visible = False
    end
    object Label1: TLabel
      Left = 10
      Top = 0
      Width = 35
      Height = 19
      Caption = #1048#1090#1086#1075
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMenuHighlight
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object eMin_Good_Length: TEdit
      Left = 808
      Top = 24
      Width = 40
      Height = 22
      Hint = 
        #1052#1080#1085#1080#1084#1072#1083#1100#1085#1099#1081' '#1075#1086#1076#1085#1099#1081' '#1091#1095#1072#1089#1090#1086#1082' '#1076#1083#1103' '#1086#1090#1088#1077#1079#1082#1080' '#1090#1088#1091#1073#1099' '#1074' '#1079#1086#1085#1072#1093'. '#1055#1086#1089#1090#1072#1074#1100#1090#1077' ' +
        '"0" '#1076#1083#1103' '#1085#1077#1088#1077#1084#1086#1085#1090#1080#1088#1091#1077#1084#1086#1081' '#1090#1088#1091#1073#1099
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = []
      NumbersOnly = True
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      OnExit = eMin_Good_LengthExit
      OnKeyDown = eMin_Good_LengthKeyDown
    end
    object lResult: TPanel
      Left = 284
      Top = 22
      Width = 317
      Height = 25
      BevelWidth = 2
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentBackground = False
      ParentFont = False
      TabOrder = 1
      OnClick = lResultClick
    end
    object pNN: TPanel
      Left = 51
      Top = 23
      Width = 114
      Height = 25
      BorderStyle = bsSingle
      Caption = '9999999999'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentBackground = False
      ParentFont = False
      TabOrder = 2
      Visible = False
    end
  end
end
