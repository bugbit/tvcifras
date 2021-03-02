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

TVCifrasApp::TVCifrasApp()
	:TProgInit
	(
		&TVCifrasApp::initStatusLine,
		&TVCifrasApp::initMenuBar,
		&TVCifrasApp::initDeskTop
	)
{
}

TMenuBar *TVCifrasApp::initMenuBar( TRect r )
{

	 r.b.y = r.a.y+1;

	 return new TMenuBar( r,
		*new TSubMenu( "~H~ello", kbAltH ) +
		  /* *new TMenuItem( "~G~reeting...", GreetThemCmd, kbAltG ) +
			newLine() + */
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

int main()
{
	TVCifrasApp app;
	app.run();

   return 0;
}
