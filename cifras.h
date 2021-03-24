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
		inline Numero(unsigned _numero) { numero=_numero; }
		inline unsigned getNumero() const { return numero; }
	protected:

		unsigned numero;
};

class Operacion : public Numero
{
	public:
		inline Operacion(unsigned _numero):Numero(_numero){}
		Operacion(EOperaciones op,unsigned n1,unsigned n2,unsigned n);

		static Operacion *Calc(EOperaciones op,unsigned n1,unsigned n2);

	private:
		EOperaciones operacion;
		unsigned numero1,numero2;
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
		Estado(NumeroCollection *n);
		Estado(NumeroCollection *n,EOperaciones op,int ii,int jj);
		~Estado();

		inline void setNext(Estado *st) { next=st; }
		inline Estado *getNext() const { return next; }
		inline NumeroCollection *getNumeros() const { return numeros; }
		void init();
		void initIJ();
		Boolean nextComb();
	private:
		NumeroCollection *numeros;
		EOperaciones operacion;
		int i,j;
		Estado *next;
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

class Resuelve
{
	public:
		Resuelve();
		void resolver(TEnunciado &e);

		inline Numero *getSolucion() const { return solucion; }
	private:
		StackSt stack;
		unsigned objetivo;
		Numero *solucion;
		unsigned dist;

		void resolver();
		Boolean resolver(Estado &st);
		Boolean resolver1N(Numero *n);
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
};

#endif
