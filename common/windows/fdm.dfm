object DM: TDM
  OldCreateOrder = False
  Left = 384
  Top = 126
  Height = 480
  Width = 696
  object db: TZConnection
    Protocol = 'firebird-1.5'
    HostName = 'localhost'
    Port = 3050
    Database = 'cqm'
    User = 'server'
    Password = 'srv1'
    AutoCommit = False
    ReadOnly = False
    TransactIsolationLevel = tiReadCommitted
    Connected = False
    SQLHourGlass = False
    Left = 32
    Top = 24
  end
  object q: TZReadOnlyQuery
    Connection = db
    SQL.Strings = (
      'select * from points')
    ParamCheck = False
    Params = <>
    Options = [doCalcDefaults]
    Left = 88
    Top = 24
  end
  object SqlMonitor: TZSQLMonitor
    AutoSave = True
    FileName = '..\log\sql\sql.log'
    MaxTraceCount = 500
    Left = 160
    Top = 24
  end
end
