#ifndef ARBOL_H
#define ARBOL_H

using namespace std;

struct NODO{ int info;
           NODO *izq, *der;
           NODO *pad;
           int ba;};
class ARBOL{NODO *raiz;
    int b;
public:	ARBOL( ){raiz=NULL;}
    NODO *raiz_arbol( ) {return raiz;}
    NODO *buscar_arbol(int n, NODO *p, NODO *q){
        if (p==NULL) return q;
        if (n < p->info){
            q=p;
            q=buscar_arbol(n,p->izq,q);
            return q;
        }else if (n > p->info) {
            q=p;
            q=buscar_arbol(n,p->der,q);
            return q;
        }else return NULL;
    }
    int ins_arbol(int n){
        b=0;
        NODO *q;
        if (raiz == NULL){
        raiz= new NODO;
        raiz->info =n;
        raiz->izq=raiz->der=NULL;
        raiz->pad=NULL;
        balanceado(raiz);
        return 0;}
        q =buscar_arbol(n,raiz,NULL);
        if (q==NULL) return -1;
        NODO *nuevo;
        nuevo= new NODO;
        nuevo->info = n;
        nuevo->izq=nuevo->der=NULL;
        if (n<q->info)
            q->izq=nuevo;
        else   q->der=nuevo;
        nuevo->pad=q;
        balanceado(nuevo);
        return 0;
    }
    void borrar_nodo (NODO *q, NODO *p){
        NODO  *r, *s,*t;
        if (p->izq==NULL) r=p->der;
        else if (p->der==NULL) r=p->izq;
        else {s =p;
            r=p->der;
            t=r->izq;
            while(t!=NULL){s=r; r=t; t=t->izq;}
            if (p!=s){
                s->izq=r->der;
                r->der=p->der; }
            r->izq =p->izq;
        }
        if (q==NULL) raiz= r;
        else if (p==q->izq) q->izq =r;
        else q->der = r;
        delete p;
    }
    NODO *buscar(int n, NODO **p, NODO *q){
        if (*p=NULL) return NULL;
        if (n <(*p)->info){
            q=*p;
	        *p=(*p)->izq;
	        q=buscar(n,p,q);
	        return q;}
        else if (n>(*p)->info){
            q=*p;
            *p=(*p)->der;
            q =buscar(n,p,q);
            return q;}
        else return q;
    }
    int retira_arbol(int n){
        NODO *q, *p=raiz;
        q=buscar(n,&p,NULL);
        if (p==NULL) return -1;
        borrar_nodo(q,p);
        return 0;}
	void inorden(NODO *p){
        if (p!=NULL){
        inorden(p->izq);
        cout<<p->info<<endl;
        inorden(p->der);}}
	void preorden(NODO *p){
        if (p!=NULL){
        cout<<p->info<<endl;
        preorden(p->izq);
        preorden(p->der);}}
	void posorden(NODO *p){
        if (p!=NULL){
        posorden(p->izq);
        posorden(p->der);
       cout<<p->info<<endl; }}
	void destruir(NODO *p){
        if (p!=NULL){
        destruir(p->izq);
        destruir(p->der);
        delete p;
        cout<<"Nodo destruido..."<< endl;}}
    int nivel(NODO *p){
        if(p==NULL){
            return 0;
        }else if(p->der==NULL&&p->izq==NULL){
            return 1;
        }else if(p->der!=NULL&&p->izq==NULL){
            return 1+ nivel(p->der);
        }else if(p->der==NULL&&p->izq!=NULL){
            return 1+ nivel(p->izq);
        }else if(p->der!=NULL&&p->izq!=NULL){
            if(nivel(p->der)>nivel(p->der)){
                return 1+nivel(p->der);
            }else{
                return 1+nivel(p->izq);
            }
        }
    }
    NODO *rotD(NODO *p){
        int r=0;
        if(p->der==NULL){
            p->der=new NODO;
            p->der->info=p->info;
        }else{
            NODO *a= new NODO;
            a=p->der;
            p->der->info=p->info;
            p->der->der=new NODO;
            p->der->der=a;
            destruir(p->der->izq);
            destruir(a);
        }
        if(p->izq->der!=NULL){
            p->der->izq=p->izq->der;
            destruir(p->izq->der);
        }
        p->info=p->izq->info;
        p->izq=p->izq->izq;
        return p;
    }
    NODO *rotI(NODO *p){
        if(p->izq==NULL){
            p->izq=new NODO;
            p->izq->info=p->info;
        }else{
            NODO *a=new NODO;
            a=p->izq;
            p->izq->info=p->info;
            p->izq->izq=new NODO;
            p->izq->izq=a;
            destruir(p->izq->der);
            destruir(a);
        }
        if(p->der->izq!=NULL){;
            p->izq->der=p->der->izq;
            destruir(p->der->izq);
        }
        p->info=p->der->info;
        p->der=p->der->der;
        return p;
    }
    int balanceado(NODO *p){
        if(p->izq==NULL&&p->der==NULL&&p!=NULL){
            if(p->pad!=NULL){
                balanceado(p->pad);
            }else return 0;
        }else if(p->izq!=NULL&&p->der==NULL){
            if(nivel(p->izq)>1){
                if(nivel(p->izq->der)-nivel(p->izq->izq)<=0){
                    p=rotD(p);
                }else{
                    p->izq=rotI(p->izq);
                    p=rotD(p);
                }
                if(p->pad!=NULL){
                    balanceado(p->pad);
                }else return 0;
            }else if(nivel(p->izq)<=1 && p->pad!=NULL){
                balanceado(p->pad);
            }else return 0;
        }else if(p->izq==NULL&&p->der!=NULL){
            if(nivel(p->der)>1){
                if(nivel(p->izq->der)-nivel(p->izq->der)>=0){
                    p=rotI(p);
                }else{
                    p->der=rotD(p->der);
                    p=rotI(p);
                }
                if(p->pad!=NULL){
                    balanceado(p->pad);
                }else return 0;
            }else if(nivel(p->der)<=1 && p->pad!=NULL){
                balanceado(p->pad);
            }else return 0;
        }else if(p->izq!=NULL&&p->der!=NULL){
            if(nivel(p->der)-nivel(p->izq)<-1){
                if(nivel(p->izq->der)-nivel(p->izq->der)<=0){
                    p=rotD(p);
                }else{
                    p->izq=rotI(p->izq);
                    p=rotD(p);
                }
                if(p->pad!=NULL){
                    balanceado(p->pad);
                }else return 0;
            }else if(nivel(p->der)-nivel(p->izq)>1){
                if(nivel(p->izq->der)-nivel(p->izq->der)>=0){
                    p=rotI(p);
                }else{
                    p->der=rotD(p->der);
                    p=rotI(p);
                }if(p->pad!=NULL){
                    balanceado(p->pad);
                }else return 0;

            }else if(p->pad!=NULL){
                balanceado(p->pad);
            }else return 0;
        }
    }
	~ARBOL( ) {destruir(raiz);}

};
#endif // ARBOL_H
