#pragma once

#ifndef DEFAULT_BUFF_VECTOR_SZ
	#define DEFAULT_BUFF_VECTOR_SZ 50
#endif

#ifdef _DEBUG
	#include <cassert>
	#include <iostream>
	#include <iomanip>
	#include <cstring>
	
	using namespace std;
	
    #define IT_PER_LINE 8	
	#define WIDE_OUTPUT 9
#endif 

#include <cstdio>

namespace GOMA {
  
    //=====================================================================
    // Elemento de lista doblemente enlazada
    //=====================================================================

    class sll_item_t {
    public:

        sll_item_t* next_;
        sll_item_t* prev_;

    public:
        sll_item_t();
        sll_item_t(sll_item_t* prev, sll_item_t* next);

        virtual ~sll_item_t(void);

#ifdef _DEBUG
        virtual void write(std::ostream& os) {};
#endif
        virtual sll_item_t* copy(void) {return NULL;}
        virtual void clean(void) {}
    };

    //=====================================================================
    // Clase gestora de lista doblemente enlazada
    //=====================================================================

    class sll_t {
    public:
        sll_item_t* inicio_;
        sll_item_t* fin_;

        int size_;

    public:
        sll_t(void);
        sll_t(const sll_t& lista);
        virtual ~sll_t(void); // Elimina la lista pero no la información

        void push_back(sll_item_t*);
        sll_item_t* pop_front(void);
        sll_item_t* pop_back(void);

        bool empty(void);

        void remove(sll_item_t*);

        void clear(void); // Borra el sólo el nodo y no borra el dato
        void clean(void); // Borra el nodo y el dato
        void softClean(void); // Vacía la lista sin eliminar los nodos
        int size(void);

        void moveFrom(sll_t& lista); // Copia la lista y la vacía sin eliminar nodos
        void copyFrom(sll_t& lista); // Copia la lista

#ifdef _DEBUG
        void write(std::ostream& os);
#endif
    };
	
}