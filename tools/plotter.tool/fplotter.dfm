object PlotF: TPlotF
  Left = 309
  Top = 183
  Width = 863
  Height = 591
  Caption = #1055#1083#1086#1090#1090#1077#1088
  Color = clBtnFace
  Font.Charset = RUSSIAN_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Courier New'
  Font.Style = []
  Menu = MainMenu
  OldCreateOrder = False
  WindowState = wsMaximized
  PixelsPerInch = 96
  TextHeight = 15
  object Splitter: TSplitter
    Left = 0
    Top = 389
    Width = 855
    Height = 3
    Cursor = crVSplit
    Align = alBottom
  end
  object C: TChart
    Left = 0
    Top = 0
    Width = 855
    Height = 389
    AnimatedZoom = True
    AnimatedZoomSteps = 1
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    MarginBottom = 0
    MarginLeft = 1
    MarginRight = 1
    MarginTop = 2
    Title.Color = clWhite
    Title.Text.Strings = (
      '')
    Title.Visible = False
    BottomAxis.DateTimeFormat = 'dd.mm hh:nn:ss'
    BottomAxis.Title.Font.Charset = DEFAULT_CHARSET
    BottomAxis.Title.Font.Color = clBlack
    BottomAxis.Title.Font.Height = -8
    BottomAxis.Title.Font.Name = 'Arial'
    BottomAxis.Title.Font.Style = []
    LeftAxis.StartPosition = 1
    LeftAxis.TickLength = 2
    Legend.Visible = False
    View3D = False
    Align = alClient
    BorderStyle = bsSingle
    Color = clWhite
    TabOrder = 0
    AutoSize = True
    object Series1: TPointSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clRed
      ShowInLegend = False
      Title = 's1'
      Pointer.Brush.Color = clBlack
      Pointer.HorizSize = 3
      Pointer.InflateMargins = False
      Pointer.Pen.Visible = False
      Pointer.Style = psCircle
      Pointer.VertSize = 3
      Pointer.Visible = True
      XValues.DateTime = True
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
    object Series2: TPointSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clRed
      ShowInLegend = False
      Title = 's2'
      Pointer.Brush.Color = clWhite
      Pointer.HorizSize = 3
      Pointer.InflateMargins = False
      Pointer.Style = psRectangle
      Pointer.VertSize = 3
      Pointer.Visible = True
      XValues.DateTime = True
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
    object Series3: TPointSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clRed
      ShowInLegend = False
      Title = 's3'
      Pointer.Brush.Color = clSilver
      Pointer.InflateMargins = False
      Pointer.Style = psDownTriangle
      Pointer.Visible = True
      XValues.DateTime = True
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
    object Series4: TPointSeries
      Marks.ArrowLength = 8
      Marks.Visible = False
      SeriesColor = clRed
      ShowInLegend = False
      Title = 's4'
      Pointer.Brush.Color = clSilver
      Pointer.HorizSize = 3
      Pointer.InflateMargins = False
      Pointer.Style = psRectangle
      Pointer.VertSize = 3
      Pointer.Visible = True
      XValues.DateTime = True
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
  object G: TStringGrid
    Left = 0
    Top = 392
    Width = 855
    Height = 153
    Align = alBottom
    ColCount = 1
    DefaultRowHeight = 16
    FixedCols = 0
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing]
    TabOrder = 1
    OnDblClick = GDblClick
    OnSelectCell = GSelectCell
  end
  object OD: TOpenDialog
    DefaultExt = 'csv'
    Filter = 'csv files|*.csv; *.txt|all files|*.*'
    Title = #1054#1090#1082#1088#1099#1090#1100' '#1092#1072#1081#1083'...'
    Left = 72
    Top = 40
  end
  object MainMenu: TMainMenu
    Left = 32
    Top = 40
    object NFile: TMenuItem
      Caption = #1060#1072#1081#1083
      object NOpen: TMenuItem
        Caption = #1054#1090#1082#1088#1099#1090#1100'...'
        ShortCut = 16463
        OnClick = BLoadClick
      end
      object NPrint: TMenuItem
        Caption = #1055#1077#1095#1072#1090#1100'...'
        ShortCut = 16464
        OnClick = BPrintClick
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object NExit: TMenuItem
        Caption = #1047#1072#1074#1077#1088#1096#1080#1090#1100' '#1088#1072#1073#1086#1090#1091
        OnClick = NExitClick
      end
    end
    object NPl: TMenuItem
      Caption = #1055#1083#1086#1090#1090#1077#1088
      object NBuildColumn: TMenuItem
        Caption = #1055#1086#1089#1090#1088#1086#1080#1090#1100' '#1074#1099#1073#1088#1072#1085#1085#1099#1081' '#1089#1090#1086#1083#1073#1077#1094
        ShortCut = 120
        OnClick = BMakeClick
      end
      object NBuildScale: TMenuItem
        Caption = #1055#1086#1089#1090#1088#1086#1080#1090#1100' '#1089' '#1084#1072#1089#1096#1090#1072#1073#1085#1099#1084' '#1082#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090#1086#1084'...'
        ShortCut = 121
        OnClick = NBuildScaleClick
      end
      object NBuildSlice: TMenuItem
        Caption = #1055#1086#1089#1090#1088#1086#1080#1090#1100' '#1089#1075#1083#1072#1078#1077#1085#1086' (x5)'
        ShortCut = 122
        OnClick = NBuildSliceClick
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object NDelLastSer: TMenuItem
        Caption = #1059#1076#1072#1083#1080#1090#1100' '#1087#1086#1089#1083#1077#1076#1085#1102#1102' '#1089#1077#1088#1080#1102
        ShortCut = 16452
        OnClick = NDelLastSerClick
      end
      object NDelAllSer: TMenuItem
        Caption = #1059#1076#1072#1083#1080#1090#1100' '#1074#1089#1077' '#1089#1077#1088#1080#1080
        ShortCut = 49220
        OnClick = BResetClick
      end
    end
    object NHelp: TMenuItem
      Caption = #1057#1087#1088#1072#1074#1082#1072
      object NAbout: TMenuItem
        Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077'...'
        OnClick = NAboutClick
      end
    end
  end
end
