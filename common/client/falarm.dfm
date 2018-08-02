object AlarmF: TAlarmF
  Left = 295
  Top = 180
  BorderStyle = bsNone
  Caption = 'AlarmF'
  ClientHeight = 282
  ClientWidth = 449
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poDesktopCenter
  OnPaint = FormPaint
  PixelsPerInch = 96
  TextHeight = 13
  object SBClose: TSpeedButton
    Left = 360
    Top = 248
    Width = 81
    Height = 26
    Cursor = crHandPoint
    Caption = #1047#1072#1082#1088#1099#1090#1100
    Flat = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsUnderline]
    ParentFont = False
    OnClick = SBCloseClick
  end
  object LWhat: TLabel
    Left = 24
    Top = 184
    Width = 409
    Height = 25
    Alignment = taCenter
    AutoSize = False
    Caption = #1063#1090#1086
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = 240
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LPar: TLabel
    Left = 24
    Top = 136
    Width = 401
    Height = 25
    Alignment = taCenter
    AutoSize = False
    Caption = #1054#1090#1082#1091#1076#1072
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = 240
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label1: TLabel
    Left = 152
    Top = 24
    Width = 152
    Height = 33
    Caption = #1042#1085#1080#1084#1072#1085#1080#1077'!'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = 240
    Font.Height = -27
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 78
    Top = 64
    Width = 300
    Height = 33
    Caption = #1040#1074#1072#1088#1080#1081#1085#1072#1103' '#1089#1080#1090#1091#1072#1094#1080#1103'!'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = 240
    Font.Height = -27
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object CBStop: TCheckBox
    Left = 16
    Top = 256
    Width = 153
    Height = 17
    Caption = #1041#1086#1083#1100#1096#1077' '#1085#1077' '#1087#1086#1082#1072#1079#1099#1074#1072#1090#1100
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsUnderline]
    ParentFont = False
    TabOrder = 0
  end
  object Timer: TTimer
    OnTimer = TimerTimer
    Left = 8
    Top = 8
  end
end
