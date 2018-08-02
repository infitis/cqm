object EnterDataF: TEnterDataF
  Left = 284
  Top = 260
  BorderStyle = bsDialog
  Caption = #1042#1074#1086#1076' '#1076#1072#1085#1085#1099#1093
  ClientHeight = 94
  ClientWidth = 415
  Color = 13421772
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object L: TLabel
    Left = 8
    Top = 8
    Width = 50
    Height = 13
    Caption = #1042#1074#1077#1076#1080#1090#1077' :'
  end
  object BOk: TButton
    Left = 256
    Top = 64
    Width = 75
    Height = 25
    Caption = 'Ok'
    Default = True
    ModalResult = 1
    TabOrder = 1
  end
  object BCancel: TButton
    Left = 336
    Top = 64
    Width = 75
    Height = 25
    Cancel = True
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 2
  end
  object E: TComboBox
    Left = 8
    Top = 32
    Width = 401
    Height = 23
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = 64
    Font.Height = -12
    Font.Name = 'Courier New'
    Font.Style = []
    ItemHeight = 15
    ParentFont = False
    TabOrder = 0
  end
end
