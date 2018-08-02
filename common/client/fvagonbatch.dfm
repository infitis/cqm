object VagonBatchF: TVagonBatchF
  Left = 415
  Top = 210
  BorderStyle = bsDialog
  Caption = #1055#1072#1088#1090#1080#1103' '#1074#1072#1075#1086#1085#1086#1074' '#8470' 165'
  ClientHeight = 286
  ClientWidth = 322
  Color = 13421772
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object LVBN: TLabel
    Left = 64
    Top = 20
    Width = 53
    Height = 13
    Caption = #1055#1072#1088#1090#1080#1103' '#8470
  end
  object LRWD: TLabel
    Left = 60
    Top = 44
    Width = 51
    Height = 13
    Caption = #1078'/'#1076' '#1089#1091#1090#1082#1080
  end
  object Label1: TLabel
    Left = 71
    Top = 68
    Width = 42
    Height = 13
    Caption = #1055#1086#1079#1080#1094#1080#1103
  end
  object LCR: TLabel
    Left = 81
    Top = 140
    Width = 32
    Height = 13
    Caption = #1052#1072#1088#1082#1072
  end
  object LP: TLabel
    Left = 96
    Top = 188
    Width = 17
    Height = 13
    Caption = #1042#1077#1089
  end
  object LH: TLabel
    Left = 58
    Top = 212
    Width = 55
    Height = 13
    Caption = #1042#1083#1072#1078#1085#1086#1089#1090#1100
  end
  object LVN: TLabel
    Left = 8
    Top = 116
    Width = 104
    Height = 13
    Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1074#1072#1075#1086#1085#1086#1074
  end
  object SBnoPos: TSpeedButton
    Left = 200
    Top = 88
    Width = 105
    Height = 17
    Cursor = crHandPoint
    Caption = #1085#1077#1090' '#1085#1091#1078#1085#1086#1081' '#1087#1086#1079#1080#1094#1080#1080'?'
    Flat = True
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clGray
    Font.Height = -9
    Font.Name = 'Tahoma'
    Font.Style = [fsUnderline]
    ParentFont = False
    OnClick = SBnoPosClick
  end
  object SBnoRank: TSpeedButton
    Left = 200
    Top = 160
    Width = 97
    Height = 17
    Cursor = crHandPoint
    Caption = #1085#1077#1090' '#1085#1091#1078#1085#1086#1081' '#1084#1072#1088#1082#1080'?'
    Flat = True
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clGray
    Font.Height = -9
    Font.Name = 'Tahoma'
    Font.Style = [fsUnderline]
    ParentFont = False
    OnClick = SBnoRankClick
  end
  object L1: TLabel
    Left = 208
    Top = 188
    Width = 6
    Height = 13
    Caption = #1090
  end
  object L2: TLabel
    Left = 208
    Top = 212
    Width = 11
    Height = 13
    Caption = '%'
  end
  object SpeedButton1: TSpeedButton
    Left = 224
    Top = 208
    Width = 73
    Height = 17
    Cursor = crHandPoint
    Caption = #1048#1079' '#1076#1086#1075#1086#1074#1086#1088#1072
    Flat = True
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clGray
    Font.Height = -9
    Font.Name = 'Tahoma'
    Font.Style = [fsUnderline]
    ParentFont = False
    OnClick = SpeedButton1Click
  end
  object BOk: TButton
    Left = 128
    Top = 248
    Width = 75
    Height = 25
    Caption = #1043#1086#1090#1086#1074#1086
    Default = True
    TabOrder = 7
    OnClick = BOkClick
  end
  object BCancel: TButton
    Left = 208
    Top = 248
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    TabOrder = 8
    OnClick = BCancelClick
  end
  object EBatchNum: TEdit
    Left = 120
    Top = 16
    Width = 81
    Height = 21
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = 20480
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
  end
  object CBPos: TComboBox
    Left = 120
    Top = 64
    Width = 185
    Height = 21
    Style = csDropDownList
    DropDownCount = 12
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = 20480
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ItemHeight = 13
    ParentFont = False
    TabOrder = 2
  end
  object CBRank: TComboBox
    Left = 120
    Top = 136
    Width = 97
    Height = 21
    Style = csDropDownList
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = 20480
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ItemHeight = 13
    ParentFont = False
    TabOrder = 4
  end
  object EP: TEdit
    Left = 120
    Top = 184
    Width = 81
    Height = 21
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = 20480
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 5
  end
  object EH: TEdit
    Left = 120
    Top = 208
    Width = 81
    Height = 21
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = 20480
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 6
  end
  object EVN: TEdit
    Left = 120
    Top = 112
    Width = 81
    Height = 21
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = 20480
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
  end
  object ERWD: TDateTimePicker
    Left = 120
    Top = 40
    Width = 81
    Height = 21
    CalAlignment = dtaLeft
    CalColors.TextColor = 20480
    Date = 38155.7365202083
    Time = 38155.7365202083
    DateFormat = dfShort
    DateMode = dmComboBox
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = 20480
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    Kind = dtkDate
    MaxDate = 41275
    MinDate = 37622
    ParseInput = False
    ParentFont = False
    TabOrder = 1
  end
end
