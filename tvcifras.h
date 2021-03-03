class THeapView;
class TClockView;

class TVCifrasApp : public TApplication
{
	public:

		TVCifrasApp();

		static TMenuBar *initMenuBar( TRect );
		static TStatusLine *initStatusLine( TRect );

      virtual void idle();              // Updates heap and clock views

	private:

		THeapView *heap;                  // Heap view
		TClockView *clock;                // Clock view
};
