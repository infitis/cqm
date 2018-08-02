object ClockF: TClockF
  Left = 488
  Top = 6
  BorderStyle = bsNone
  Caption = #1063#1072#1089#1099
  ClientHeight = 22
  ClientWidth = 198
  Color = clBlack
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object L: TLabel
    Left = 1
    Top = 1
    Width = 196
    Height = 20
    Alignment = taCenter
    AutoSize = False
    Caption = '1000-00-00 00:00:00'
    Color = 6137588
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    Layout = tlCenter
    OnMouseDown = LMouseDown
    OnMouseMove = LMouseMove
    OnMouseUp = LMouseUp
  end
  object Timer: TTimer
    OnTimer = TimerTimer
    Left = 104
  end
end
