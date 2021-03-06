#if !defined(__TVCIFRAS_H)

#define __TVCIFRAS_H

const int NewCifrasDlgCmd = 100;

class THeapView;
class TClockView;

class TVCifrasApp : public TApplication
{
	public:

		TVCifrasApp();

		static TMenuBar *initMenuBar( TRect );
		static TStatusLine *initStatusLine( TRect );

		virtual void idle();              // Updates heap and clock views
		virtual void handleEvent( TEvent& event );

	private:

		THeapView *heap;                  // Heap view
		TClockView *clock;                // Clock view

      void NewCifraDlg();
};

#endif
