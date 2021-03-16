#if !defined(__CIFRAS_H)

#define	__CIFRAS_H

#include <stdlib.h>

#define Uses_TNSSortedCollection
#include <tvision\tv.h>

#define	NUM_NUMEROS	6

enum EOperaciones { Ninguna,Suma,Multiplicacion,Resta,Division,Op1=Suma,OpL=Division };

typedef struct _TEnunciado
{
	unsigned numeros[NUM_NUMEROS];
	unsigned objetivo;
} TEnunciado;

class Numero : public TObject
{
	public:
		unsigned numero;

		inline Numero(unsigned _numero) { numero=_numero; }
};

class Operacion : public Numero
{
	public:
		EOperaciones Operacion;
		unsigned numero1,numero2;

		inline Operacion(unsigned _numero):Numero(_numero){}
};

class NumeroCollection : public TNSSortedCollection
{
	public:
		inline NumeroCollection(ccIndex aLimit):TNSSortedCollection(aLimit,0){}
		inline virtual ccIndex insert( Numero *tc )
		{
			return TNSSortedCollection::insert( tc );
		}

		virtual void *keyOf(void *item);

	private:

   	virtual int compare( void *key1, void *key2);
		virtual void freeItem( void *item );
};

class Estado
{
	public:
		NumeroCollection *numeros;
		EOperaciones operacion;
		int i,j;
		Estado *next;

		Estado(NumeroCollection *n);
		Estado(NumeroCollection *n,EOperaciones op,int ii,int jj);
		~Estado();

		void init();
		void initIJ();
		Boolean nextComb();
};

class StackSt
{
	public:
		inline StackSt():stack(NULL){}
      inline ~StackSt(){ free(); }
		void push(Estado *e);
		Estado *pop();
		void free();
	private:
		Estado *stack;
};

class Cifras
{
	public:
		static const char *numerosTV[];

		void generar_random_tv(TEnunciado &e) const;
		void generar_random_canalsur(TEnunciado &e) const;
		void generar_random_1_100(TEnunciado &e) const;
		Numero *resolver(TEnunciado &e) const;
	private:
		static unsigned grupos[][6];

		inline int ajusteidxgrupo(int idx) const
		{
			return ((idx % 7)!=0) ? idx: idx+1;
		}
		void mezclargr2(unsigned *result,int n) const;
		void mezclargr(unsigned *result) const;
		unsigned obtnumero(unsigned *result,int grupo) const;
		int randomgrupo(int n123,int num) const;
      inline void randomobjetivo(TEnunciado &e) const
		{
			e.objetivo=100+random(900);
		}
      Numero *resolver(StackSt &stack) const;
};

#endif
