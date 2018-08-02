object CustomVagonsViewerF: TCustomVagonsViewerF
  Left = 574
  Top = 162
  Width = 293
  Height = 372
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = #1042#1072#1075#1086#1085#1099
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
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
  object G: TDBGrid
    Left = 0
    Top = 0
    Width = 285
    Height = 326
    Align = alClient
    DataSource = DS
    FixedColor = 13421772
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
    ReadOnly = True
    TabOrder = 0
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'VDATE'
        Title.Caption = #1042#1088#1077#1084#1103
        Width = 47
        Visible = True
      end
      item
        Color = 15921906
        Expanded = False
        FieldName = 'ID'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = 5263440
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        Title.Caption = #8470
        Width = 41
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'P'
        Title.Caption = 'P, '#1090
        Width = 44
        Visible = True
      end
      item
        Color = 15135743
        Expanded = False
        FieldName = 'A'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        Title.Caption = 'A, %'
        Title.Font.Charset = DEFAULT_CHARSET
        Title.Font.Color = clNavy
        Title.Font.Height = -11
        Title.Font.Name = 'MS Sans Serif'
        Title.Font.Style = []
        Width = 30
        Visible = True
      end>
  end
  object Status: TStatusBar
    Left = 0
    Top = 326
    Width = 285
    Height = 19
    Color = 13421772
    Panels = <>
    SimplePanel = True
  end
  object DS: TDataSource
    DataSet = q
    Left = 176
    Top = 40
  end
  object q: TZReadOnlyQuery
    Connection = DM.db
    SQL.Strings = (
      '')
    ParamCheck = False
    Params = <>
    Options = [doCalcDefaults]
    Left = 136
    Top = 40
    object qVDATE: TTimeField
      FieldName = 'VDATE'
      ReadOnly = True
      Required = True
    end
    object qID: TIntegerField
      FieldName = 'ID'
      Required = True
    end
    object qP: TFloatField
      FieldName = 'P'
      DisplayFormat = '0.0'
    end
    object qA: TFloatField
      FieldName = 'A'
      DisplayFormat = '0.0'
    end
  end
end
