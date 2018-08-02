//---------------------------------------------------------------------------
#include <ctype.h>

//---------------------------------------------------------------------------
#include "cqmstreamparse.h"
#include "cqmsys.h"

//---------------------------------------------------------------------------
void SkipSpacesAndComments(std::istream& s)
{
    char c;
    char n[MAX_NAME_LEN];
    bool ok=0;
    do
    {
        s.get(c);
        if (c == COMMENT_SYMBOL)
        {
            s.putback(c);
            s.getline(n, MAX_NAME_LEN);
        }
        else
        if (!isspace(c))
        {
            s.putback(c);
            ok = 1;
        }
    }
    while (!ok && !s.eof());
}

//---------------------------------------------------------------------------
void GetQuote(std::istream& s, char* buf, int bufsize,
              char forwardQuote, char closeQuote)
{
    int i = 0; char c = 0;
    while (c != forwardQuote && !s.eof())
    {
        s.get(c);
    }
    c = 0;
    while (!s.eof() && i<bufsize)
    {
        s.get(c);
        if (c == closeQuote)
        {
            break;
        }
        else
        {
            buf[i++] = c;
        }
    }
    buf[i] = 0;
}

//---------------------------------------------------------------------------
void GetPair(std::istream& s, int bufsize, char* var, char* val, char divider)
{
    SkipSpacesAndComments(s);
    int i = 0; char c = 0;
    while (!s.eof() && i<bufsize)
    {
        s.get(c);
        if (c == divider)
        {
            break;
        }
        if (isprint(c) && !isspace(c))
        {
            var[i++] = c;
        }
    }

    var[i] = 0; i = 0; c = 0;
    SkipSpacesAndComments(s);
    while (i<bufsize)
    {
        s.get(c);
        if (s.eof())
        {
            break;
        }
        if (isprint(c) && !isspace(c))
        {
            val[i++] = c;
        }
        else
        {
            break;
        }
    }
    val[i] = 0;
}

//---------------------------------------------------------------------------


