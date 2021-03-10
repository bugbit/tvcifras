#define Uses_TDialog
#define Uses_TRect
#define Uses_TLabel
#define Uses_TInputLine
#define Uses_TStreamableClass
#define Uses_TInputLine
#define Uses_THistory
#define Uses_TScrollBar
#define Uses_TMemo
#define Uses_TButton
#define Uses_TStreamable
#define Uses_MsgBox
#define Uses_TKeys
#define Uses_TEvent
#include <tvision\tv.h>
#include <string.h>
#include <stdlib.h>
#include <strstrea.h>

#include "cifradlg.h"
#include "cifras.h"

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
		 TDialog( TRect(1,1,58,22), aTitle),
		 TWindowInit(&TCifrasDlg::initFrame)
{
	int labelCol=1;
	int x=labelCol+1;
	int y=1+2;
	int x1;
	TRect r;
	TView *c1=NULL;
	TView *c;
	TMemo *d;

   randomize();
	for (int i=0;i++<NUM_NUMEROS;x=x1+4)
	{
		x1=x+5;
		r = TRect(x, y, x1, y + 1);
		c = new TInputLine(r,4);
		insert(c);

		if (c1==NULL)
			c1=c;

		THistory *h=new THistory( TRect( x1, y, x1+3, y+1 ), (TInputLine *)c, i );

		for(char **str=(char **)Cifras::numerosTV;*str;str++)
			h->recordHistory(*str);

		insert(h);
	}

	y -= 2;

	r= TRect(labelCol, y, labelCol + 26, y + 1);
	insert( new TLabel(r, "Numeros de partida:", c1));

	y += 6;
	x=labelCol+1;

	r = TRect(x, y, x+5, y + 1);
	c = new TInputLine(r,4);
	insert(c);

	x += 7;
	int wBtn=10;

	r = TRect(x, y, x+wBtn, y + 2);
	insert( new TButton(r, "~R~esuelve", ResuelveCmd, bfDefault));

	x += wBtn+1;
	r = TRect(x, y, x+wBtn, y + 2);
	insert( new TButton(r, "Genera ~L~a2", GeneraLa2Cmd, bfDefault));

	x += wBtn+1;
	r = TRect(x, y, x+wBtn, y + 2);
	insert( new TButton(r, "Genera ~C~analSur", GeneraCanalSurCmd, bfDefault));

	x += wBtn+1;
	r = TRect(x, y, x+wBtn, y + 2);
	insert( new TButton(r, "~G~enera 1-100", Genera1_100Cmd, bfDefault));

	y -= 2;

	r= TRect(labelCol, y, labelCol + 36, y + 1);
	insert( new TLabel(r, "Numero Objetivo (entre 100 y 999)", c));

	y += 6;
	x=labelCol+1;

	r = TRect(x+50, y, x+51, y + 8);
	c = new TScrollBar(r);
	insert(c);

	r = TRect(x, y, x + 50, y + 8);
	d = new TMemo(r, 0, (TScrollBar *) c, 0, ResultadoLength);
	insert(d);

	y -= 2;

	r= TRect(labelCol, y, labelCol + 26, y + 1);
	insert( new TLabel(r, "Resultado del analisis", c));

	selectNext(False);      // Select first field

	/*
	TCifrasDlgData data;

	strcpy(data.Numeros[0],"111");
	strcpy(data.Numeros[1],"222");
	strcpy(data.Numeros[2],"333");
	strcpy(data.Numeros[3],"444");
	strcpy(data.Numeros[4],"555");
	strcpy(data.Numeros[5],"666");
	strcpy(data.Objetivo,"999");
	data.Resultado.textLen=strlen("Resultado");
	strcpy(data.Resultado.textData,"Resultado");
	setData(&data);
	*/
}

void TCifrasDlg::handleEvent( TEvent& event)
{
	// Respond to CANCEL button and ESC
	 if ( ( (event.what == evKeyDown) && (event.keyDown.keyCode == kbEsc) ) /* ||
		 ( (event.what == evCommand) && (event.message.command == cmCancel) )*/ )
	{
		clearEvent(event);
		destroy(this);
		return;
	}

	TDialog::handleEvent(event);

   // Respond to SAVE button
	if ( (event.what == evCommand) && (event.message.command == GeneraLa2Cmd) )
	{
		clearEvent(event);
		generar_random_tv();
   }
}

void TCifrasDlg::putEnunciado(TEnunciado &e)
{
	TCifrasDlgData data;

	getData(&data);
	for(int i=0;i< NUM_NUMEROS;i++)
   	itoa(e.numeros[i],data.numeros[i],10);
	itoa(e.objetivo,data.objetivo,10);
   setData(&data);
}

void TCifrasDlg::generar_random_tv()
{
	TEnunciado e;

	Cifras::generar_random_tv(e);
   putEnunciado(e);
}
