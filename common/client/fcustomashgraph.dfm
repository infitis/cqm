object CustomAshGraphF: TCustomAshGraphF
  Left = 538
  Top = 184
  Width = 277
  Height = 235
  Caption = #1054#1073#1086#1073#1097#1105#1085#1085#1099#1081' '#1075#1088#1072#1092#1080#1082' '#1079#1086#1083#1100#1085#1086#1089#1090#1080
  Color = clBtnFace
  Constraints.MinHeight = 200
  Constraints.MinWidth = 200
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
    3336666AAA119009999000000000CCCC3336666AAAA15550999000000000CCCC
    333336666AA055599999900000008CCCCC3336666AA55555019990000000C8CC
    C33333666A15555599990900000088C8CCC33366661555555019990900008888
    CC3C33336A5555555991199000008888C8CC3333665555555509999990002828
    8CCCC33361555A55555119990900288888CCC33335555AA55550191990002228
    88CCCCC3655556A55555119999902228888CCCC3655566A6555599990009B222
    28888CC6555566661555555555552B228888CCCC55556666655555555555B222
    222888C6555336366A55555555552222288888C55553336666AAAA1A11995552
    22228835555C33336666AAA111195555822888C555333336666AAAA1A1195555
    22282C5555CC333336666AAA1111755558222C5555CCC33336666AAAAA117555
    55B28555588CCCC33336666AA1A17755558225555CCCCC33336666A6AA1177B5
    5552C5558888CCCC3333666AAAAA4775555855558888CCCC333366666AAA477B
    55555555828888CCCC333366A6AA4447555555522288888CCC33336666AA4474
    B555555222288C8CC3C336366A6A4447775555522228288C8CC3C336366AD444
    475555BB22228888CCCC33336666D444477555BBBB22228888CCCC3333664D44
    44777BBBB22228888CCCC3333666D4D44447777BBBB22228888CCCC333360000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    0000000000000000000000000000000000000000000000000000000000000000
    000000000000000000000000000000000000000000000000000000000000}
  OldCreateOrder = False
  Position = poDefault
  Scaled = False
  Visible = True
  WindowState = wsMinimized
  PixelsPerInch = 96
  TextHeight = 13
  object DBChart: TDBChart
    Left = 0
    Top = 35
    Width = 269
    Height = 173
    AllowPanning = pmNone
    AllowZoom = False
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    Foot.Visible = False
    Gradient.Direction = gdBottomTop
    Gradient.EndColor = 16448250
    Gradient.StartColor = clSilver
    Gradient.Visible = True
    MarginBottom = 0
    MarginLeft = 0
    MarginRight = 2
    MarginTop = 2
    PrintProportional = False
    Title.Alignment = taLeftJustify
    Title.Font.Charset = RUSSIAN_CHARSET
    Title.Font.Color = clNavy
    Title.Font.Height = -11
    Title.Font.Name = 'Tahoma'
    Title.Font.Style = []
    Title.Text.Strings = (
      '')
    Title.Visible = False
    BottomAxis.Automatic = False
    BottomAxis.AutomaticMaximum = False
    BottomAxis.AutomaticMinimum = False
    BottomAxis.DateTimeFormat = 'hh:nn'
    LeftAxis.Automatic = False
    LeftAxis.AutomaticMaximum = False
    LeftAxis.AutomaticMinimum = False
    LeftAxis.Grid.Color = 9408399
    LeftAxis.Maximum = 60
    LeftAxis.Minimum = 5
    LeftAxis.MinorTickCount = 1
    LeftAxis.TickLength = 2
    LeftAxis.Ticks.Color = clBlack
    LeftAxis.Title.Caption = #1047#1086#1083#1100#1085#1086#1089#1090#1100', %'
    LeftAxis.Title.Font.Charset = RUSSIAN_CHARSET
    LeftAxis.Title.Font.Color = clNavy
    LeftAxis.Title.Font.Height = -11
    LeftAxis.Title.Font.Name = 'Tahoma'
    LeftAxis.Title.Font.Style = []
    Legend.Visible = False
    View3D = False
    Align = alClient
    BevelInner = bvRaised
    BevelOuter = bvNone
    Color = clWhite
    PopupMenu = PopupMenu
    TabOrder = 0
    object Series1: TPointSeries
      Marks.ArrowLength = 0
      Marks.Frame.Visible = False
      Marks.Visible = False
      DataSource = q
      SeriesColor = clRed
      Title = #1047#1086#1083#1100#1085#1086#1089#1090#1100
      Pointer.Brush.Color = 1052768
      Pointer.HorizSize = 3
      Pointer.InflateMargins = True
      Pointer.Pen.Color = clMaroon
      Pointer.Pen.Visible = False
      Pointer.Style = psCircle
      Pointer.VertSize = 3
      Pointer.Visible = True
      XValues.DateTime = True
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      XValues.ValueSource = 'moment'
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
      YValues.ValueSource = 'ad'
    end
    object Series2: TPointSeries
      Marks.ArrowLength = 0
      Marks.Visible = False
      DataSource = qvag
      SeriesColor = clGreen
      Title = #1042#1072#1075#1086#1085#1099
      Pointer.Brush.Color = 15135743
      Pointer.InflateMargins = True
      Pointer.Pen.Color = 1132486
      Pointer.Style = psDownTriangle
      Pointer.Visible = True
      XValues.DateTime = True
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      XValues.ValueSource = 'moment'
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
      YValues.ValueSource = 'ad'
    end
  end
  object P: TPanel
    Left = 0
    Top = 0
    Width = 269
    Height = 35
    Align = alTop
    Color = 13421772
    TabOrder = 1
    object LPerc: TLabel
      Left = 120
      Top = 3
      Width = 11
      Height = 13
      Caption = '%'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clNavy
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object LA: TLabel
      Left = 88
      Top = 1
      Width = 28
      Height = 16
      Caption = '23.2'
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clNavy
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelAName: TLabel
      Left = 8
      Top = 3
      Width = 57
      Height = 13
      Caption = #1047#1086#1083#1100#1085#1086#1089#1090#1100':'
    end
    object LabelDName: TLabel
      Left = 8
      Top = 17
      Width = 70
      Height = 13
      Caption = #1044#1080#1072#1075#1085#1086#1089#1090#1080#1082#1072':'
    end
    object LD: TLabel
      Left = 88
      Top = 17
      Width = 41
      Height = 13
      Caption = #1087#1088#1086#1089#1090#1086#1081
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clMaroon
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
  end
  object PopupMenu: TPopupMenu
    Left = 152
    Top = 56
    object N1hour: TMenuItem
      Caption = '1 '#1095#1072#1089
      RadioItem = True
      OnClick = N1hourClick
    end
    object N6hours: TMenuItem
      Caption = '6 '#1095#1072#1089#1086#1074
      Checked = True
      RadioItem = True
      OnClick = N6hoursClick
    end
    object N1Day: TMenuItem
      Caption = '1 '#1089#1091#1090#1082#1080
      RadioItem = True
      OnClick = N1DayClick
    end
    object N1: TMenuItem
      Caption = '-'
      GroupIndex = 2
    end
    object NGeneral: TMenuItem
      Caption = #1054#1088#1080#1075#1080#1085#1072#1083
      GroupIndex = 2
      RadioItem = True
      OnClick = NGeneralClick
    end
    object NSliding: TMenuItem
      Caption = #1057#1082#1086#1083#1100#1079#1103#1097#1080#1081' (3)'
      Checked = True
      GroupIndex = 2
      RadioItem = True
      OnClick = NSlidingClick
    end
    object NSliding6: TMenuItem
      Caption = #1057#1082#1086#1083#1100#1079#1103#1097#1080#1081' (6)'
      GroupIndex = 2
      RadioItem = True
      OnClick = NSliding6Click
    end
    object N2: TMenuItem
      Caption = '-'
      GroupIndex = 2
    end
    object NPrint: TMenuItem
      Caption = #1055#1077#1095#1072#1090#1100
      GroupIndex = 2
      OnClick = NPrintClick
    end
  end
  object q: TZReadOnlyQuery
    Connection = DM.db
    ParamCheck = False
    Params = <>
    Options = [doCalcDefaults]
    Left = 184
    Top = 56
  end
  object qvag: TZReadOnlyQuery
    Connection = DM.db
    ParamCheck = False
    Params = <>
    Options = [doCalcDefaults]
    Left = 216
    Top = 56
  end
end
