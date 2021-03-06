#define Uses_TKeys
#define Uses_TApplication
#define Uses_TEvent
#define Uses_TRect
#define Uses_TDialog
#define Uses_TStaticText
#define Uses_TButton
#define Uses_TMenuBar
#define Uses_TSubMenu
#define Uses_TMenuItem
#define Uses_TStatusLine
#define Uses_TStatusItem
#define Uses_TStatusDef
#define Uses_TDeskTop
#include <tvision\tv.h>

#include "tvcifras.h"
#include "gadgets.h"
#include "cifradlg.h"

TVCifrasApp::TVCifrasApp()
	:TProgInit
	(
		&TVCifrasApp::initStatusLine,
		&TVCifrasApp::initMenuBar,
		&TVCifrasApp::initDeskTop
	)
{
	TRect r = getExtent();                      // Create the clock view.
	r.a.x = r.b.x - 9;      r.b.y = r.a.y + 1;
	clock = new TClockView( r );
	insert(clock);

	r = getExtent();                            // Create the heap view.
	r.a.x = r.b.x - 13;     r.a.y = r.b.y - 1;
	heap = new THeapView( r );
	insert(heap);

   NewCifraDlg();
}

TMenuBar *TVCifrasApp::initMenuBar( TRect r )
{

	 r.b.y = r.a.y+1;

	 return new TMenuBar( r,
		*new TSubMenu( "TV~C~ifras", kbAltC ) +
		  *new TMenuItem( "~N~ew Cifra...", NewCifrasDlgCmd, kbAltN ) +
			newLine() +
		  *new TMenuItem( "E~x~it", cmQuit, cmQuit, hcNoContext, "Alt-X" )
		  );

}

TStatusLine *TVCifrasApp::initStatusLine( TRect r )
{
	 r.a.y = r.b.y-1;
	 return new TStatusLine( r,
		  *new TStatusDef( 0, 0xFFFF ) +
				*new TStatusItem( "~Alt-X~ Exit", kbAltX, cmQuit ) +
				*new TStatusItem( 0, kbF10, cmMenu )
				);
}

void TVCifrasApp::idle()
{
	 TProgram::idle();
	 clock->update();
	 heap->update();
} 

void TVCifrasApp::handleEvent( TEvent& event )
{
    TApplication::handleEvent( event );
    if( event.what == evCommand )
        {
        switch( event.message.command )
            {
				case NewCifrasDlgCmd:
					 NewCifraDlg();
                clearEvent( event );
                break;
            default:
                break;
            }
        }
}

void TVCifrasApp::NewCifraDlg()
{
	TCifrasDlg *dlg=new TCifrasDlg("prueba");

	deskTop->insert(dlg);
}

int main()
{
	TVCifrasApp *app=new TVCifrasApp;

	app->run();

	TObject::destroy(app);

	return 0;
}
