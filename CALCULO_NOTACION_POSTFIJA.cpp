#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct pila{
    int n;
    struct pila *Siguiente;
};

void ins_pila(struct pila **Nodo, int n);
struct pila *nuevoElemento();
int quitar_pila(struct pila **Nodo);
int vacia_pila(struct pila *Nodo);
int operacion(int n1, int n2, char caract);
void conversion(struct pila **Nodo, char cad[]);
void mostrar_pila(struct pila **Nodo);

int main()
{
    int res;
    struct pila *operandos=NULL;
    char expresion[15];
    printf("Digite la expresion separada por espacios: ");
    gets(expresion);
    printf("\n");
    conversion(&operandos, expresion);
    mostrar_pila(&operandos);
    res=quitar_pila(&operandos);
    printf("\nEl resultado de la expresion es: %d\n\n", res);

    system("pause");
    return 0;
}

struct pila *nuevoElemento()
{
    return (struct pila *)malloc(sizeof(struct pila));
}

void ins_pila(struct pila **Nodo, int n)
{
    struct pila *nuevo=NULL;
    nuevo=nuevoElemento();
    nuevo->n=n;
    nuevo->Siguiente=*Nodo;
    *Nodo=nuevo;
}

int quitar_pila(struct pila **Nodo)
{
    int n;
    struct pila *aux=NULL;
    n=(*Nodo)->n;
    aux=*Nodo;
    *Nodo=aux->Siguiente;
    free(aux);
    return n;
}


int vacia_pila(struct pila *Nodo)
{
    if(Nodo==NULL)
        return 0;
    return 1;
}

int operacion(int n1, int n2, char caract)
{
    int r;
    if(caract=='*')
        r= n1*n2;
    if(caract=='-')
        r= n1-n2;
    if(caract=='+')
        r= n1+n2;
    if(caract=='/')// verificar que n2 no sea 0
    {
        if(n2!=0)
            r= n1/n2;
    }
    return r;
}

void conversion(struct pila **Nodo, char cad[])
{
    int n1, n2, nuevo, i=0;
    while(cad[i]!='f'){
        if(cad[i]>='0' && cad[i]<='9') // es digito?
            ins_pila(Nodo, cad[i]-'0'); // convertir a entero antes de apilar
        if(cad[i]=='+' || cad[i]=='-' ||
           cad[i]=='*' || cad[i]=='/'){// es operacion?
            n2=quitar_pila(Nodo);
            n1=quitar_pila(Nodo);
            nuevo=operacion(n1, n2, cad[i]);
            ins_pila(Nodo, nuevo);
        }
        i++;
    }
}

void mostrar_pila(struct pila **Nodo)
{
    struct pila *aux=NULL;
    aux=*Nodo;
    while(aux!=NULL){
        printf("%d",aux->n);
        aux=aux->Siguiente;
    }
}
