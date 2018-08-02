/*---------------------------------------------------------------------------
    Copyright (c) 2002-2004 Пиленков  Олег Григорьевич,
                            Невойса   Эрик Григорьевич,
                            Глузман   Владимир Иосифович,
                            Цехмистро Станислав Сергеевич,
                            Кеба      Руслан Анатольевич.

    ЯДРО ПРОГРАММНЫХ СРЕДСТВ
    КОМПЛЕКСА МОНИТОРИНГА КАЧЕСТВА УГЛЕЙ

    Файл: hurup.h

    Описание класса huru - парсер и решатель huru-скриптов

---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
#ifndef hurupH
#define hurupH

//---------------------------------------------------------------------------
#include <istream>
#include <map>
#include <string>

//---------------------------------------------------------------------------
enum token_value {
	NAME,      NUMBER,     END,
	PLUS='+',  MINUS='-',  MUL='*',    DIV='/',
    MORE='>',  LESS='<',   EQU='=',
    B_AND='&', B_OR='|',   B_NEG='!',
	PRINT=';', ASSIGN=':', LP='(',     RP=')'
};

//---------------------------------------------------------------------------
typedef std::map<std::string, double> hurunames;

//---------------------------------------------------------------------------
#define HURU_MSG_LEN 255

//---------------------------------------------------------------------------
class huru
{
    public:

    huru(void);
    ~huru(void);
    double solve(char* t);
    void insert (char* name, double val);
    int errors;
    char errors_msg[HURU_MSG_LEN];

    private:


    std::istream *in;

    token_value curr_tok;

    double expr();
    double term();
    double prim();
    token_value get_token();

    double error(const char* s);

    double number_value;
    char name_string[HURU_MSG_LEN];

    hurunames names;
};



//---------------------------------------------------------------------------
#endif
