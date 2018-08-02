//---------------------------------------------------------------------------
#ifndef stuffH
#define stuffH

//---------------------------------------------------------------------------
int Start();
int Stop();

void LoadDataFromIni();
void InitForms();
void ShowStartPosition();
void CqmObjActivated(int id);
void CqmObjDeActivated(int id);
void RefreshActions(void);
void ShowWorkPosition(void);
void ShowMinutes(void);
void Action_Connect();
void Action_Disconnect();
void Action_Update();
void Action_RestoreDB();
void Action_BackupDB();

//---------------------------------------------------------------------------
#endif
