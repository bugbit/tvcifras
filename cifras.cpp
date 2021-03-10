#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include "cifras.h"

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
	for (i=0;i<6;i++)
	{
		grupo=randomgrupo(0,0);
      e.numeros[i]=obtnumero((unsigned *) &result,grupo);
	}
   e.objetivo=100+random(900);
}
