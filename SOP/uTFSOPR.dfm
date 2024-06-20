object FSOPR: TFSOPR
  Left = 0
  Top = 0
  Caption = #1069#1090#1072#1083#1086#1085#1099
  ClientHeight = 966
  ClientWidth = 733
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 33
    Height = 13
    Caption = #1057#1054#1055#1099
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 8
    Top = 246
    Width = 117
    Height = 13
    Caption = #1050#1086#1085#1090#1088#1086#1083#1100#1085#1099#1077' '#1090#1086#1095#1082#1080
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 8
    Top = 498
    Width = 89
    Height = 13
    Caption = #1046#1091#1088#1085#1072#1083' '#1089#1074#1077#1088#1082#1080
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object DBGrid1: TDBGrid
    Left = 8
    Top = 24
    Width = 438
    Height = 185
    DataSource = DataEtalons
    Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit, dgMultiSelect, dgTitleClick, dgTitleHotTrack]
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    Columns = <
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'SOP'
        Title.Alignment = taCenter
        Title.Caption = #1053#1072#1079#1074#1072#1085#1080#1077
        Width = 205
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'TypeSize'
        PickList.Strings = (
          'sss'
          'sdfsd'
          'sdf')
        Title.Alignment = taCenter
        Title.Caption = #1058#1080#1087#1086#1088#1072#1079#1084#1077#1088
        Width = 93
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Date'
        ReadOnly = True
        Title.Alignment = taCenter
        Title.Caption = #1044#1072#1090#1072' '#1079#1072#1085#1077#1089#1077#1085#1080#1103
        Width = 119
        Visible = True
      end>
  end
  object DBNavigator1: TDBNavigator
    Left = 8
    Top = 207
    Width = 285
    Height = 25
    DataSource = DataEtalons
    VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbRefresh]
    TabOrder = 1
  end
  object DBGrid2: TDBGrid
    Left = 8
    Top = 265
    Width = 665
    Height = 200
    DataSource = DataSource2
    TabOrder = 2
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnColExit = DBGrid2ColExit
    Columns = <
      item
        Expanded = False
        FieldName = 'Module'
        PickList.Strings = (
          #1058#1086#1083#1097#1080#1085#1086#1084#1077#1088
          #1055#1086#1087#1077#1088#1077#1095#1085#1099#1081
          #1055#1088#1086#1076#1086#1083#1100#1085#1099#1081)
        Title.Caption = #1052#1086#1076#1091#1083#1100
        Width = 93
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'DefType'
        Title.Caption = #1058#1080#1087
        Width = 86
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'DefPoint'
        Title.Caption = #1055#1086#1083#1086#1078#1077#1085#1080#1077','#1084#1084
        Width = 88
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'DefRadius'
        Title.Caption = #1056#1072#1076#1080#1091#1089
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'isTopBrackBorder'
        PickList.Strings = (
          #1044#1072
          #1053#1077#1090)
        Title.Caption = #1042#1077#1088#1093'. '#1087#1086#1088#1086#1075
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'TopBorderPercent'
        Title.Caption = #1042#1077#1088#1093'. %'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'isBottomBrackBorder'
        PickList.Strings = (
          #1044#1072
          #1053#1077#1090)
        Title.Caption = #1053#1080#1078#1085'.'#1087#1086#1088#1086#1075
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'BottomBorderPercent'
        Title.Caption = #1053#1080#1078#1085'. %'
        Visible = True
      end>
  end
  object DBNavigator2: TDBNavigator
    Left = 8
    Top = 465
    Width = 290
    Height = 25
    DataSource = DataSource2
    VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbRefresh]
    TabOrder = 3
  end
  object DBNavigator3: TDBNavigator
    Left = 8
    Top = 669
    Width = 180
    Height = 25
    DataSource = DataSource3
    VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbRefresh]
    TabOrder = 4
    BeforeAction = DBNavigator3BeforeAction
  end
  object DBGrid3: TDBGrid
    Left = 8
    Top = 543
    Width = 665
    Height = 120
    DataSource = DataSource3
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit, dgMultiSelect, dgTitleClick, dgTitleHotTrack]
    TabOrder = 5
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'ID'
        Title.Caption = #1053#1086#1084#1077#1088
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Date'
        Title.Caption = #1044#1072#1090#1072
        Width = 112
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'SOP'
        Title.Caption = #1057#1054#1055
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'TypeSize'
        Title.Caption = #1058#1080#1087#1086#1088#1072#1079#1084#1077#1088
        Width = 63
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Result'
        Title.Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090
        Width = 61
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'MatchedDefects'
        Title.Caption = #1057#1086#1087#1072#1076#1077#1085#1080#1081
        Width = 63
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'NumOfDefects'
        Title.Caption = #1044#1077#1092#1077#1082#1090#1086#1074
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'Defectoscoper'
        Title.Caption = #1044#1077#1092#1077#1082#1090#1086#1089#1082#1086#1087#1080#1089#1090
        Width = 95
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'SaveAddress'
        Title.Caption = #1060#1072#1081#1083
        Width = 517
        Visible = True
      end>
  end
  object Panel: TPanel
    Left = 8
    Top = 512
    Width = 449
    Height = 25
    BevelOuter = bvNone
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 6
    object LTS: TLabel
      Left = 0
      Top = 5
      Width = 71
      Height = 16
      Caption = #1058#1080#1087#1086#1088#1072#1079#1084#1077#1088
    end
    object lDateFrom: TLabel
      Left = 150
      Top = 5
      Width = 39
      Height = 16
      Caption = #1044#1072#1090#1072' '#1089
    end
    object lDateTo: TLabel
      Left = 316
      Top = 4
      Width = 14
      Height = 16
      Caption = #1087#1086
    end
    object cbTypeSize: TComboBox
      Left = 77
      Top = 1
      Width = 57
      Height = 24
      Style = csDropDownList
      TabOrder = 0
      OnChange = cbTypeSizeChange
    end
    object dtpTo: TDateTimePicker
      Left = 337
      Top = 1
      Width = 113
      Height = 24
      Date = 41826.341551643520000000
      Time = 41826.341551643520000000
      TabOrder = 2
      OnChange = cbTypeSizeChange
    end
    object dtpFrom: TDateTimePicker
      Left = 197
      Top = 1
      Width = 113
      Height = 24
      Date = 41826.341551643520000000
      Time = 41826.341551643520000000
      TabOrder = 1
      OnChange = cbTypeSizeChange
    end
  end
  object Button1: TButton
    Left = 188
    Top = 669
    Width = 77
    Height = 25
    Caption = #1042#1099#1073#1088#1072#1090#1100' '#1074#1089#1077
    TabOrder = 7
    OnClick = Button1Click
  end
  inline FRSOPCheck1: TFRSOPCheck
    Left = 452
    Top = 7
    Width = 221
    Height = 225
    TabOrder = 9
    ExplicitLeft = 452
    ExplicitTop = 7
    ExplicitHeight = 225
    inherited GroupBox1: TGroupBox
      Height = 225
      ExplicitHeight = 225
    end
  end
  object Button3: TButton
    Left = 293
    Top = 208
    Width = 60
    Height = 25
    Caption = #1057#1074#1077#1088#1080#1090#1100
    TabOrder = 8
    OnClick = Button3Click
  end
  object DataEtalons: TDataSource
    DataSet = ADOTable1
    Left = 301
    Top = 4
  end
  object ADOTable1: TADOTable
    AfterInsert = ADOTable1AfterInsert
    AfterPost = ADOTable1AfterPost
    AfterDelete = ADOTable1AfterDelete
    OnNewRecord = ADOTable1NewRecord
    TableName = 'dbo.EtalonDefect'
    Left = 248
    Top = 65528
  end
  object ADOTable2: TADOTable
    MasterFields = 'SOP'
    MasterSource = DataEtalons
    TableName = 'dbo.EtalonTubeDefects'
    Left = 392
    Top = 464
  end
  object DataSource2: TDataSource
    DataSet = ADOTable2
    OnDataChange = DataSource2DataChange
    OnUpdateData = DataSource2UpdateData
    Left = 456
    Top = 464
  end
  object DataSource3: TDataSource
    DataSet = ADOTable3
    Left = 440
    Top = 669
  end
  object ADOTable3: TADOTable
    Filtered = True
    MaxRecords = 100
    BeforeRefresh = ADOTable3BeforeRefresh
    TableName = 'dbo.EtalonCheckResult'
    Left = 376
    Top = 669
  end
end
