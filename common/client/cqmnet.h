//---------------------------------------------------------------------------
#ifndef cqmnetH
#define cqmnetH

//---------------------------------------------------------------------------
//������ � cqmnet ��������
bool CqmNetConnected(void);
int CqmNetConnect(void); //1 - �������, 0 - ������
void CqmNetDisconnect(void);
inline int CqmNetCheckConnection(void); //(1 - �������)
int CqmNetQuery(AnsiString q, AnsiString &a);//1 - �������, 0-��� ������



//---------------------------------------------------------------------------
#endif
