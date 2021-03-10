#if !defined(__CIFRAS_H)

#define	__CIFRAS_H

#define	NUM_NUMEROS	6

typedef struct _TEnunciado
{
	unsigned numeros[6];
   unsigned objetivo;
} TEnunciado;

class Cifras
{
	public:
		static const char *numerosTV[];

      void generar_random_tv(TEnunciado &e) const;
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
};

#endif
