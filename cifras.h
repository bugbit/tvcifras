#if !defined(__CIFRAS_H)

#define	__CIFRAS_H

#define	NUM_NUMEROS	6

typedef struct _TEnunciado
{
	unsigned numero[6];
   unsigned objetivo;
} TEnunciado;

class Cifras
{
	public:
		static const char *numerosTV[];
	private:
   	static int grupos[][6];
};

#endif
