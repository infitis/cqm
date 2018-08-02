object AboutF: TAboutF
  Left = 220
  Top = 163
  BorderStyle = bsNone
  Caption = #1054' '#1055#1088#1086#1075#1088#1072#1084#1084#1077
  ClientHeight = 300
  ClientWidth = 522
  Color = 6316128
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object RE: TRichEdit
    Left = 0
    Top = 0
    Width = 522
    Height = 300
    Align = alClient
    Color = clBlack
    ReadOnly = True
    TabOrder = 0
    OnMouseUp = REMouseUp
  end
  object T: TTimer
    Interval = 40
    OnTimer = TTimer
    Left = 8
    Top = 8
  end
end
