object SelectPointDateF: TSelectPointDateF
  Left = 336
  Top = 135
  BorderStyle = bsDialog
  Caption = #1042#1099#1073#1086#1088' '#1090#1086#1095#1082#1080' '#1082#1086#1085#1090#1088#1086#1083#1103' '#1080' '#1074#1088#1077#1084#1077#1085#1080
  ClientHeight = 225
  ClientWidth = 220
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object L1: TLabel
    Left = 16
    Top = 8
    Width = 54
    Height = 13
    Caption = #1042#1099#1073#1077#1088#1080#1090#1077':'
  end
  object CB: TComboBox
    Left = 16
    Top = 32
    Width = 145
    Height = 21
    ItemHeight = 13
    TabOrder = 0
  end
  object GBDate: TGroupBox
    Left = 8
    Top = 64
    Width = 177
    Height = 57
    Caption = #1042#1099#1073#1077#1088#1080#1090#1077' '#1076#1072#1090#1091':'
    TabOrder = 1
    object DateP: TDateTimePicker
      Left = 16
      Top = 24
      Width = 137
      Height = 21
      CalAlignment = dtaLeft
      Date = 37977.6403411921
      Time = 37977.6403411921
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 0
    end
  end
  object GBDateTime: TGroupBox
    Left = 8
    Top = 64
    Width = 201
    Height = 113
    Caption = #1042#1099#1073#1077#1088#1080#1090#1077' '#1080#1085#1090#1077#1088#1074#1072#1083' '#1074#1088#1077#1084#1077#1085#1080':'
    TabOrder = 2
    object L2: TLabel
      Left = 16
      Top = 16
      Width = 12
      Height = 13
      Caption = #1086#1090
    end
    object L3: TLabel
      Left = 16
      Top = 64
      Width = 13
      Height = 13
      Caption = #1076#1086
    end
    object DateP1: TDateTimePicker
      Left = 16
      Top = 32
      Width = 81
      Height = 21
      CalAlignment = dtaLeft
      Date = 37977.6437874653
      Time = 37977.6437874653
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 0
    end
    object TimeP1: TDateTimePicker
      Left = 96
      Top = 32
      Width = 73
      Height = 21
      CalAlignment = dtaLeft
      Date = 37977.6450246528
      Time = 37977.6450246528
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkTime
      ParseInput = False
      TabOrder = 1
    end
    object TimeP2: TDateTimePicker
      Left = 96
      Top = 80
      Width = 73
      Height = 21
      CalAlignment = dtaLeft
      Date = 37977.6450246528
      Time = 37977.6450246528
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkTime
      ParseInput = False
      TabOrder = 3
    end
    object DateP2: TDateTimePicker
      Left = 16
      Top = 80
      Width = 81
      Height = 21
      CalAlignment = dtaLeft
      Date = 37977.6437874653
      Time = 37977.6437874653
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 2
    end
  end
  object BOk: TButton
    Left = 48
    Top = 192
    Width = 75
    Height = 25
    Caption = #1043#1086#1090#1086#1074#1086
    Default = True
    ModalResult = 1
    TabOrder = 3
  end
  object BCancel: TButton
    Left = 128
    Top = 192
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 4
  end
end
