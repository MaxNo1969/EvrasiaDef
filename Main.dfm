object MainForm: TMainForm
  Left = -44
  Top = 0
  Caption = #1041#1059#1056#1040#1053'-5000. '#1059#1089#1090#1072#1085#1086#1074#1082#1072' '#1085#1077#1088#1072#1079#1088#1091#1096#1072#1102#1097#1077#1075#1086' '#1082#1086#1085#1090#1088#1086#1083#1103' '#1053#1050#1058
  ClientHeight = 806
  ClientWidth = 1268
  Color = clBtnFace
  Constraints.MinHeight = 100
  Constraints.MinWidth = 100
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clBlack
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 5
    Top = 44
    Width = 88
    Height = 18
    Caption = #1058#1080#1087#1086#1088#1072#1079#1084#1077#1088':'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
  end
  object StatusBarTop: TStatusBar
    Left = 215
    Top = 39
    Width = 1284
    Height = 22
    Align = alNone
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = 20
    Font.Name = 'Tahoma'
    Font.Style = []
    Panels = <
      item
        Width = 200
      end
      item
        Width = 50
      end>
    Touch.ParentTabletOptions = False
    Touch.TabletOptions = []
    UseSystemFont = False
  end
  inline FRLine1: TFRLineRemote
    Left = 2
    Top = 410
    Width = 756
    Height = 100
    TabOrder = 1
    ExplicitLeft = 2
    ExplicitTop = 410
    ExplicitWidth = 756
    ExplicitHeight = 100
    inherited Chart1: TChart
      Width = 756
      Height = 54
      ExplicitWidth = 756
      ExplicitHeight = 54
    end
    inherited Panel1: TPanel
      Width = 756
      ExplicitWidth = 756
      inherited Label2: TLabel
        Font.Color = clMenuHighlight
        ParentColor = False
      end
    end
  end
  inline FRThick1: TFRThick
    Left = 2
    Top = 180
    Width = 710
    Height = 95
    TabOrder = 2
    ExplicitLeft = 2
    ExplicitTop = 180
    ExplicitWidth = 710
    ExplicitHeight = 95
    inherited Panel3: TPanel
      Width = 710
      ExplicitWidth = 710
      inherited Label3: TLabel
        ParentColor = False
      end
    end
    inherited Chart1: TChart
      Width = 710
      Height = 49
      LeftAxis.Maximum = 19.900000000000020000
      LeftAxis.Minimum = 9.900000000000015000
      ExplicitWidth = 710
      ExplicitHeight = 49
      PrintMargins = (
        15
        15
        15
        45)
    end
  end
  object ActionMainMenuBar1: TActionMainMenuBar
    Left = 0
    Top = 0
    Width = 1268
    Height = 25
    UseSystemFont = False
    ActionManager = ActionManager1
    Caption = 'ActionMainMenuBar1'
    Color = clMenuBar
    ColorMap.DisabledFontColor = 7171437
    ColorMap.HighlightColor = clWhite
    ColorMap.BtnSelectedFont = clBlack
    ColorMap.UnusedColor = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    Spacing = 0
  end
  inline FRStatist1: TFRStatist
    Left = 340
    Top = 0
    Width = 363
    Height = 40
    TabOrder = 3
    ExplicitLeft = 340
    ExplicitWidth = 363
    ExplicitHeight = 40
    inherited GroupBox1: TGroupBox
      Width = 363
      Height = 40
      ExplicitWidth = 363
      ExplicitHeight = 40
    end
  end
  object Button1: TButton
    Left = 8
    Top = 34
    Width = 75
    Height = 25
    Caption = 'Button1'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 6
    Visible = False
    OnClick = Button1Click
  end
  inline FRButtons1: TFRButtons
    Left = 8
    Top = 65
    Width = 825
    Height = 38
    TabOrder = 7
    ExplicitLeft = 8
    ExplicitTop = 65
    ExplicitWidth = 825
  end
  inline FRSumM1: TFRSumM
    Left = 8
    Top = 521
    Width = 1073
    Height = 200
    TabOrder = 8
    ExplicitLeft = 8
    ExplicitTop = 521
    ExplicitWidth = 1073
    ExplicitHeight = 200
    inherited Chart1: TChart
      Width = 1073
      Height = 151
      ExplicitWidth = 1073
      ExplicitHeight = 151
    end
    inherited Panel1: TPanel
      Width = 1073
      ExplicitWidth = 1073
    end
  end
  inline FRCross1: TFRCross
    Left = 0
    Top = 290
    Width = 833
    Height = 100
    TabOrder = 9
    ExplicitTop = 290
    ExplicitHeight = 100
    inherited Chart1: TChart
      Height = 54
      ExplicitHeight = 54
    end
    inherited Panel1: TPanel
      inherited Label2: TLabel
        ParentColor = False
      end
    end
  end
  inline FRSplit1: TFRSplit
    Left = 0
    Top = 279
    Width = 728
    Height = 4
    Cursor = crVSplit
    Color = clGray
    ParentBackground = False
    ParentColor = False
    TabOrder = 10
    ExplicitTop = 279
    ExplicitWidth = 728
    ExplicitHeight = 4
  end
  inline FRSplit2: TFRSplit
    Left = 0
    Top = 396
    Width = 728
    Height = 4
    Cursor = crVSplit
    Color = clGray
    ParentBackground = False
    ParentColor = False
    TabOrder = 11
    ExplicitTop = 396
    ExplicitWidth = 728
    ExplicitHeight = 4
  end
  inline FRSplit3: TFRSplit
    Left = 0
    Top = 516
    Width = 728
    Height = 4
    Cursor = crVSplit
    Color = clGray
    ParentBackground = False
    ParentColor = False
    TabOrder = 12
    ExplicitTop = 516
    ExplicitWidth = 728
    ExplicitHeight = 4
  end
  object Panel4: TPanel
    Left = 0
    Top = 126
    Width = 770
    Height = 5
    BevelOuter = bvLowered
    ParentBackground = False
    TabOrder = 13
  end
  inline FRSOP1: TFRSOP
    Left = 8
    Top = 104
    Width = 461
    Height = 22
    TabOrder = 14
    Visible = False
    ExplicitLeft = 8
    ExplicitTop = 104
  end
  inline FRSG1: TFRSG
    Left = 850
    Top = 80
    Width = 250
    Height = 39
    Color = clBtnFace
    ParentBackground = False
    ParentColor = False
    TabOrder = 15
    Visible = False
    ExplicitLeft = 850
    ExplicitTop = 80
  end
  object cbInterruptView: TCheckBox
    Left = 871
    Top = 62
    Width = 147
    Height = 17
    Caption = #1055#1088#1077#1088#1099#1074#1072#1085#1080#1077' '#1085#1072' '#1087#1088#1086#1089#1084#1086#1090#1088
    TabOrder = 0
  end
  object SaveToFileDialog: TSaveDialog
    DefaultExt = '.bindkb'
    Filter = #1044#1072#1085#1085#1099#1077' '#1087#1086' '#1090#1088#1091#1073#1077' (.bindkb)|*.bindkb|'#1042#1089#1077' '#1092#1072#1081#1083#1099'|*.*'
    Options = [ofHideReadOnly, ofNoChangeDir, ofShowHelp, ofEnableSizing]
    Left = 772
    Top = 2
  end
  object OpenDialogFromFile: TOpenDialog
    DefaultExt = '.bindkb'
    Filter = #1044#1072#1085#1085#1099#1077' '#1087#1086' '#1090#1088#1091#1073#1077'(.bindkb)|*.bindkb|'#1042#1089#1077' '#1092#1072#1081#1083#1099'|*.*'
    Options = [ofHideReadOnly, ofNoChangeDir, ofEnableSizing]
    Left = 808
    Top = 4
  end
  object ApplicationEvents: TApplicationEvents
    OnMessage = ApplicationEventsMessage
    Left = 728
  end
  object OtherTest: TPopupMenu
    BiDiMode = bdLeftToRight
    ParentBiDiMode = False
    Left = 680
    object TestRotation: TMenuItem
      Caption = #1058#1077#1089#1090' '#1089' '#1074#1088#1072#1097#1077#1085#1080#1077#1084
    end
  end
  object XPManifest1: TXPManifest
    Left = 618
    Top = 2
  end
  object ActionManager1: TActionManager
    ActionBars = <
      item
        Items = <
          item
            Items = <
              item
                Action = ActionPars
                Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1080', '#1087#1077#1088#1077#1089#1095#1077#1090
              end
              item
                Action = Action27
                Caption = #1054#1082#1085#1072' '#1087#1086' '#1091#1084#1086#1083#1095#1072#1085#1080#1102
              end>
            Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072
          end
          item
            Items = <
              item
                Action = Action7
                Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
              end
              item
                Action = Action8
                Caption = #1054#1090#1082#1088#1099#1090#1100
              end>
            Caption = #1058#1088#1091#1073#1072
          end
          item
            Items = <
              item
                Visible = False
                Action = Action9
                Caption = #1058#1077#1089#1090
              end
              item
                Visible = False
                Action = Action10
                Caption = #1058#1077#1089#1090' '#1091#1089#1090#1088#1086#1081#1089#1090#1074
              end
              item
                Visible = False
                Action = Action6
                Caption = #1058#1077#1089#1090' '#1089#1074#1103#1079#1080' '#1089' '#1052#1072#1088#1082#1077#1088#1086#1084
              end
              item
                Action = Action12
                Caption = #1057#1080#1075#1085#1072#1083#1099
              end
              item
                Action = Action13
                Caption = #1055#1088#1086#1090#1086#1082#1086#1083
              end>
            Caption = #1044#1080#1072#1075#1085#1086#1089#1090#1080#1082#1072
          end
          item
            Items = <
              item
                Action = Action17
                Caption = #1043#1088#1072#1092#1080#1082#1080' '#1043#1055
              end>
            Visible = False
            Caption = #1043#1088#1091#1087#1087#1072' '#1087#1088#1086#1095#1085#1086#1089#1090#1080
          end
          item
            Items = <
              item
                Action = Action21
                Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
              end>
            Caption = #1055#1086#1084#1086#1097#1100
          end
          item
            Items = <
              item
                Action = Action25
                Caption = #1057#1074#1077#1088#1082#1072
              end
              item
                Action = Action22
                Caption = #1044#1077#1092#1077#1082#1090#1086#1089#1082#1086#1087#1080#1089#1090#1099
              end>
            Visible = False
            Caption = #1050#1086#1085#1090#1088#1086#1083#1100' '#1057#1054#1055
          end>
        ActionBar = ActionMainMenuBar1
      end>
    Left = 8
    Top = 616
    StyleName = 'Platform Default'
    object Action1: TAction
      Caption = 'Action1'
    end
    object Action2: TAction
      Caption = 'Action2'
    end
    object Action3: TAction
      Caption = 'Action3'
    end
    object Action4: TAction
      Caption = 'Action4'
    end
    object Action5: TAction
      Caption = 'Action5'
    end
    object Action7: TAction
      Caption = 'Action7'
      OnExecute = menuSaveTubeClick
    end
    object Action8: TAction
      Caption = 'Action8'
      OnExecute = menuLoadTubeClick
    end
    object Action9: TAction
      Caption = 'Action9'
    end
    object Action10: TAction
      Caption = 'Action10'
      OnExecute = menuTestAdvantechClick
    end
    object Action11: TAction
      Caption = 'Action11'
    end
    object Action12: TAction
      Caption = 'Action12'
      OnExecute = menuSignalsStateClick
    end
    object Action13: TAction
      Caption = 'Action13'
      OnExecute = menuProtocolClick
    end
    object Action14: TAction
      Caption = 'Action14'
    end
    object Action15: TAction
      Caption = 'Action15'
    end
    object Action16: TAction
      Caption = 'Action16'
    end
    object Action17: TAction
      Caption = 'Action17'
    end
    object Action18: TAction
      Caption = 'Action18'
    end
    object Action19: TAction
      Caption = 'Action19'
    end
    object Action20: TAction
      Caption = 'Action20'
    end
    object Action21: TAction
      Caption = 'Action21'
      OnExecute = N1Click
    end
    object Action6: TAction
      Caption = 'Action6'
      Visible = False
    end
    object Action22: TAction
      Caption = 'Action22'
    end
    object Action23: TAction
      Caption = 'Action23'
    end
    object Action24: TAction
      Caption = 'Action24'
    end
    object Action25: TAction
      Caption = 'Action25'
      OnExecute = Action25Execute
    end
    object Action26: TAction
      Caption = 'Action26'
    end
    object Action27: TAction
      Caption = 'Action27'
      OnExecute = Action27Execute
    end
    object ActionPars: TAction
      Caption = 'ActonPars'
      OnExecute = ActionParsExecute
    end
  end
end
