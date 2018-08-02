object CustomVagonsEditorF: TCustomVagonsEditorF
  Left = 234
  Top = 135
  Width = 795
  Height = 512
  Caption = 'CustomVagonsEditorF'
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsMDIChild
  Icon.Data = {
    0000010001002020100000000000E80200001600000028000000200000004000
    000001000400000000008002000000000000000000000000000000000000A6A6
    A600AEAEAE00C6C6C600BABABA00D2D2D2000282FE00B6B6B600CECECE00C2C2
    C200AAAAAA00B2B2B200CACACA00BEBEBE00D6D6D6000000000000000000CCC3
    3A555A6AAA1A1119999000000000CCC33555551AA1111119999000000000C8C6
    555655519551A111199990000000CCC5553335555551A1111999900000008C55
    53333A5555AAAA11119999000000C555CC3C3655551AAAA1119999000000555C
    CCC36555555AA1111111999900005588C8C3555635559551A111999900005588
    8C35553366555551A11119999000555CCC5553333665551AA111191999002555
    C555CCC33A555551A111119999002255555CCCC33555A5559155911199902285
    55C8CCC655533A55555511191990B255555CCC355563366555511A119999B255
    8555C3555C3336A55551A1111199BB22225555553C33365555559A191119BBBB
    22855558CCC365553A5559551199BBB222855553CCC355566665555511197BBB
    22555555CC355536366155511A117BBBB255285553555333366555559111777B
    BBB222855555CCCC3A555A555195777BBBB222285553CC336555A66555554777
    BBBB22855555CC365553666A55557777BBBB2225585553355563666A55554477
    77BBBB22288555555C3336655555447777BBBBB22288555533C336555AA54447
    777BB2B228885555CCC36555666A4447777B7BB2B225555553C35556666AD444
    4777BBBB222558C5553555336666D444477777BBBB2222885555533333664D44
    44777BBBB2222888C5553C333666D4D44447777BBBB2222855555C3333360000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000}
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  PixelsPerInch = 96
  TextHeight = 13
  object ToolBar: TToolBar
    Left = 0
    Top = 0
    Width = 787
    Height = 30
    ButtonHeight = 24
    ButtonWidth = 8
    Caption = 'ToolBar'
    Color = 13421772
    Flat = True
    ParentColor = False
    TabOrder = 0
    Wrapable = False
    object SBNewV: TSpeedButton
      Left = 0
      Top = 0
      Width = 90
      Height = 24
      Cursor = crHandPoint
      Caption = #1042#1089#1090#1072#1074#1080#1090#1100' '#1074#1072#1075#1086#1085
      Flat = True
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsUnderline]
      ParentFont = False
      Transparent = False
      OnClick = SBNewVClick
    end
    object ToolButton4: TToolButton
      Left = 90
      Top = 0
      Width = 6
      Caption = 'ToolButton4'
      ImageIndex = 2
      Style = tbsSeparator
    end
    object SBMergeV: TSpeedButton
      Left = 96
      Top = 0
      Width = 150
      Height = 24
      Cursor = crHandPoint
      Caption = #1054#1073#1098#1077#1076#1080#1085#1080#1090#1100' '#1089#1086' '#1089#1083#1077#1076#1091#1102#1097#1080#1084
      Flat = True
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsUnderline]
      ParentFont = False
      Transparent = False
      OnClick = SBMergeVClick
    end
    object ToolButton1: TToolButton
      Left = 246
      Top = 0
      Width = 6
      Caption = 'ToolButton1'
      ImageIndex = 2
      Style = tbsSeparator
    end
    object SBMergeCust: TSpeedButton
      Left = 252
      Top = 0
      Width = 76
      Height = 24
      Cursor = crHandPoint
      Caption = #1054#1073#1098#1077#1076#1080#1085#1080#1090#1100
      Enabled = False
      Flat = True
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsUnderline]
      ParentFont = False
      Transparent = False
      OnClick = SBMergeCustClick
    end
    object PMergeCust: TPanel
      Left = 328
      Top = 0
      Width = 174
      Height = 24
      BevelOuter = bvNone
      TabOrder = 1
      object LN1: TLabel
        Left = 8
        Top = 8
        Width = 13
        Height = 13
        Caption = #8470
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object LN2: TLabel
        Left = 88
        Top = 8
        Width = 22
        Height = 13
        Caption = #1080' '#8470
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object E1: TEdit
        Left = 24
        Top = 2
        Width = 57
        Height = 21
        TabStop = False
        Color = 15921906
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = 5263440
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        ReadOnly = True
        TabOrder = 0
      end
      object E2: TEdit
        Left = 112
        Top = 2
        Width = 57
        Height = 21
        TabStop = False
        Color = 15921906
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = 5263440
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        ReadOnly = True
        TabOrder = 1
      end
    end
    object ToolButton2: TToolButton
      Left = 502
      Top = 0
      Width = 6
      Caption = 'ToolButton2'
      ImageIndex = 2
      Style = tbsSeparator
    end
    object SBDelV: TSpeedButton
      Left = 508
      Top = 0
      Width = 90
      Height = 24
      Cursor = crHandPoint
      Caption = #1059#1076#1072#1083#1080#1090#1100' '#1074#1072#1075#1086#1085
      Flat = True
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsUnderline]
      ParentFont = False
      Transparent = False
      OnMouseUp = SBDelVMouseUp
    end
    object ToolButton5: TToolButton
      Left = 598
      Top = 0
      Width = 6
      Caption = 'ToolButton5'
      ImageIndex = 2
      Style = tbsSeparator
    end
    object SBFindV: TSpeedButton
      Left = 604
      Top = 0
      Width = 50
      Height = 24
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
      Left = 654
      Top = 0
      Width = 80
      Height = 24
      TabStop = False
      Color = 15921906
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = 5263440
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnKeyPress = EFKeyPress
    end
    object ToolButton3: TToolButton
      Left = 734
      Top = 0
      Width = 6
      Caption = 'ToolButton3'
      ImageIndex = 1
      Style = tbsSeparator
    end
    object DBNavigator: TDBNavigator
      Left = 740
      Top = 0
      Width = 180
      Height = 24
      Cursor = crHandPoint
      DataSource = DS
      VisibleButtons = [nbFirst, nbLast, nbEdit, nbPost, nbCancel, nbRefresh]
      Flat = True
      TabOrder = 0
    end
  end
  object G: TDBGrid
    Left = 0
    Top = 60
    Width = 787
    Height = 406
    Align = alClient
    DataSource = DS
    FixedColor = 13421772
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgCancelOnExit]
    ParentFont = False
    PopupMenu = PopupMenu
    TabOrder = 1
    TitleFont.Charset = RUSSIAN_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnDblClick = GDblClick
    OnKeyUp = GKeyUp
    Columns = <
      item
        Color = 15921906
        Expanded = False
        FieldName = 'ID'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = 5263440
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ReadOnly = True
        Title.Caption = #8470
        Title.Font.Charset = RUSSIAN_CHARSET
        Title.Font.Color = 5263440
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = []
        Width = 51
        Visible = True
      end
      item
        Alignment = taRightJustify
        Expanded = False
        FieldName = 'MOMENT'
        Title.Caption = #1044#1072#1090#1072' '#1042#1088#1077#1084#1103
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'P'
        Title.Caption = 'P, '#1090
        Width = 47
        Visible = True
      end
      item
        Color = 15135743
        Expanded = False
        FieldName = 'A'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Title.Caption = 'A, %'
        Title.Font.Charset = RUSSIAN_CHARSET
        Title.Font.Color = clNavy
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = []
        Width = 42
        Visible = True
      end
      item
        Alignment = taRightJustify
        Expanded = False
        FieldName = 'RWDATE'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = 20480
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Title.Caption = #1078'/'#1076' '#1089#1091#1090#1082#1080
        Width = 66
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'NUMBER'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = 20480
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Title.Caption = #1053#1086#1084#1077#1088' '#1074#1072#1075#1086#1085#1072
        Width = 83
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'POS'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = 20480
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Title.Caption = #1055#1086#1079#1080#1094#1080#1103
        Width = 77
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'CERT'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = 20480
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Title.Caption = #1055#1072#1088#1090#1080#1103
        Width = 52
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'COALRANK_L'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = 20480
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Title.Caption = #1052#1072#1088#1082#1072' '#1091#1075#1083#1103
        Width = 69
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'WEI'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = 20480
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Title.Caption = #1042#1077#1089', '#1090
        Width = 40
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'W'
        Font.Charset = RUSSIAN_CHARSET
        Font.Color = 20480
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Title.Caption = #1042#1083#1072#1078#1085#1086#1089#1090#1100', %'
        Width = 78
        Visible = True
      end>
  end
  object Status: TStatusBar
    Left = 0
    Top = 466
    Width = 787
    Height = 19
    Panels = <>
    SimplePanel = True
  end
  object ToolBarVB: TToolBar
    Left = 0
    Top = 30
    Width = 787
    Height = 30
    ButtonHeight = 24
    ButtonWidth = 8
    Caption = 'ToolBarVB'
    Color = 13421772
    Flat = True
    ParentColor = False
    TabOrder = 3
    object SpeedButton1: TSpeedButton
      Left = 0
      Top = 0
      Width = 100
      Height = 24
      Cursor = crHandPoint
      Caption = #1042#1089#1090#1072#1074#1080#1090#1100' '#1087#1072#1088#1090#1080#1102
      Flat = True
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsUnderline]
      ParentFont = False
      Transparent = False
      OnClick = SpeedButton1Click
    end
    object ToolButton6: TToolButton
      Left = 100
      Top = 0
      Width = 8
      Caption = 'ToolButton6'
      Style = tbsSeparator
    end
    object SBNewBatch: TSpeedButton
      Left = 108
      Top = 0
      Width = 100
      Height = 24
      Cursor = crHandPoint
      Caption = #1048#1079#1084#1077#1085#1080#1090#1100' '#1087#1072#1088#1090#1080#1102
      Flat = True
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsUnderline]
      ParentFont = False
      Transparent = False
      OnClick = SBNewBatchClick
    end
  end
  object DS: TDataSource
    DataSet = q
    Left = 72
    Top = 120
  end
  object PopupMenu: TPopupMenu
    Left = 104
    Top = 122
    object N2days: TMenuItem
      Caption = '2 '#1076#1085#1103
      Checked = True
      GroupIndex = 1
      RadioItem = True
      OnClick = N2daysClick
    end
    object N1month: TMenuItem
      Caption = '1 '#1084#1077#1089#1103#1094
      GroupIndex = 1
      RadioItem = True
      OnClick = N1monthClick
    end
    object N1year: TMenuItem
      Caption = #1042#1089#1077
      GroupIndex = 1
      RadioItem = True
      OnClick = N1yearClick
    end
  end
  object q: TZQuery
    Connection = DM.db
    RequestLive = True
    CachedUpdates = False
    SQL.Strings = (
      'select * from vagons')
    ParamCheck = False
    Params = <>
    ShowRecordTypes = [utUnmodified, utModified, utInserted]
    UpdateMode = umUpdateChanged
    WhereMode = wmWhereKeyOnly
    Options = [doCalcDefaults]
    Left = 40
    Top = 120
    object qID: TIntegerField
      FieldName = 'ID'
      Required = True
    end
    object qMOMENT: TDateTimeField
      FieldName = 'MOMENT'
    end
    object qVNAME: TStringField
      FieldName = 'VNAME'
      Size = 16
    end
    object qCOALTYPE: TIntegerField
      FieldName = 'COALTYPE'
    end
    object qP: TFloatField
      FieldName = 'P'
      DisplayFormat = '0.0'
    end
    object qA: TFloatField
      FieldName = 'A'
      DisplayFormat = '0.0'
    end
    object qMP: TIntegerField
      FieldName = 'MP'
    end
    object qLNFP: TFloatField
      FieldName = 'LNFP'
    end
    object qWEI: TFloatField
      FieldName = 'WEI'
      DisplayFormat = '0.0'
    end
    object qW: TFloatField
      FieldName = 'W'
      DisplayFormat = '0.0'
    end
    object qRWDATE: TDateField
      FieldName = 'RWDATE'
    end
    object qNUMBER: TIntegerField
      FieldName = 'NUMBER'
    end
    object qPOS: TIntegerField
      FieldName = 'POS'
    end
    object qCERT: TIntegerField
      FieldName = 'CERT'
    end
    object qCOALRANK: TIntegerField
      FieldName = 'COALRANK'
    end
    object qCOALRANK_L: TStringField
      FieldKind = fkLookup
      FieldName = 'COALRANK_L'
      LookupDataSet = qcoalranks
      LookupKeyFields = 'ID'
      LookupResultField = 'NAME'
      KeyFields = 'COALRANK'
      Size = 8
      Lookup = True
    end
  end
  object qcoalranks: TZReadOnlyQuery
    Connection = DM.db
    SQL.Strings = (
      'select * from coalranks where id >0 order by id')
    ParamCheck = True
    Params = <>
    Options = [doCalcDefaults]
    Left = 96
    Top = 160
  end
end
