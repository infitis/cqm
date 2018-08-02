object DateTimeSelect: TDateTimeSelect
  Left = 468
  Top = 317
  BorderStyle = bsDialog
  Caption = 'DateTimeSelectF'
  ClientHeight = 177
  ClientWidth = 218
  Color = 13421772
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object L1: TLabel
    Left = 16
    Top = 16
    Width = 7
    Height = 13
    Caption = 'C'
  end
  object L2: TLabel
    Left = 16
    Top = 72
    Width = 15
    Height = 13
    Caption = 'по:'
  end
  object DateTimePicker1: TDateTimePicker
    Left = 16
    Top = 32
    Width = 81
    Height = 21
    CalAlignment = dtaLeft
    Date = 37944.6992315278
    Time = 37944.6992315278
    DateFormat = dfShort
    DateMode = dmComboBox
    Kind = dtkDate
    ParseInput = False
    TabOrder = 0
  end
  object DateTimePicker2: TDateTimePicker
    Left = 104
    Top = 32
    Width = 73
    Height = 21
    CalAlignment = dtaLeft
    Date = 37944.6998175579
    Time = 37944.6998175579
    DateFormat = dfShort
    DateMode = dmComboBox
    Kind = dtkTime
    ParseInput = False
    TabOrder = 1
  end
  object DateTimePicker3: TDateTimePicker
    Left = 16
    Top = 88
    Width = 81
    Height = 21
    CalAlignment = dtaLeft
    Date = 37944.6992315278
    Time = 37944.6992315278
    DateFormat = dfShort
    DateMode = dmComboBox
    Kind = dtkDate
    ParseInput = False
    TabOrder = 2
  end
  object DateTimePicker4: TDateTimePicker
    Left = 104
    Top = 88
    Width = 73
    Height = 21
    CalAlignment = dtaLeft
    Date = 37944.6998175579
    Time = 37944.6998175579
    DateFormat = dfShort
    DateMode = dmComboBox
    Kind = dtkTime
    ParseInput = False
    TabOrder = 3
  end
  object BOk: TButton
    Left = 56
    Top = 144
    Width = 75
    Height = 25
    Caption = 'Готово'
    Default = True
    ModalResult = 1
    TabOrder = 4
  end
  object BCancel: TButton
    Left = 136
    Top = 144
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Отмена'
    ModalResult = 2
    TabOrder = 5
  end
end
