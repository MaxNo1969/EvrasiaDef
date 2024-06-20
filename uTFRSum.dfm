object FRSum: TFRSum
  Left = 0
  Top = 0
  Width = 1054
  Height = 240
  TabOrder = 0
  OnResize = FrameResize
  object gbSummary: TGroupBox
    Left = 0
    Top = 0
    Width = 1054
    Height = 240
    Align = alClient
    Caption = #1048#1090#1086#1075
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object Chart1: TChart
      Left = 2
      Top = 45
      Width = 1050
      Height = 193
      BackWall.Color = clBtnFace
      BackWall.Transparent = False
      BottomWall.Visible = False
      LeftWall.Visible = False
      Legend.Visible = False
      MarginBottom = 0
      MarginLeft = 5
      MarginRight = 5
      MarginTop = 0
      MarginUnits = muPixels
      Title.Text.Strings = (
        '')
      BottomAxis.Automatic = False
      BottomAxis.AutomaticMaximum = False
      BottomAxis.AutomaticMinimum = False
      BottomAxis.Maximum = 5.000000000000000000
      BottomAxis.MinorTicks.Visible = False
      DepthAxis.Automatic = False
      DepthAxis.AutomaticMaximum = False
      DepthAxis.AutomaticMinimum = False
      DepthAxis.Maximum = 4.219999999999990000
      DepthAxis.Minimum = 3.219999999999988000
      DepthAxis.Visible = True
      DepthTopAxis.Automatic = False
      DepthTopAxis.AutomaticMaximum = False
      DepthTopAxis.AutomaticMinimum = False
      DepthTopAxis.Maximum = 4.219999999999990000
      DepthTopAxis.Minimum = 3.219999999999988000
      LeftAxis.Automatic = False
      LeftAxis.AutomaticMaximum = False
      LeftAxis.AutomaticMinimum = False
      LeftAxis.Grid.Visible = False
      LeftAxis.LabelsSeparation = 100
      LeftAxis.Maximum = 1.000000000000000000
      LeftAxis.MinorTicks.Visible = False
      LeftAxis.TickLength = 5
      LeftAxis.TicksInner.Visible = False
      RightAxis.Automatic = False
      RightAxis.AutomaticMaximum = False
      RightAxis.AutomaticMinimum = False
      TopAxis.Automatic = False
      TopAxis.AutomaticMaximum = False
      TopAxis.AutomaticMinimum = False
      View3D = False
      Zoom.Allow = False
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 0
      DefaultCanvas = 'TGDIPlusCanvas'
      ColorPaletteIndex = 13
      object Series4: TBarSeries
        ColorEachPoint = True
        Marks.Visible = False
        BarWidthPercent = 100
        OffsetPercent = 50
        XValues.Name = 'X'
        XValues.Order = loAscending
        YValues.Name = 'Bar'
        YValues.Order = loNone
      end
    end
    object Panel1: TPanel
      Left = 2
      Top = 21
      Width = 1050
      Height = 24
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 1
      object Label7: TLabel
        Left = 154
        Top = 2
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
        Left = 898
        Top = 4
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
        Left = 779
        Top = -1
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
        Left = 212
        Top = 2
        Width = 30
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
        Left = 837
        Top = -1
        Width = 30
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
        Left = 4
        Top = -2
        Width = 20
        Height = 25
        Alignment = taRightJustify
        AutoSize = False
        Caption = #8470
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        Layout = tlCenter
      end
      object eMin_Good_Length: TEdit
        Left = 968
        Top = -1
        Width = 40
        Height = 22
        Hint = 
          #1052#1080#1085#1080#1084#1072#1083#1100#1085#1099#1081' '#1075#1086#1076#1085#1099#1081' '#1091#1095#1072#1089#1090#1086#1082' '#1076#1083#1103' '#1086#1090#1088#1077#1079#1082#1080' '#1090#1088#1091#1073#1099' '#1074' '#1079#1086#1085#1072#1093'. '#1055#1086#1089#1090#1072#1074#1100#1090#1077' ' +
          '"0" '#1076#1083#1103' '#1085#1077#1088#1077#1084#1086#1085#1090#1080#1088#1091#1077#1084#1086#1081' '#1090#1088#1091#1073#1099
        NumbersOnly = True
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        OnExit = eMin_Good_LengthExit
        OnKeyDown = eMin_Good_LengthKeyDown
      end
      object lResult: TPanel
        Left = 456
        Top = -1
        Width = 317
        Height = 25
        BorderStyle = bsSingle
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clWindowText
        Font.Height = -21
        Font.Name = 'Times New Roman'
        Font.Style = []
        ParentBackground = False
        ParentFont = False
        TabOrder = 1
      end
      object pNN: TPanel
        Left = 30
        Top = 0
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
      end
    end
  end
end
