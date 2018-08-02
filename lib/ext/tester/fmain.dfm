object MainF: TMainF
  Left = 236
  Top = 168
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1058#1077#1089#1090#1077#1088' '#1076#1083#1103' cqm-extensions'
  ClientHeight = 453
  ClientWidth = 681
  Color = 11579568
  Ctl3D = False
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Lucida Sans Unicode'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 16
  object BOpenModule: TSpeedButton
    Left = 416
    Top = 16
    Width = 25
    Height = 22
    Cursor = crHandPoint
    Caption = '...'
    Flat = True
    OnClick = BOpenModuleClick
  end
  object BLoad: TSpeedButton
    Left = 448
    Top = 16
    Width = 65
    Height = 22
    Cursor = crHandPoint
    Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100
    Flat = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsUnderline]
    ParentFont = False
    OnClick = BLoadClick
  end
  object BFree: TSpeedButton
    Left = 520
    Top = 16
    Width = 65
    Height = 22
    Cursor = crHandPoint
    Caption = #1042#1099#1075#1088#1091#1079#1080#1090#1100
    Enabled = False
    Flat = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsUnderline]
    ParentFont = False
    OnClick = BFreeClick
  end
  object BStart: TSpeedButton
    Left = 88
    Top = 48
    Width = 65
    Height = 22
    Cursor = crHandPoint
    Caption = #1057#1090#1072#1088#1090
    Enabled = False
    Flat = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsUnderline]
    ParentFont = False
    OnClick = BStartClick
  end
  object BStop: TSpeedButton
    Left = 160
    Top = 48
    Width = 65
    Height = 22
    Cursor = crHandPoint
    Caption = #1057#1090#1086#1087
    Enabled = False
    Flat = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsUnderline]
    ParentFont = False
    OnClick = BStopClick
  end
  object BProc: TSpeedButton
    Left = 416
    Top = 80
    Width = 73
    Height = 22
    Cursor = crHandPoint
    Caption = #1042#1099#1087#1086#1083#1085#1080#1090#1100
    Enabled = False
    Flat = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clNavy
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsUnderline]
    ParentFont = False
    OnClick = BProcClick
  end
  object EModul: TLabeledEdit
    Left = 88
    Top = 16
    Width = 321
    Height = 22
    EditLabel.Width = 44
    EditLabel.Height = 16
    EditLabel.Caption = #1052#1086#1076#1091#1083#1100
    LabelPosition = lpLeft
    LabelSpacing = 10
    TabOrder = 0
  end
  object M: TMemo
    Left = 8
    Top = 120
    Width = 665
    Height = 321
    ScrollBars = ssVertical
    TabOrder = 1
  end
  object EProc: TLabeledEdit
    Left = 88
    Top = 80
    Width = 321
    Height = 22
    EditLabel.Width = 68
    EditLabel.Height = 16
    EditLabel.Caption = #1055#1088#1086#1094#1077#1076#1091#1088#1072
    LabelPosition = lpLeft
    LabelSpacing = 10
    TabOrder = 2
  end
  object OpenDialog: TOpenDialog
    Filter = 'dll-'#1084#1086#1076#1091#1083#1100'|*.dll|'#1074#1089#1077' '#1092#1072#1081#1083#1099'|*.*'
    Options = [ofHideReadOnly, ofFileMustExist, ofEnableSizing]
    Left = 616
    Top = 16
  end
end
