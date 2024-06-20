object FRLineRemote: TFRLineRemote
  Left = 0
  Top = 0
  Width = 1023
  Height = 201
  TabOrder = 0
  object Chart1: TChart
    Left = 0
    Top = 46
    Width = 1023
    Height = 155
    Legend.Visible = False
    MarginBottom = 0
    MarginLeft = 17
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
    LeftAxis.Maximum = 3.000000000000000000
    LeftAxis.MinorTickCount = 0
    LeftAxis.MinorTickLength = 0
    LeftAxis.TicksInner.Visible = False
    View3D = False
    Zoom.Allow = False
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 0
    DefaultCanvas = 'TGDIPlusCanvas'
    ColorPaletteIndex = 13
    object Series1: TBarSeries
      ColorEachPoint = True
      Marks.Visible = False
      BarWidthPercent = 100
      Emboss.Color = 8553090
      Emboss.HorizSize = 2
      MultiBar = mbStacked
      Shadow.Color = 8553090
      Shadow.Visible = False
      SideMargins = False
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Bar'
      YValues.Order = loNone
      Data = {
        000600000000000000000C82400000000000DC84400000000000D08140000000
        00001484400000000000A886400000000000888840}
    end
    object Series2: TBarSeries
      ColorEachPoint = True
      Marks.Visible = False
      BarWidthPercent = 100
      Emboss.Color = 8553090
      Emboss.HorizSize = 2
      MultiBar = mbStacked
      Shadow.Color = 8553090
      Shadow.Visible = False
      SideMargins = False
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Bar'
      YValues.Order = loNone
      Data = {
        000600000000000000000C82400000000000DC84400000000000D08140000000
        00001484400000000000A886400000000000888840}
    end
    object Series3: TBarSeries
      ColorEachPoint = True
      Marks.Visible = False
      BarWidthPercent = 100
      Emboss.Color = 8487297
      Emboss.HorizSize = 2
      MultiBar = mbStacked
      Shadow.Color = 8487297
      Shadow.Visible = False
      SideMargins = False
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Bar'
      YValues.Order = loNone
      Data = {
        000600000000000000000C82400000000000DC84400000000000D08140000000
        00001484400000000000A886400000000000888840}
    end
    object Series4: TBarSeries
      ColorEachPoint = True
      Marks.Visible = False
      BarWidthPercent = 100
      Emboss.Color = 8487297
      Emboss.HorizSize = 2
      MultiBar = mbStacked
      Shadow.Color = 8487297
      Shadow.Visible = False
      SideMargins = False
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Bar'
      YValues.Order = loNone
      Data = {
        000600000000000000000C82400000000000DC84400000000000D08140000000
        00001484400000000000A886400000000000888840}
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1023
    Height = 46
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 1
    object Label2: TLabel
      Left = 10
      Top = 0
      Width = 206
      Height = 19
      Caption = #1055#1088#1086#1076#1086#1083#1100#1085#1072#1103' '#1076#1077#1092#1077#1082#1090#1086#1089#1082#1086#1087#1080#1103
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clActiveCaption
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object cbLinear: TCheckBox
      Left = 222
      Top = 5
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
      OnClick = cbLinearClick
    end
    inline FRBordersLine: TFRBorders
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
      Top = 21
      Width = 271
      Height = 23
      TabOrder = 2
      ExplicitLeft = 470
      ExplicitTop = 21
      inherited Label13: TLabel
        Visible = False
      end
      inherited Label5: TLabel
        Visible = False
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
