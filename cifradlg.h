#if !defined(__CIFRADLG_H)

#define __CIFRADLG_H

#define Uses_TRect
#define Uses_TDialog
#define Uses_TInputLine
#define Uses_TStreamable
#define Uses_TEvent
#include <tvision\tv.h>

#include "cifras.h"

const int ResultadoLength=512;

const int ResuelveCmd = 2000;
const int GeneraLa2Cmd = 2001;
const int GeneraCanalSurCmd = 2002;
const int Genera1_100Cmd = 2001;

typedef char TNumeroRec[4];

typedef struct _TResultadoData
{
	ushort textLen;
	char textData[ResultadoLength];
} TResultadoData;

typedef struct _TCifrasDlgData
{
	TNumeroRec numeros[NUM_NUMEROS];
	TNumeroRec objetivo;
	TResultadoData resultado;
} TCifrasDlgData;

// Accepts only valid numeric input between Min and Max

class TNumInputLine : public TInputLine
{

public:

    TNumInputLine( const TRect&, int, long, long );
    virtual ushort dataSize();
    virtual void getData( void *);
    virtual void setData( void *);
    virtual Boolean valid( ushort );
    long min;
    long max;

protected:

    TNumInputLine( StreamableInit ) : TInputLine( streamableInit ) {};
    virtual void write( opstream& );
    virtual void *read( ipstream& );

private:

    virtual const char *streamableName() const
        { return name; }

public:

    static const char * const name;
    static TStreamable *build();

};

inline ipstream& operator >> ( ipstream& is, TNumInputLine& cl )
    { return is >> (TStreamable&)cl; }
inline ipstream& operator >> ( ipstream& is, TNumInputLine*& cl )
    { return is >> (void *&)cl; }
inline opstream& operator << ( opstream& os, TNumInputLine& cl )
	 { return os << (TStreamable&)cl; }
inline opstream& operator << ( opstream& os, TNumInputLine* cl )
    { return os << (TStreamable *)cl; }


class TCifrasDlg : public TDialog
{
	public:

	 //TCifrasDlg( StreamableInit ) : TDialog (streamableInit), TWindowInit(&TForm::initFrame) {};
	 TCifrasDlg( const char* );

    virtual void handleEvent( TEvent& );
};

#endif