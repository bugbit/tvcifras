#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include "cifras.h"

void *NumeroCollection::keyOf(void *item)
{
	return (void *)((Numero *) item)->getNumero();
}

int NumeroCollection::compare( void *key1, void *key2)
{
	return (unsigned *) key2-(unsigned *) key1;
}

void NumeroCollection::freeItem( void *item )
{
	delete (Numero *) item;
}

Estado::Estado(NumeroCollection *n)
{
	numeros=n;
   init();
}

Estado::Estado(NumeroCollection *n,EOperaciones op,int ii,int jj)
{
	numeros=n;
	operacion=op;
	i=ii;
	j=jj;
}

Estado::~Estado()
{
	if (numeros!=NULL)
		delete numeros;
}

void Estado::init()
{
	operacion=Op1;
	initIJ();
}

void Estado::initIJ()
{
	i=0;
	j=-1;
}

Boolean Estado::nextComb()
{
	if (++j>=numeros->getCount())
	{
		if (++i>=numeros->getCount()-1)
			j=i+1;
		else
		{
			operacion++;
			if (operacion>OpL)
				return False;

			initIJ();
		}
	}

   return True;
}

void StackSt::push(Estado *e)
{
	if (stack!=NULL)
		e->setNext(stack);
	stack=e;
	e->setNext(NULL);
}

Estado *StackSt::pop()
{
	if (stack==NULL)
		return NULL;

	Estado *e=stack;
	stack=e->getNext();

	return e;
}

void StackSt::free()
{
	while(pop());
}

Resuelve::Resuelve():stack(),solucion(NULL),dist(0xFFFF) {}

void Resuelve::resolver(TEnunciado &e)
{
	NumeroCollection *c=new NumeroCollection(NUM_NUMEROS);
	unsigned *n=e.numeros;

	for (int i=i<NUM_NUMEROS;i-->0;)
		c->insert(new Numero(*n++));

	Estado *st=new Estado(c);

	stack.push(st);
	objetivo=e.objetivo;
}

void Resuelve::resolver()
{
	for(;;)
	{
		Estado *st=stack.pop();

		if (st==NULL)
			return;

		if (!st->nextComb())
		{
			delete st;

			continue;
		}

		if (resolver(*st))
			return;
	}
}

Boolean Resuelve::resolver(Estado &st)
{
	NumeroCollection *n=st.getNumeros();

	switch(n->getCount())
	{
		case 1:
			return resolver1N((Numero *) n->at(0));
		case 2:
		default:
			return False;
	}

	return False;
}

Boolean Resuelve::resolver1N(Numero *n)
{
	unsigned numero=n->getNumero();

	if (numero==objetivo)
	{
		solucion=n;
      dist=0;

		return True;
	}

	if (solucion==NULL)
		solucion=n;
	//else if (abs(soluc))

	return False;
}

const char *Cifras::numerosTV[]=
{
	"1","2","3","4","5","6","7","8","9","10","25","50","75","100",NULL
};

unsigned Cifras::grupos[][6]=
{
	{ 1,2,3,4,5,6 },
	{ 7,8,9,1,2,3 },
	{ 4,5,6,7,8,9 },
	{ 10,10,25,50,75,100 }
};

/*
	Aplicamos el algoritmo para mezcla de Fisher-Yates
	n = El numero de grupos que queremos juntar
*/
void Cifras::mezclargr2(unsigned *result,int n) const
{
	int t=6*n,i,r,idx1,idx2;
	unsigned tmp;

	for (i=t;i>=0;i--)
	{
		r=random(t);
		idx1=ajusteidxgrupo(i);
		idx2=ajusteidxgrupo(r);
		tmp=result[idx1];
		result[idx1]=result[idx2];
		result[idx2]=tmp;
	}
}

void Cifras::mezclargr(unsigned *result) const
{
	int i,idx1,idx2,t=100+random(200);
	unsigned tmp;
	unsigned *rptr=result;
	unsigned *m=(unsigned *) &grupos;

	for (i=0;i<4;i++,rptr += 6,m += 6)
	{
		*rptr++=6;
		memcpy(rptr,m,6*sizeof(int));
	}
	mezclargr2(result,3);
	mezclargr2(result+7*3,1);
	//memcpy(result,mgrupos,4*6*sizeof(int));
	for (i=0;i<t;i++)
	{
		idx1=random(3)*7+random(6)+1;
		idx2=random(3)*7+random(6)+1;
		tmp=result[idx1];
		result[idx1]=result[idx2];
		result[idx2]=tmp;
		idx1=3*7+random(6)+1;
		idx2=3*7+random(6)+1;
		tmp=result[idx1];
		result[idx1]=result[idx2];
		result[idx2]=tmp;
	}
}

unsigned Cifras::obtnumero(unsigned *result,int grupo) const
{
	unsigned *rptr=result+7*(grupo-1);
	unsigned num=rptr[*rptr];

	--*rptr;

	return num;
}

int Cifras::randomgrupo(int n123,int num) const
{
	int p=random(100);
	int p123=(num) ? 100*n123/num : 0;
	int p100123=(100-p123)/2;
	int g=(p<=p100123) ? random(3)+1 : 4;

	return g;
}

void Cifras::generar_random_tv(TEnunciado &e) const
{
	unsigned result[4][7];
	int i;
	int grupo;

	mezclargr((unsigned *) &result);
	for (i=0;i<NUM_NUMEROS;i++)
	{
		grupo=randomgrupo(0,0);
		e.numeros[i]=obtnumero((unsigned *) &result,grupo);
	}
	randomobjetivo(e);
}

void Cifras::generar_random_canalsur(TEnunciado &e) const
{
	unsigned result[4][7];
	int i;
	int n123=0;
	int grupo;

	mezclargr((unsigned *) &result);
	for (i=0;i<NUM_NUMEROS;i++)
	{
		grupo=randomgrupo(n123,i+1);
		e.numeros[i]=obtnumero((unsigned *) &result,grupo);
		if (grupo<4)
			n123++;
	}
	randomobjetivo(e);
}

void Cifras::generar_random_1_100(TEnunciado &e) const
{
	int i;

	for (i=0;i<NUM_NUMEROS;i++)
	{
		e.numeros[i]=random(100)+1;
	}
	randomobjetivo(e);
}

Numero *Cifras::resolver(TEnunciado &e) const
{
	Resuelve r;

	r.resolver(e);

	return r.getSolucion();
}
