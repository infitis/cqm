object MainICF: TMainICF
  Left = 335
  Top = 188
  Width = 468
  Height = 353
  Caption = 'MainICF'
  Color = 15790320
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIForm
  Menu = MainMenu
  OldCreateOrder = False
  WindowState = wsMaximized
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object MainMenu: TMainMenu
    Left = 8
    Top = 8
    object NIC: TMenuItem
      Caption = #1048#1085#1092#1086#1094#1077#1085#1090#1088
      object Ndiv1: TMenuItem
        Caption = '-'
      end
      object NExit: TMenuItem
        Caption = #1047#1072#1074#1077#1088#1096#1077#1085#1080#1077' '#1088#1072#1073#1086#1090#1099
        OnClick = NExitClick
      end
    end
    object Na: TMenuItem
      Caption = #1044#1077#1081#1089#1090#1074#1080#1103
      Enabled = False
      object NaRefrsh: TMenuItem
        Caption = #1054#1073#1085#1086#1074#1080#1090#1100' '#1073#1072#1079#1091' '#1076#1072#1085#1085#1099#1093' '#1086#1073#1098#1077#1082#1090#1072
        OnClick = NaRefrshClick
      end
      object Ndiv5: TMenuItem
        Caption = '-'
      end
      object NaConnect: TMenuItem
        Caption = #1059#1089#1090#1072#1085#1086#1074#1080#1090#1100' '#1089#1086#1077#1076#1080#1085#1077#1085#1080#1077' '#1089' '#1086#1073#1098#1077#1082#1090#1086#1084
        OnClick = NaConnectClick
      end
      object NaDisconnect: TMenuItem
        Caption = #1056#1072#1079#1086#1088#1074#1072#1090#1100' '#1089#1086#1077#1076#1080#1085#1077#1085#1080#1077' '#1089' '#1086#1073#1098#1077#1082#1090#1086#1084
        OnClick = NaDisconnectClick
      end
      object Ndiv6: TMenuItem
        Caption = '-'
      end
      object NaDBRestoreFromFile: TMenuItem
        Caption = #1042#1086#1089#1089#1090#1072#1085#1086#1074#1080#1090#1100' '#1073#1072#1079#1091' '#1076#1072#1085#1085#1099#1093' '#1086#1073#1098#1077#1082#1090#1072' '#1080#1079' '#1092#1072#1081#1083#1072
        OnClick = NaDBRestoreFromFileClick
      end
      object NaDBBackup: TMenuItem
        Caption = #1057#1086#1079#1076#1072#1090#1100' '#1088#1077#1079#1077#1088#1074#1085#1091#1102' '#1082#1086#1087#1080#1102' '#1073#1072#1079#1099' '#1076#1072#1085#1085#1099#1093' '#1086#1073#1098#1077#1082#1090#1072
        OnClick = NaDBBackupClick
      end
    end
    object NWindows: TMenuItem
      Caption = #1054#1082#1085#1072
      object NRefresh: TMenuItem
        Caption = #1054#1073#1085#1086#1074#1080#1090#1100
        ShortCut = 16466
        OnClick = NRefreshClick
      end
      object Ndiv2: TMenuItem
        Caption = '-'
      end
      object NMin: TMenuItem
        Caption = #1052#1080#1085#1091#1090#1085#1099#1077' '#1079#1085#1072#1095#1077#1085#1080#1103
        ShortCut = 114
        OnClick = NMinClick
      end
      object NWorkPositopn: TMenuItem
        Caption = #1056#1072#1073#1086#1095#1077#1077' '#1087#1086#1083#1086#1078#1077#1085#1080#1077
        ShortCut = 115
        OnClick = NWorkPositopnClick
      end
      object Ndiv3: TMenuItem
        Caption = '-'
      end
      object NMsgs: TMenuItem
        Caption = #1046#1091#1088#1085#1072#1083
        ShortCut = 16461
        OnClick = NMsgsClick
      end
    end
    object Nr: TMenuItem
      Caption = #1054#1090#1095#1105#1090#1099
      Enabled = False
      object NrDayPoint: TMenuItem
        Caption = #1057#1091#1090#1086#1095#1085#1099#1081' '#1087#1086' '#1090#1086#1095#1082#1072#1084' '#1082#1086#1085#1090#1088#1086#1083#1103
        OnClick = NrDayPointClick
      end
      object NrDayRoute: TMenuItem
        Caption = #1057#1091#1090#1086#1095#1085#1099#1081' '#1087#1086' '#1084#1072#1088#1096#1088#1091#1090#1072#1084' '#1076#1074#1080#1078#1077#1085#1080#1103' '#1091#1075#1083#1103
        OnClick = NrDayRouteClick
      end
      object NrIntervalRoute: TMenuItem
        Caption = #1057#1091#1090#1086#1095#1085#1099#1081' '#1087#1086' '#1080#1085#1090#1077#1088#1074#1072#1083#1072#1084' '#1088#1072#1073#1086#1090#1099' '#1084#1072#1088#1096#1088#1091#1090#1086#1074
        OnClick = NrIntervalRouteClick
      end
      object NrMonthPoint: TMenuItem
        Caption = #1052#1077#1089#1103#1095#1085#1099#1081' '#1087#1086' '#1090#1086#1095#1082#1072#1084' '#1082#1086#1085#1090#1088#1086#1083#1103
        OnClick = NrMonthPointClick
      end
      object NrMonthRoute: TMenuItem
        Caption = #1052#1077#1089#1103#1095#1085#1099#1081' '#1087#1086' '#1084#1072#1088#1096#1088#1091#1090#1072#1084' '#1076#1074#1080#1078#1077#1085#1080#1103' '#1091#1075#1083#1103
        OnClick = NrMonthRouteClick
      end
      object NrVagon: TMenuItem
        Caption = #1055#1086#1074#1072#1075#1086#1085#1085#1099#1081
        OnClick = NrVagonClick
      end
      object NrPos: TMenuItem
        Caption = #1055#1086' '#1087#1086#1079#1080#1094#1080#1103#1084
        OnClick = NrPosClick
      end
      object Ndiv4: TMenuItem
        Caption = '-'
      end
      object NrMinute: TMenuItem
        Caption = #1055#1086#1084#1080#1085#1091#1090#1085#1099#1081
        OnClick = NrMinuteClick
      end
      object NrGraphPoint: TMenuItem
        Caption = #1043#1088#1072#1092#1080#1082' '#1079#1086#1083#1100#1085#1086#1089#1090#1080' '#1090#1086#1095#1082#1080' '#1082#1086#1085#1090#1088#1086#1083#1103
        OnClick = NrGraphPointClick
      end
      object NrGraphRoute: TMenuItem
        Caption = #1043#1088#1072#1092#1080#1082' '#1079#1086#1083#1100#1085#1086#1089#1090#1080' '#1084#1072#1088#1096#1088#1091#1090#1072
        OnClick = NrGraphRouteClick
      end
    end
    object NHelp: TMenuItem
      Caption = #1057#1087#1088#1072#1074#1082#1072
      object NAbout: TMenuItem
        Caption = #1054' '#1055#1088#1086#1075#1088#1072#1084#1084#1077'...'
        OnClick = NAboutClick
      end
    end
  end
end
