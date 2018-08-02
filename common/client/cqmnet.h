//---------------------------------------------------------------------------
#ifndef cqmnetH
#define cqmnetH

//---------------------------------------------------------------------------
//Работа с cqmnet сервером
bool CqmNetConnected(void);
int CqmNetConnect(void); //1 - успешно, 0 - ошибка
void CqmNetDisconnect(void);
inline int CqmNetCheckConnection(void); //(1 - успешно)
int CqmNetQuery(AnsiString q, AnsiString &a);//1 - успешно, 0-код ошибки



//---------------------------------------------------------------------------
#endif
