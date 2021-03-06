#if !defined(__CIFRADLG_H)

#define __CIFRADLG_H

#define Uses_TRect
#define Uses_TDialog
#include <tvision\tv.h>

class TCifrasDlg : public TDialog
{
	public:

	 //TCifrasDlg( StreamableInit ) : TDialog (streamableInit), TWindowInit(&TForm::initFrame) {};
	 TCifrasDlg( const char* );
};

#endif