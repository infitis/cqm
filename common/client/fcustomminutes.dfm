object MinutesF: TMinutesF
  Left = 567
  Top = 142
  Width = 575
  Height = 462
  Caption = #1052#1080#1085#1091#1090#1085#1099#1077' '#1079#1085#1072#1095#1077#1085#1080#1103' '#1079#1086#1083#1100#1085#1086#1089#1090#1080
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
    C200AAAAAA00B2B2B200CACACA00BEBEBE00D6D6D6000000000000000000CC33
    3336666AA1A11119990000000000CCC333AAA1A111199990000000000000CCCC
    355555555555555555555550000088CCC5555555555555555555555000008CCC
    C355556A55A15519559055000000888CCC55556655AA5511550055000000288C
    CC5536556A55A1551955550900008888CC5533556655AA559955559900002288
    88835536556A55A955551999900028888CCC5536556A55115555919990002228
    88C8C3553655615555A1119990902228888CCC553655AA55551111119990B222
    28888CC355365555AAAA1119999922228888CCCC55665555AAAA1A111999BB22
    828888CC3553655666AAA1A19199BB2B2288888CC553355A66AAAA111199BBB2
    222288C8355365566666AAAA1119BBBB22288888C553655A666A6AA111197BB2
    B222288C55C355553666AAAAA1117B7BB222288C553C5555A66666AAA11177BB
    B2B228558C55C35555666A6AA1A17777BBB222558855CC555566666AAA11477B
    BBB255828888CCCC365566A6AAAA7777BBB255228888CCCC3C556666AAAA4477
    7B552B22828888CCC3365566A6AA447777552B2B2288888CCCC355666AAA4447
    7B55BBB222288C8CCC335536666A444777552B22228888CCCC335566666AD444
    7555555555555555555555536666D44445555555555555555555555336364D44
    44777BBBB22228888CCCC3333666D4D44447777BBBB22228888CCCC333360000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000}
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  PixelsPerInch = 96
  TextHeight = 13
  object Panel: TPanel
    Left = 0
    Top = 0
    Width = 567
    Height = 36
    Align = alTop
    TabOrder = 0
    object L: TLabel
      Left = 8
      Top = 10
      Width = 85
      Height = 13
      Caption = #1058#1086#1095#1082#1072' '#1082#1086#1085#1090#1088#1086#1083#1103':'
    end
    object CB: TComboBox
      Left = 96
      Top = 7
      Width = 145
      Height = 21
      ItemHeight = 13
      TabOrder = 0
      OnChange = CBChange
    end
  end
  object G: TDBGrid
    Left = 0
    Top = 36
    Width = 567
    Height = 380
    Align = alClient
    DataSource = DS
    PopupMenu = PopupMenu
    TabOrder = 1
    TitleFont.Charset = RUSSIAN_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'MOMENT'
        Title.Caption = #1044#1072#1090#1072' '#1042#1088#1077#1084#1103
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'P'
        Title.Caption = #1042#1077#1089', '#1090
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
        Title.Caption = #1047#1086#1083#1100#1085#1086#1089#1090#1100', %'
        Title.Font.Charset = RUSSIAN_CHARSET
        Title.Font.Color = clNavy
        Title.Font.Height = -11
        Title.Font.Name = 'Tahoma'
        Title.Font.Style = []
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'DIAG'
        Title.Caption = #1044#1080#1072#1075#1085#1086#1089#1090#1080#1082#1072
        Visible = True
      end>
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 416
    Width = 567
    Height = 19
    Panels = <>
    SimplePanel = True
  end
  object DS: TDataSource
    DataSet = q
    Left = 24
    Top = 88
  end
  object PopupMenu: TPopupMenu
    Left = 88
    Top = 88
    object N1hour: TMenuItem
      Caption = '1 '#1095#1072#1089
      Checked = True
      RadioItem = True
      OnClick = N1hourClick
    end
    object N6hours: TMenuItem
      Caption = '6 '#1095#1072#1089#1086#1074
      RadioItem = True
      OnClick = N6hoursClick
    end
    object N1day: TMenuItem
      Caption = '1 '#1089#1091#1090#1082#1080
      RadioItem = True
      OnClick = N1dayClick
    end
    object N3day: TMenuItem
      Caption = '3 '#1089#1091#1090#1086#1082
      RadioItem = True
      OnClick = N3dayClick
    end
  end
  object q: TZReadOnlyQuery
    Connection = DM.db
    AfterScroll = qAfterScroll
    SQL.Strings = (
      'select * from points')
    ParamCheck = False
    Params = <>
    Options = [doCalcDefaults]
    Left = 56
    Top = 88
    object qMOMENT: TDateTimeField
      FieldName = 'MOMENT'
    end
    object qP: TFloatField
      FieldName = 'P'
      DisplayFormat = '0.00'
    end
    object qA: TFloatField
      FieldName = 'A'
      DisplayFormat = '0.0'
    end
    object qDIAG: TIntegerField
      FieldName = 'DIAG'
    end
  end
end
