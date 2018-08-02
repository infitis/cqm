object CteF: TCteF
  Left = 253
  Top = 132
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = #1056#1077#1076#1072#1082#1090#1086#1088' '#1090#1080#1087#1086#1074' '#1091#1075#1083#1077#1081
  ClientHeight = 521
  ClientWidth = 769
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object GBp: TGroupBox
    Left = 0
    Top = 0
    Width = 769
    Height = 265
    Caption = #1055#1086#1079#1080#1094#1080#1080
    TabOrder = 0
    object Gp: TDBGrid
      Left = 8
      Top = 16
      Width = 753
      Height = 209
      DataSource = dsp
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      Columns = <
        item
          Expanded = False
          FieldName = 'id'
          Title.Caption = #8470
          Width = 58
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'name'
          Title.Caption = #1053#1072#1079#1074#1072#1085#1080#1077
          Width = 355
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'station'
          Title.Caption = #1057#1090#1072#1085#1094#1080#1103
          Width = 232
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'a'
          Width = 35
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'w'
          Width = 31
          Visible = True
        end>
    end
    object Np: TDBNavigator
      Left = 8
      Top = 232
      Width = 240
      Height = 25
      DataSource = dsp
      Flat = True
      TabOrder = 1
    end
  end
  object GBr: TGroupBox
    Left = 0
    Top = 265
    Width = 193
    Height = 256
    Caption = #1052#1072#1088#1082#1080' '#1091#1075#1083#1077#1081
    TabOrder = 1
    object Gr: TDBGrid
      Left = 8
      Top = 16
      Width = 177
      Height = 209
      DataSource = dsr
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      Columns = <
        item
          Expanded = False
          FieldName = 'name'
          Title.Caption = #1053#1072#1079#1074#1072#1085#1080#1077
          Width = 53
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'hhv'
          Title.Caption = #1053#1058#1047'(Q)'
          Width = 48
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'k'
          Width = 33
          Visible = True
        end>
    end
    object Nr: TDBNavigator
      Left = 8
      Top = 226
      Width = 176
      Height = 25
      DataSource = dsr
      VisibleButtons = [nbFirst, nbLast, nbInsert, nbDelete, nbEdit, nbPost, nbCancel, nbRefresh]
      Flat = True
      TabOrder = 1
    end
  end
  object GBt: TGroupBox
    Left = 192
    Top = 265
    Width = 577
    Height = 256
    Caption = #1058#1080#1087#1099' '#1091#1075#1083#1077#1081
    TabOrder = 2
    object SBDelete: TSpeedButton
      Left = 8
      Top = 226
      Width = 73
      Height = 25
      Cursor = crHandPoint
      Caption = #1059#1076#1072#1083#1080#1090#1100
      Flat = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsUnderline]
      ParentFont = False
      OnClick = SBDeleteClick
    end
    object SpeedButton1: TSpeedButton
      Left = 496
      Top = 226
      Width = 73
      Height = 25
      Cursor = crHandPoint
      Caption = #1047#1072#1082#1088#1099#1090#1100
      Flat = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsUnderline]
      ParentFont = False
      OnClick = SpeedButton1Click
    end
    object Gt: TDBGrid
      Left = 8
      Top = 16
      Width = 321
      Height = 209
      DataSource = dst
      Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgCancelOnExit]
      ReadOnly = True
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'Tahoma'
      TitleFont.Style = []
      OnDblClick = GtDblClick
      Columns = <
        item
          Expanded = False
          FieldName = 'COALRANK'
          Title.Caption = #1052#1072#1088#1082#1072
          Width = 45
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'POSNAME'
          Title.Caption = #1055#1086#1079#1080#1094#1080#1103
          Width = 188
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'COALTYPE'
          Title.Caption = #1058#1080#1087' '#1091#1075#1083#1103
          Width = 47
          Visible = True
        end>
    end
    object RG1: TRadioGroup
      Left = 336
      Top = 112
      Width = 233
      Height = 113
      Caption = #1055#1086#1082#1072#1079#1099#1074#1072#1090#1100
      TabOrder = 1
    end
    object RBpos: TRadioButton
      Left = 344
      Top = 128
      Width = 177
      Height = 17
      Caption = #1058#1080#1087#1099' '#1076#1083#1103' '#1074#1099#1073#1088#1072#1085#1085#1086#1081' '#1087#1086#1079#1080#1094#1080#1080
      TabOrder = 2
      OnClick = RBposrankClick
    end
    object RBrank: TRadioButton
      Left = 344
      Top = 152
      Width = 177
      Height = 17
      Caption = #1058#1080#1087#1099' '#1076#1083#1103' '#1074#1099#1073#1088#1072#1085#1085#1086#1081' '#1084#1072#1088#1082#1080
      TabOrder = 3
      OnClick = RBposrankClick
    end
    object RBposrank: TRadioButton
      Left = 344
      Top = 176
      Width = 217
      Height = 17
      Caption = #1058#1080#1087#1099' '#1076#1083#1103' '#1074#1099#1073#1088#1072#1085#1085#1099#1093' '#1087#1086#1079#1080#1094#1080#1080' '#1080' '#1084#1072#1088#1082#1080
      TabOrder = 4
      OnClick = RBposrankClick
    end
    object RBall: TRadioButton
      Left = 344
      Top = 200
      Width = 81
      Height = 17
      Caption = #1042#1089#1077' '#1090#1080#1087#1099
      Checked = True
      TabOrder = 5
      TabStop = True
      OnClick = RBposrankClick
    end
    object GBAdd: TGroupBox
      Left = 336
      Top = 16
      Width = 233
      Height = 97
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1090#1080#1087' '#1091#1075#1083#1103' '#1076#1083#1103':'
      TabOrder = 6
      object SBAdd: TSpeedButton
        Left = 8
        Top = 16
        Width = 201
        Height = 25
        Cursor = crHandPoint
        BiDiMode = bdLeftToRight
        Caption = #1079#1072#1076#1072#1085#1085#1086#1081' '#1084#1072#1088#1082#1080' '#1080' '#1079#1072#1076#1072#1085#1085#1086#1081' '#1087#1086#1079#1080#1094#1080#1080
        Flat = True
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsUnderline]
        ParentFont = False
        ParentBiDiMode = False
        OnClick = SBAddClick
      end
      object SBAdd4r: TSpeedButton
        Left = 8
        Top = 41
        Width = 169
        Height = 25
        Cursor = crHandPoint
        BiDiMode = bdLeftToRight
        Caption = #1079#1072#1076#1072#1085#1085#1086#1081' '#1084#1072#1088#1082#1080' ('#1074#1089#1077' '#1087#1086#1079#1080#1094#1080#1080')'
        Flat = True
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsUnderline]
        ParentFont = False
        ParentBiDiMode = False
        OnClick = SBAdd4rClick
      end
      object SBAdd4p: TSpeedButton
        Left = 8
        Top = 66
        Width = 169
        Height = 25
        Cursor = crHandPoint
        BiDiMode = bdLeftToRight
        Caption = #1079#1072#1076#1072#1085#1085#1086#1081' '#1087#1086#1079#1080#1094#1080#1080' ('#1074#1089#1077' '#1084#1072#1088#1082#1080')'
        Flat = True
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsUnderline]
        ParentFont = False
        ParentBiDiMode = False
        OnClick = SBAdd4pClick
      end
    end
  end
  object dsp: TDataSource
    DataSet = tp
    Left = 128
    Top = 136
  end
  object dsr: TDataSource
    DataSet = tr
    Left = 72
    Top = 360
  end
  object dst: TDataSource
    DataSet = tt
    Left = 288
    Top = 432
  end
  object tp: TZTable
    Connection = DM.db
    SortedFields = 'ID'
    AfterScroll = tOnScroll
    Filter = 'ID>0'
    Filtered = True
    RequestLive = True
    CachedUpdates = False
    TableName = 'posits'
    ShowRecordTypes = [utUnmodified, utModified, utInserted]
    UpdateMode = umUpdateChanged
    WhereMode = wmWhereKeyOnly
    Options = [doCalcDefaults]
    Left = 96
    Top = 136
    object tpa: TFloatField
      FieldName = 'a'
      DisplayFormat = '#0.0'
    end
    object tpw: TFloatField
      FieldName = 'w'
      DisplayFormat = '#0.0'
    end
    object tpid: TIntegerField
      FieldName = 'id'
      Required = True
    end
    object tpname: TStringField
      FieldName = 'name'
      Required = True
      Size = 255
    end
    object tpstation: TStringField
      FieldName = 'station'
      Required = True
      Size = 255
    end
  end
  object tr: TZTable
    Connection = DM.db
    SortedFields = 'name'
    AfterScroll = tOnScroll
    Filter = 'ID>0'
    Filtered = True
    RequestLive = True
    CachedUpdates = False
    TableName = 'COALRANKS'
    ShowRecordTypes = [utUnmodified, utModified, utInserted]
    UpdateMode = umUpdateChanged
    WhereMode = wmWhereKeyOnly
    Options = [doCalcDefaults]
    Left = 40
    Top = 360
    object trhhv: TFloatField
      FieldName = 'hhv'
      DisplayFormat = '0.000'
    end
    object trk: TFloatField
      FieldName = 'k'
      DisplayFormat = '0.00'
    end
    object trname: TStringField
      FieldName = 'name'
      Required = True
      Size = 8
    end
    object trID: TIntegerField
      FieldName = 'ID'
      Required = True
    end
  end
  object tt: TZQuery
    Connection = DM.db
    RequestLive = False
    CachedUpdates = False
    SQL.Strings = (
      'select '
      'pos_id,'
      'coalrank_id,'
      'posits.name as posname, '
      'coalranks.name as coalrank, '
      'coaltypes.coaltype as coaltype'
      'from posits, coalranks, coaltypes'
      
        'where coaltypes.pos_id = posits.id and coaltypes.coalrank_id = c' +
        'oalranks.id'
      'order by coalrank_id desc, pos_id desc')
    ParamCheck = True
    Params = <>
    ShowRecordTypes = [utUnmodified, utModified, utInserted]
    UpdateMode = umUpdateChanged
    WhereMode = wmWhereKeyOnly
    Options = [doCalcDefaults]
    Left = 256
    Top = 432
    object ttPOSNAME: TStringField
      FieldName = 'POSNAME'
      ReadOnly = True
      Required = True
      Size = 256
    end
    object ttCOALRANK: TStringField
      FieldName = 'COALRANK'
      ReadOnly = True
      Size = 8
    end
    object ttCOALTYPE: TIntegerField
      FieldName = 'COALTYPE'
      Required = True
    end
    object ttPOS_ID: TIntegerField
      FieldName = 'POS_ID'
      Required = True
    end
    object ttCOALRANK_ID: TIntegerField
      FieldName = 'COALRANK_ID'
      Required = True
    end
  end
end
