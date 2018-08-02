//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#include <fstream.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#include "ReadCsv.h"

//---------------------------------------------------------------------------
// Reads file of CSV into WM_LDData
//---------------------------------------------------------------------------
// Read Headings into string array
static int GetNextLine(istream & Fin,TStringList * pReturnValues)
{
   pReturnValues->Clear();
   const cBUFFER_SIZE = 2000;
   char * szBuffer = new char[cBUFFER_SIZE + 1 + 1];

   Fin.getline(szBuffer, cBUFFER_SIZE, '\n');

   long nCharsIn = Fin.gcount();
   if ( nCharsIn <= 0 )
   {
      delete [] szBuffer;
      return 1;
   }
   if ( szBuffer[(int)(nCharsIn-1)] != ',' )
   {
      // No terminating comma, so add one
      szBuffer [(int) nCharsIn] = ',';
      nCharsIn++;
      szBuffer [(int) nCharsIn ] = '\0';
   }
   int x = 0;

   char * szOutBuffer = new char[cBUFFER_SIZE + 1];

   while ( x < nCharsIn)
   {
      szOutBuffer[0] = '\0';
      int nOut = 0;
      switch ( szBuffer[x] )
      {
         case ',':
         {
            // empty column
            x++;
            break;
         }
         case '"':
         case '\'':
         case '`':
         {
            char cQuote = szBuffer[x];
            // We have the start of a quoted string
            x++;
            while ( x < nCharsIn )
            {
               if ( cQuote == szBuffer[x] )
               {
                  x++;
                  if ( szBuffer[x] != cQuote )
                  {
                     break;
                  }
                  // else  Double quote, so keep one and keep looking
               }
               else
               if ( '\\' == szBuffer[x] && 'n' == szBuffer[x+1] )
               {
                  // newline
                  x++;
                  x++;
                  szOutBuffer[nOut++] = '\n';
                  continue;
               }
               szOutBuffer[nOut++] = szBuffer[x++];
            }
            while ( x < nCharsIn && szBuffer[x] != ',' )
            {
               // Skip to comma
               x++;
            }
            x++; // ignore comma
            break;
         }
         default:
         {
            nOut = 0;
            while ( x < nCharsIn && szBuffer[x] != ',' )
            {
               szOutBuffer[nOut++] = szBuffer[x++];
            }
            x++;
         }
      }
      szOutBuffer[nOut] = '\0';
      AnsiString s = szOutBuffer;
      s = s.Trim();
      pReturnValues->Add(s);
   }
   delete [] szOutBuffer;
   delete [] szBuffer;
#ifdef TRACE_CSV
   Log;
   for (int i = 0; i < asValues.ItemsInArray(); i++)
   {
      if ( pReturnValues->Strings[i].Length() > 0 && pReturnValues->Strings[i][0] > '9' )
         Log << '"' << pReturnValues->Strings[i] << "\",";
      else
         Log << pReturnValues->Strings[i] << ",";
   }
   Log << endl;
#endif;
   return 0;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
int const CSV2ListData(AnsiString & sCSVFile, TStringGrid * StringGrid)
{
   StringGrid->RowCount = 2;
   StringGrid->ColCount = 1;
   ifstream Fin(sCSVFile.c_str());
   if ( !Fin )
   {
      AnsiString s = "Failed to open input CSV file : \"" + sCSVFile + '"';
      MessageBox(0,s.c_str(), "File Access Error",MB_OK | MB_APPLMODAL | MB_ICONWARNING);
      return 1;
   }

   TStringList * RowStrings = new TStringList;
   int nLinesInput = 0;
   // Read Headings into string array
   int nReply = GetNextLine(Fin,RowStrings);
   nLinesInput++;

   int nColumns = RowStrings->Count;
   // set list title
   if ( nReply > 0 || nColumns < 1 )
   {
      return 1;
   }
   StringGrid->ColCount = nColumns;
   for (int iColumn = 0; iColumn < nColumns; iColumn++)
   {
      StringGrid->Cells[iColumn][0] = RowStrings->Strings[iColumn];
   }
   // Process Data
   while ( Fin  && nReply == 0 )
   {
      nReply = GetNextLine(Fin,RowStrings);
      if ( nReply )
         break;

      nLinesInput++;
      StringGrid->RowCount = nLinesInput;
      if ( RowStrings->Count != nColumns )
      {
         AnsiString s = "Wrong number of columns read: \n\n  Expected " + String(nColumns) +
                    "\n  Found " + String(RowStrings->Count) +
                    "\n  Line  " + String(nLinesInput);
         MessageBox(0,s.c_str(), "File Content Error",MB_OK | MB_APPLMODAL | MB_ICONWARNING);
         return 1;
      }
      for (int iColumn = 0; iColumn < nColumns; iColumn++)
      {
         StringGrid->Cells[iColumn][nLinesInput-1] = RowStrings->Strings[iColumn];
      }
   }
   Fin.close();
   if ( nLinesInput < 2 )
   {
      String s("Too few lines read (");
      s = s + String(nLinesInput) + ") to be a valid CSV data file.";
      MessageBox(0,s.c_str(), "File Content Error",MB_OK | MB_APPLMODAL | MB_ICONWARNING);
      return 1;
   }
   return 0;
}

