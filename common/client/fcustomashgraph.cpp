//---------------------------------------------------------------------------
#include <vcl.h>
#include <teeprevi.hpp>
#include <inifiles.hpp>
#include "fcustomashgraph.h"
//#include <strstream>
#include <stdio.h>
#pragma  hdrstop

//---------------------------------------------------------------------------
#include "globcli.h"
#include "..\windows\fdm.h"
#include "..\windows\fmsgs.h"
#include "clientdata.h"
#include "globcli.h"
#include "..\classes\cqmdiag.h"

#ifdef CQM_CLIENT_APPLICATION
  #include "cqmnet.h"
  #include "clialarmthread.h"
#endif

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "ZAbstractRODataset"
#pragma link "ZDataset"
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
TCustomAshGraphF *CustomAshGraphF = NULL;
TCustomAshGraphF *AshGraphs[MAX_CLIENT_POINTS];

//---------------------------------------------------------------------------
__fastcall TCustomAshGraphF::TCustomAshGraphF(TComponent* Owner)
    : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TCustomAshGraphF::Init(int pid)
{
    mypointindex = pid;
    myvagonindex = clipoints[mypointindex].id;
    sqlwhat = "moment, ad";
    sqlwhen = "21600";
    smooth = 3;
    chartinterval = 6.0/24;
    Caption = clipoints[mypointindex].title;

    Amin = 5.0;
    Amax = 60.0;
    LoadIntervals();
    LoadPosition();

    //если это НЕ Клиент
    #ifndef CQM_CLIENT_APPLICATION
    P->Visible = false;
    #endif

    #ifdef CQM_CLIENT_APPLICATION
    P->Visible = isserver;
    /*
    if (!isserver)
    {
        LA->Caption = "              ";
        LD->Caption = "отсутствует соединение с МКУ Сервером";
    }
    */
    #endif
}

//---------------------------------------------------------------------------
void __fastcall TCustomAshGraphF::Refresh(void)
{
    //точка контроля
    q->Close();
    q->SQL->Text = AnsiString("select ")+sqlwhat
                 + " from get_smooth_ash('" + clipoints[mypointindex].name
                 + "', " + sqlwhen
                 + ", "+IntToStr(smooth)+")";
    q->Open();

    //вагоны
    if (myvagonindex >= 0)
    {
        qvag->Close();
        qvag->SQL->Text = AnsiString("select moment, a as ad ")
                     + " from vagons where vname='" + clivagons[myvagonindex].name
                     + "' and addsecond(moment, "+sqlwhen+") >= current_timestamp"
                   //+ "' and cast(current_timestamp - moment as decimal(17,4)) <= cast(cast("+sqlwhen+" as float)/86400.0 as decimal(17,4))"
                     + " and a is not null and a>0 order by moment";
        qvag->Open();
    }
    //промежуток времени
    DBChart->BottomAxis->Maximum = Now()+0.000695; // 1.0/24/60 прибавляем одну минуту
    DBChart->BottomAxis->Minimum = Now()-chartinterval;

//если это Клиент
#ifdef CQM_CLIENT_APPLICATION

    if (!isserver)
        return;

    //текущие зольность и даигностика

    /*
    char str[SOCKET_BUFFER_SIZE];
    char buf[SOCKET_BUFFER_SIZE];
    int data;
    diag = 0;
    double val;
    */

    AnsiString q,a;
    q = AnsiString("core: getpoint ")+clipoints[mypointindex].name;
    if (CqmNetQuery(q,a))
    {
        if (!GetCurrentAsh(a.Trim()))
        {
            LA->Caption = "нет данных";
            LD->Caption = "";
            DoMsg(Caption+": Ошибка при разборе ответа, запрос: `"+q+"` Ответ сервера: `"+a+"`");
            return;
        }

        /*
        strcpy(str, a.c_str());
        std::istrstream ss(str);

        //приходит так: p a h diag
        ss>>data;
        //ok?
        if (data && CheckAnswer(a))
        {
            //пропустим вес
            ss>>buf;
            //зола
            ss>>buf;
            if (!strcmp(buf, "NULL"))
            {
                LA->Caption = "             ";//пробелы
            }
            else
            {
                double ash = atof(buf);
                if (ash < MIN_ASH_VALUE)
                {
                    LA->Caption = "             ";//пробелы
                }
                else
                {
                    LA->Caption = AnsiString().sprintf("%.1f", ash);
                }
            }
            //пропустим влажность
            ss>>buf;
            //диагностика
            ss>>diag;
            buf[0]=0;
            diag2str(buf, diag);
            LD->Caption = buf;
        }*/
    }
    else
    {
        LA->Caption = "нет данных";
        LD->Caption = "";
        DoMsg(Caption+": CqmNet ошибка, запрос: `"+q+"` Ответ сервера: `"+a+"`");
        return;
    }

    //Нужна ли сигнализация?
    if (diag&D_SOURCE || diag&D_P_BREAK || diag&D_A_BREAK)
    {
        DoMsg("Сигнализация. Ответ сервера: `"+a+"` = `"+LD->Caption+"`");
        ShowAlarmForm(Caption, LD->Caption);
    }

#endif
}

//---------------------------------------------------------------------------
bool __fastcall TCustomAshGraphF::GetCurrentAsh(AnsiString a)
{
    /* 1 p a h diag*/
    /* {1|0} {NULL|double} {NULL|double} {NULL|double} {int}*/
    int ok = -1, diag = 0;
    char p_str[16], a_str[16], h_str[16];
    char diag_buf[256];
    double ash = 0;
    p_str[0] = a_str[0] = h_str[0] = 0;
    int c = sscanf(a.c_str(), "%d %s %s %s %d", &ok, &p_str, &a_str, &h_str, &diag);
    if (c != 5)
        return false;
    if (ok != 1)
        return false;
    if (!strcmp(a_str, "NULL"))
    {
        LA->Caption = "             ";//пробелы
    }
    else
    {
        try
        {
            ash = StrToFloat(AnsiString(a_str));
        }
        catch(...)
        {
            return false;
        }

        if (ash < MIN_ASH_VALUE)
        {
            LA->Caption = "             ";//пробелы
        }
        else
        {
            LA->Caption = AnsiString().sprintf("%.1f", ash);
        }
    }

    diag2str(diag_buf, diag);
    LD->Caption = diag_buf;

    return true;
}

//---------------------------------------------------------------------------
void __fastcall TCustomAshGraphF::N1hourClick(TObject *Sender)
{
    N1hour->Checked = true;
    sqlwhen = "3600";

    chartinterval = 1.0/24;
    Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TCustomAshGraphF::N6hoursClick(TObject *Sender)
{
    N6hours->Checked = true;
    sqlwhen = "21600";
    chartinterval = 6.0/24;
    Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TCustomAshGraphF::N1DayClick(TObject *Sender)
{
    N1Day->Checked = true;
    sqlwhen = "86400";
    chartinterval = 1.0;
    Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TCustomAshGraphF::NGeneralClick(TObject *Sender)
{
    NGeneral->Checked = true;
    smooth = 1;
    Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TCustomAshGraphF::NSlidingClick(TObject *Sender)
{
    NSliding->Checked = true;
    smooth = 3;
    Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TCustomAshGraphF::NSliding6Click(TObject *Sender)
{
    NSliding6->Checked = true;
    smooth = 6;
    Refresh();
}

//---------------------------------------------------------------------------
void __fastcall TCustomAshGraphF::NPrintClick(TObject *Sender)
{
    AnsiString title = DBChart->Title->Text->Text;
    DBChart->Title->Text->Text = "График зольности на " + Caption
                               + " ; дата " + DateToStr(Date())
                               + " ; время " + TimeToStr(Time());
    DBChart->Gradient->Visible = false;
    ChartPreview(this, DBChart);
    DBChart->Gradient->Visible = true;
    DBChart->Title->Text->Text = title;
}

//---------------------------------------------------------------------------
__fastcall TCustomAshGraphF::~TCustomAshGraphF(void)
{
    //SavePosition();
}

//---------------------------------------------------------------------------
void __fastcall TCustomAshGraphF::LoadPosition(void)
{
	Top =	 ini->ReadInteger(AnsiString("AshGraph-")+IntToStr(mypointindex), "Top", 10);
	Left =	 ini->ReadInteger(AnsiString("AshGraph-")+IntToStr(mypointindex), "Left", 10);
	Width =	 ini->ReadInteger(AnsiString("AshGraph-")+IntToStr(mypointindex), "Width", 200);
	Height = ini->ReadInteger(AnsiString("AshGraph-")+IntToStr(mypointindex), "Height", 200);
}

//---------------------------------------------------------------------------
void __fastcall TCustomAshGraphF::LoadIntervals(void)
{
	Amin = 	 ini->ReadFloat  (AnsiString("AshGraph-")+IntToStr(mypointindex), "Amin", Amin);
	Amax = 	 ini->ReadFloat  (AnsiString("AshGraph-")+IntToStr(mypointindex), "Amax", Amax);

    DBChart->LeftAxis->Minimum = Amin;
    DBChart->LeftAxis->Maximum = Amax;

    myvagonindex =
             ini->ReadInteger(AnsiString("AshGraph-")+IntToStr(mypointindex), "VagonId", myvagonindex);
}

//---------------------------------------------------------------------------



