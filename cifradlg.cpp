#define Uses_TDialog
#define Uses_TRect
#define Uses_TLabel
#define Uses_TInputLine
#define Uses_TStreamableClass
#define Uses_TInputLine
#define Uses_TStreamable
#define Uses_MsgBox
#include <tvision\tv.h>
#include <string.h>
#include <stdlib.h>
#include <strstream.h>

#include "cifradlg.h"

// TNumInputLine

const char * const TNumInputLine::name = "TNumInputLine";

void TNumInputLine::write( opstream& os )
{
    TInputLine::write( os );
    os << min;
    os << max;
    
}

void *TNumInputLine::read( ipstream& is )
{
    TInputLine::read( is );
    is >> min;
    is >> max;
    return this;
}

TStreamable *TNumInputLine::build()
{
    return new TNumInputLine( streamableInit );
}


TStreamableClass RNumInputLine( TNumInputLine::name,
                                  TNumInputLine::build,
                                  __DELTA(TNumInputLine)
                                );

TNumInputLine::TNumInputLine( const TRect& bounds,
			      int aMaxLen,
			      long aMin,
			      long aMax ) :
    TInputLine(bounds, aMaxLen)
{
    min = aMin;
    max = aMax;
}


ushort TNumInputLine::dataSize()
{
    return sizeof(long);
}

void TNumInputLine::getData( void *rec )
{
    *(long *)rec = atol(data);
}

void TNumInputLine::setData( void *rec )
{
    ltoa(*(long *)rec, data, 10);
    selectAll(True);
}

Boolean TNumInputLine::valid( ushort command )
{
    long value;
    Boolean ok;
    char msg[80];
    ostrstream os(msg, 80);

    ok = True;
    if ( (command != cmCancel) && (command != cmValid) )
        {
        if (strlen(data) == 0)
            strcpy(data,"0");
        value = atol(data);
        if ( (value == 0) || (value < min) || (value > max) )
            {
            select();
            os << "Number must be from " << min << " to " << max << "." << ends;
            messageBox(os.str(), mfError + mfOKButton);
            selectAll(True);
            ok = False;
            }
        }
    if (ok)
        return TInputLine::valid(command);
    else
        return False;
}

TCifrasDlg::TCifrasDlg( const char *aTitle) :
		 TDialog( TRect(1,1,30,20), aTitle),
		 TWindowInit(&TCifrasDlg::initFrame)
{
	int labelCol=1;
	int y=1+2;

	TRect r = TRect(labelCol+1, y, labelCol + 5, y + 1);
	TNumInputLine *c = new TNumInputLine(r,4,1,100);
	insert(c);

	y -= 2;

	r= TRect(labelCol, y, labelCol + 28, y + 1);
	insert( new TLabel(r, "Introduccion de datos", c));
}
