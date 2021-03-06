#if !defined(__CIFRADLG_H)

#define __CIFRADLG_H

#define Uses_TRect
#define Uses_TDialog
#define Uses_TInputLine
#define Uses_TStreamable
#include <tvision\tv.h>

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
};

#endif