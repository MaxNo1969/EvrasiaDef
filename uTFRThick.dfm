object FRThick: TFRThick
  Left = 0
  Top = 0
  Width = 770
  Height = 295
  TabOrder = 0
  OnResize = FrameResize
  object Panel3: TPanel
    Left = 0
    Top = 0
    Width = 770
    Height = 46
    Align = alTop
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 0
    object Label3: TLabel
      Left = 10
      Top = 0
      Width = 149
      Height = 19
      Caption = #1050#1086#1085#1090#1088#1086#1083#1100'  '#1090#1086#1083#1097#1080#1085#1099
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMenuHighlight
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 469
      Top = 26
      Width = 82
      Height = 14
      Caption = #1052#1080#1085'. '#1058#1086#1083#1097#1080#1085#1072
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMenuHighlight
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      Visible = False
    end
    object Label1: TLabel
      Left = 620
      Top = 26
      Width = 36
      Height = 14
      Caption = #1074' '#1079#1086#1085#1077
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMenuHighlight
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      Visible = False
    end
    object cbThick: TCheckBox
      Left = 163
      Top = 3
      Width = 75
      Height = 17
      Hint = '       '
      Caption = #1042' '#1088#1072#1073#1086#1090#1077
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = cbThickClick
    end
    inline FRBordersThick: TFRBorders
      Left = 10
      Top = 21
      Width = 359
      Height = 22
      TabOrder = 1
      ExplicitLeft = 10
      ExplicitTop = 21
      ExplicitWidth = 359
    end
    object Panel2: TPanel
      Left = 554
      Top = 21
      Width = 60
      Height = 22
      BorderStyle = bsSingle
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      Visible = False
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
    object Panel1: TPanel
      Left = 662
      Top = 21
      Width = 60
      Height = 22
      BorderStyle = bsSingle
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      Visible = False
    end
  end
  object Chart1: TChart
    Left = 0
    Top = 46
    Width = 770
    Height = 249
    BackWall.Color = clBtnFace
    BackWall.Transparent = False
    BottomWall.Visible = False
    Foot.Alignment = taLeftJustify
    Foot.Visible = False
    Foot.AdjustFrame = False
    LeftWall.Visible = False
    Legend.Visible = False
    MarginBottom = 0
    MarginLeft = 0
    MarginRight = 5
    MarginTop = 0
    MarginUnits = muPixels
    PrintProportional = False
    SubFoot.Alignment = taLeftJustify
    SubFoot.Visible = False
    SubTitle.Alignment = taLeftJustify
    SubTitle.Visible = False
    Title.Alignment = taLeftJustify
    Title.Text.Strings = (
      '')
    Title.Visible = False
    BottomAxis.Automatic = False
    BottomAxis.AutomaticMaximum = False
    BottomAxis.AutomaticMinimum = False
    BottomAxis.Axis.Width = 1
    BottomAxis.ExactDateTime = False
    BottomAxis.Increment = 1.000000000000000000
    BottomAxis.Maximum = 8.000000000000000000
    BottomAxis.MaximumOffset = 1
    BottomAxis.MinorTickCount = 0
    DepthAxis.Automatic = False
    DepthAxis.AutomaticMaximum = False
    DepthAxis.AutomaticMinimum = False
    DepthAxis.ExactDateTime = False
    DepthAxis.Increment = 1.000000000000000000
    DepthTopAxis.Automatic = False
    DepthTopAxis.AutomaticMaximum = False
    DepthTopAxis.AutomaticMinimum = False
    DepthTopAxis.ExactDateTime = False
    DepthTopAxis.Increment = 1.000000000000000000
    Emboss.Color = clLime
    LeftAxis.Automatic = False
    LeftAxis.AutomaticMaximum = False
    LeftAxis.AutomaticMinimum = False
    LeftAxis.AxisValuesFormat = '#,##0.0#'
    LeftAxis.ExactDateTime = False
    LeftAxis.LabelsMultiLine = True
    LeftAxis.LabelsOnAxis = False
    LeftAxis.Maximum = 10.000000000000000000
    LeftAxis.MinorTicks.Visible = False
    Pages.AutoScale = True
    Pages.MaxPointsPerPage = 7
    RightAxis.Automatic = False
    RightAxis.AutomaticMaximum = False
    RightAxis.AutomaticMinimum = False
    RightAxis.Visible = False
    Shadow.Color = clRed
    Shadow.Visible = False
    TopAxis.Automatic = False
    TopAxis.AutomaticMaximum = False
    TopAxis.AutomaticMinimum = False
    TopAxis.Visible = False
    View3D = False
    Zoom.Allow = False
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 1
    DefaultCanvas = 'TGDIPlusCanvas'
    PrintMargins = (
      15
      15
      15
      45)
    ColorPaletteIndex = 13
    object Series3: TBarSeries
      Legend.Visible = False
      ColorEachPoint = True
      Depth = 0
      Marks.Visible = False
      Marks.Margins.Left = 44
      Marks.Arrow.Visible = False
      Marks.AutoPosition = False
      Marks.Callout.Arrow.Visible = False
      ShowInLegend = False
      BarRound = brNone
      BarWidthPercent = 100
      Dark3D = False
      MarksOnBar = True
      MultiBar = mbStacked
      OffsetPercent = 50
      Shadow.Visible = False
      YOrigin = 3.000000000000000000
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Bar'
      YValues.Order = loNone
      Data = {
        0007000000000000000050894000000000004887400000000000A88640000000
        000008864000000000006885400000000000F084400000000000D08140}
    end
  end
end
