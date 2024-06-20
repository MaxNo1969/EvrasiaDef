object FRViewZone: TFRViewZone
  Left = 0
  Top = 0
  Width = 380
  Height = 268
  TabOrder = 0
  OnResize = FrameResize
  object Chart1: TChart
    Left = 0
    Top = 0
    Width = 380
    Height = 268
    BackWall.Transparent = False
    Legend.Visible = False
    MarginBottom = 2
    MarginLeft = 2
    MarginRight = 2
    MarginTop = 2
    MarginUnits = muPixels
    Title.Alignment = taLeftJustify
    Title.Text.Strings = (
      'TChart')
    OnClickBackground = Chart1ClickBackground
    OnClickSeries = Chart1ClickSeries
    DepthAxis.Automatic = False
    DepthAxis.AutomaticMaximum = False
    DepthAxis.AutomaticMinimum = False
    DepthAxis.Maximum = 0.530000000000000000
    DepthAxis.Minimum = -0.470000000000000000
    DepthTopAxis.Automatic = False
    DepthTopAxis.AutomaticMaximum = False
    DepthTopAxis.AutomaticMinimum = False
    DepthTopAxis.Maximum = 0.530000000000000000
    DepthTopAxis.Minimum = -0.470000000000000000
    LeftAxis.Automatic = False
    LeftAxis.AutomaticMaximum = False
    LeftAxis.AutomaticMinimum = False
    LeftAxis.Maximum = 103.000000000000000000
    LeftAxis.Minimum = 3.000000000000000000
    RightAxis.Automatic = False
    RightAxis.AutomaticMaximum = False
    RightAxis.AutomaticMinimum = False
    View3D = False
    Align = alClient
    BevelOuter = bvNone
    TabOrder = 0
    DefaultCanvas = 'TGDIPlusCanvas'
    ColorPaletteIndex = 13
    object CheckBox1: TCheckBox
      Left = 238
      Top = 2
      Width = 90
      Height = 17
      Caption = #1050#1072#1083#1080#1073#1088#1086#1074#1072#1090#1100
      Checked = True
      State = cbChecked
      TabOrder = 0
    end
    object BarOut: TBarSeries
      BarPen.Visible = False
      ColorEachPoint = True
      Marks.Visible = False
      Dark3D = False
      Emboss.Color = 8553090
      Shadow.Color = 8553090
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Bar'
      YValues.Order = loNone
    end
    object BarIn: TBarSeries
      BarPen.Visible = False
      ColorEachPoint = True
      Marks.Visible = False
      Dark3D = False
      Emboss.Color = 8553090
      Shadow.Color = 8553090
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Bar'
      YValues.Order = loNone
    end
    object Out1: TLineSeries
      SeriesColor = 3513587
      Brush.BackColor = clDefault
      LinePen.Color = 3513587
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object Out2: TLineSeries
      Brush.BackColor = clDefault
      LinePen.Color = 1330417
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object In1: TLineSeries
      SeriesColor = 1330417
      Brush.BackColor = clDefault
      LinePen.Color = 1330417
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object In2: TLineSeries
      SeriesColor = 1330417
      Brush.BackColor = clDefault
      LinePen.Color = 1330417
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object Zero: TLineSeries
      SeriesColor = 1330417
      Brush.BackColor = clDefault
      LinePen.Color = 1330417
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
  end
  object Edit1: TEdit
    Left = 326
    Top = 0
    Width = 33
    Height = 21
    TabOrder = 1
    OnExit = Edit1Exit
    OnKeyDown = Edit1KeyDown
  end
  object CSpinButton1: TCSpinButton
    Left = 365
    Top = 0
    Width = 15
    Height = 21
    DownGlyph.Data = {
      0E010000424D0E01000000000000360000002800000009000000060000000100
      200000000000D800000000000000000000000000000000000000008080000080
      8000008080000080800000808000008080000080800000808000008080000080
      8000008080000080800000808000000000000080800000808000008080000080
      8000008080000080800000808000000000000000000000000000008080000080
      8000008080000080800000808000000000000000000000000000000000000000
      0000008080000080800000808000000000000000000000000000000000000000
      0000000000000000000000808000008080000080800000808000008080000080
      800000808000008080000080800000808000}
    TabOrder = 2
    UpGlyph.Data = {
      0E010000424D0E01000000000000360000002800000009000000060000000100
      200000000000D800000000000000000000000000000000000000008080000080
      8000008080000080800000808000008080000080800000808000008080000080
      8000000000000000000000000000000000000000000000000000000000000080
      8000008080000080800000000000000000000000000000000000000000000080
      8000008080000080800000808000008080000000000000000000000000000080
      8000008080000080800000808000008080000080800000808000000000000080
      8000008080000080800000808000008080000080800000808000008080000080
      800000808000008080000080800000808000}
    OnDownClick = CSpinButton1DownClick
    OnUpClick = CSpinButton1UpClick
  end
  object PopupMenu1: TPopupMenu
    Top = 24
    object N1: TMenuItem
      Caption = #1050#1072#1083#1080#1073#1088#1086#1074#1072#1090#1100
      OnClick = N1Click
    end
  end
end
