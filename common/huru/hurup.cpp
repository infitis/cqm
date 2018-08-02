//---------------------------------------------------------------------------
#include "hurup.h"

//---------------------------------------------------------------------------
#include <ctype.h>
#include <string.h>
#include <strstream>
#include <iostream.h>

//---------------------------------------------------------------------------
huru::huru(void)
{
	insert("pi", 3.1415926535897932385);
	insert("e",  2.7182818284590452354);
    errors = 0;
    in = NULL;
}

//---------------------------------------------------------------------------
huru::~huru(void)
{
    names.clear();
}

//---------------------------------------------------------------------------
double huru::solve(char* t)
{
    errors = 0;
    errors_msg[0] = 0;
    double ret = 0;
    std::istrstream *s = new std::istrstream(t);
    try
    {
        in = s;
        while (!(s->eof()))
        {
            get_token();
            if (curr_tok == END) break;
		    if (curr_tok == PRINT) continue;
            ret = expr();
            insert("prev", ret);
        }
    }
    __finally
    {
        delete s;
    }

    return ret;
}

//---------------------------------------------------------------------------
void huru::insert (char* name, double val)
{
    names[std::string(name)] = val;
}

//---------------------------------------------------------------------------
double huru::expr()	// складывает  и вычитает
{
	double left = term();
	for(;;)
    {
		switch(curr_tok)
        {
			case PLUS:
            {
				get_token();	// случай '+'
				left += term();
				break;
            }
			case MINUS:
            {
				get_token();	// случай '-'
				left -= term();
				break;
            }
			default:
				return left;
		}
    }
}

//---------------------------------------------------------------------------
double huru::term()	// умножает и складывает
{
	double left = prim();
	for(;;)
    {
		switch(curr_tok)
        {
			case MUL:
            {
				get_token();	// случай '*'
				left *= prim();
				break;
            }
			case DIV:
            {
				get_token();	// случай '/'
				double d = prim();
				if (d == 0) return error("division by 0");
				left /= d;
				break;
            }
			case MORE:
            {
				get_token();	// случай '>'
                double d = prim();
				left = (left > d);
				break;
            }
			case LESS:
            {
				get_token();	// случай '<'
                double d = prim();
				left = (left < d);
				break;
            }
			case EQU:
            {
				get_token();	// случай '<'
                double d = prim();
				left = (left == d);
				break;
            }
			case B_AND:
            {
				get_token();	// случай '&'
                double d = prim();
				left = (left && d);
				break;
            }
			case B_OR:
            {
				get_token();	// случай '|'
                double d = prim();
				left = (left || d);
				break;
            }
			default:
            {
				return left;
            }
        }
	}
}

//---------------------------------------------------------------------------
double huru::prim()               // обрабатывает первичное
{
    switch (curr_tok)
    {
		case NUMBER:
        {          // константа с плавающей точкой
			get_token();
			return number_value;
        }
		case NAME:
        {
			if (get_token() == ASSIGN)
            {
                char thisname[256];
                strcpy(thisname, name_string);
                get_token();
                double val = expr();
                names[std::string(thisname)] = val;
				return val;
			}
			return names[std::string(name_string)];
        }
		case MINUS:               // унарный минус
        {
			get_token();
			return -prim();
        }
		case B_NEG:               // логической отрицание (унарное)
        {
			get_token();
            double d = prim();
			return !d;
        }
		case LP:
        {
			get_token();
			double e = expr();
			if (curr_tok != RP) return error("need )");
			get_token();
			return e;
        }
		case END:
        {
			return 1;
        }
		default:
        {
			return error("need primary");
        }
	}
}


//---------------------------------------------------------------------------
token_value huru::get_token()
{
	char ch;
	do
    {
		if(!in->get(ch)) return curr_tok = END;
	}
    while (ch!='\n' && isspace(ch));

	switch (ch)
    {
		case ';':
		case '\n':
        {
			*in >> ws;	// пропуск обобщенного пробела
			return curr_tok=PRINT;
        }
		case '*':
		case '/':
		case '+':
		case '-':
		case '(':
		case ')':
		case ':':
        case '>':
        case '<':
        case '=':
        case '&':
        case '|':
        case '!':
			return curr_tok=token_value(ch);
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
		case '.':
        {
			in->putback(ch);
			*in >> number_value;
			return curr_tok=NUMBER;
        }
		default:	// NAME, NAME= или ошибка
        {
			if (isalpha(ch))
            {
				char* p = name_string;
				*p++ = ch;
				while (in->get(ch) && isalnum(ch)) *p++ = ch;
				in->putback(ch);
				*p = 0;
				return curr_tok=NAME;
			}
			error("bad token");
			return curr_tok=PRINT;
        }
	}
}

//---------------------------------------------------------------------------
double huru::error(const char* s)
{
    if (strlen(errors_msg) + strlen(s) >= HURU_MSG_LEN - 16)
        return 0;
    strcat(errors_msg, " | ");
    strcat(errors_msg, s);
	errors++;
	return 0;
}

//---------------------------------------------------------------------------

