object PositsEditorF: TPositsEditorF
  Left = 254
  Top = 155
  Width = 905
  Height = 634
  Caption = #1056#1077#1076#1072#1082#1090#1086#1088' '#1087#1086#1079#1080#1094#1080#1081
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poMainFormCenter
  Visible = True
  PixelsPerInch = 96
  TextHeight = 13
  object G: TDBGrid
    Left = 0
    Top = 29
    Width = 897
    Height = 578
    Align = alClient
    DataSource = DS
    TabOrder = 0
    TitleFont.Charset = RUSSIAN_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'id'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clGreen
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Title.Caption = #1053#1086#1084#1077#1088' '#1087#1086#1079#1080#1094#1080#1080
        Width = 91
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'name'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clGreen
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Title.Caption = #1053#1072#1079#1074#1072#1085#1080#1077
        Width = 370
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'station'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clGreen
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Title.Caption = #1057#1090#1072#1085#1094#1080#1103
        Width = 250
        Visible = True
      end
      item
        Color = 15135743
        Expanded = False
        FieldName = 'a'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Title.Caption = #1047#1086#1083#1100#1085#1086#1089#1090#1100
        Visible = True
      end
      item
        Color = 16773360
        Expanded = False
        FieldName = 'w'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Title.Caption = #1042#1083#1072#1078#1085#1086#1089#1090#1100
        Visible = True
      end>
  end
  object ToolBar: TToolBar
    Left = 0
    Top = 0
    Width = 897
    Height = 29
    ButtonHeight = 23
    Caption = 'ToolBar'
    Flat = True
    TabOrder = 1
    object SBRefresh: TSpeedButton
      Left = 0
      Top = 0
      Width = 89
      Height = 23
      Cursor = crHandPoint
      Caption = #1054#1073#1085#1086#1074#1080#1090#1100
      Flat = True
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsUnderline]
      ParentFont = False
      Transparent = False
      OnClick = SBRefreshClick
    end
    object ToolButton4: TToolButton
      Left = 89
      Top = 0
      Width = 8
      Caption = 'ToolButton4'
      ImageIndex = 2
      Style = tbsSeparator
    end
    object SBNewP: TSpeedButton
      Left = 97
      Top = 0
      Width = 89
      Height = 23
      Cursor = crHandPoint
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100
      Flat = True
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsUnderline]
      ParentFont = False
      Transparent = False
      OnClick = SBNewPClick
    end
    object ToolButton1: TToolButton
      Left = 186
      Top = 0
      Width = 8
      Caption = 'ToolButton1'
      Style = tbsSeparator
    end
    object SBDelP: TSpeedButton
      Left = 194
      Top = 0
      Width = 80
      Height = 23
      Cursor = crHandPoint
      Caption = #1059#1076#1072#1083#1080#1090#1100
      Flat = True
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsUnderline]
      ParentFont = False
      Transparent = False
      OnClick = SBDelPClick
    end
    object ToolButton2: TToolButton
      Left = 274
      Top = 0
      Width = 8
      Caption = 'ToolButton2'
      ImageIndex = 0
      Style = tbsSeparator
    end
    object SBFindV: TSpeedButton
      Left = 282
      Top = 0
      Width = 56
      Height = 23
      Cursor = crHandPoint
      Caption = #1053#1072#1081#1090#1080
      Flat = True
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsUnderline]
      ParentFont = False
      Transparent = False
      OnClick = SBFindVClick
    end
    object EF: TEdit
      Left = 338
      Top = 0
      Width = 80
      Height = 23
      TabStop = False
      Color = 15921906
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = 5263440
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnKeyPress = EFKeyPress
    end
    object ToolButton3: TToolButton
      Left = 418
      Top = 0
      Width = 8
      Caption = 'ToolButton3'
      ImageIndex = 1
      Style = tbsSeparator
    end
    object DBNavigator: TDBNavigator
      Left = 426
      Top = 0
      Width = 224
      Height = 23
      Cursor = crHandPoint
      DataSource = DS
      VisibleButtons = [nbFirst, nbPrior, nbNext, nbLast, nbEdit, nbPost, nbCancel, nbRefresh]
      Flat = True
      TabOrder = 1
    end
  end
  object DS: TDataSource
    DataSet = t
    Left = 304
    Top = 24
  end
  object t: TZTable
    Connection = DM.db
    SortedFields = 'id'
    Filter = 'id>0'
    Filtered = True
    RequestLive = True
    CachedUpdates = False
    TableName = 'posits'
    ShowRecordTypes = [utUnmodified, utModified, utInserted]
    UpdateMode = umUpdateChanged
    WhereMode = wmWhereKeyOnly
    Options = [doCalcDefaults]
    Left = 272
    Top = 24
    object tid: TIntegerField
      FieldName = 'id'
      Required = True
    end
    object tname: TStringField
      FieldName = 'name'
      Required = True
      Size = 255
    end
    object tstation: TStringField
      FieldName = 'station'
      Required = True
      Size = 255
    end
    object ta: TFloatField
      FieldName = 'a'
      DisplayFormat = '0.0'
    end
    object tw: TFloatField
      FieldName = 'w'
      DisplayFormat = '0.0'
    end
  end
end
