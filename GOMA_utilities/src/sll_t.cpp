#include "sll_t.hpp"

namespace GOMA {

    //=====================================================================
    // Elemento de lista doblemente enlazada
    //=====================================================================

    sll_item_t::sll_item_t() :
	next_(NULL),
    prev_(NULL)
	{
    }

    sll_item_t::sll_item_t(sll_item_t* prev, sll_item_t* next) :
    next_(next),
    prev_(prev) {
    }

    sll_item_t::~sll_item_t(void) {
        prev_ = NULL;
        next_ = NULL;
    }

    //=====================================================================
    // Clase gestora de lista doblemente enlazada
    //=====================================================================

    sll_t::sll_t(void) :
    inicio_(NULL),
    fin_(NULL),
    size_(0) {
    }

    sll_t::~sll_t(void) {

        clear();
    }

    sll_t::sll_t(const sll_t& lista) :
    inicio_(NULL),
    fin_(NULL),
    size_(0) {
    }

    void sll_t::clear(void) {

        sll_item_t* aux = NULL;

        while (inicio_ != NULL) {
            aux = inicio_;
            inicio_ = inicio_->next_;
            delete aux;
            aux = NULL;
        }
        size_ = 0;
        inicio_ = NULL;
        fin_ = NULL;
    }


    void sll_t::clean(void) {

        sll_item_t* aux = NULL;

        while (inicio_ != NULL) {
			
            aux = inicio_;
            inicio_ = inicio_->next_;
			
			if (aux){
				aux->clean();
				delete aux;				
			}
        }

        size_ = 0;
        inicio_ = NULL;
        fin_ = NULL;
    }
		

    void sll_t::softClean(void) {
        inicio_ = NULL;
        fin_ = NULL;
        size_ = 0;
    }

    void sll_t::moveFrom(sll_t& lista) {

        if (lista.inicio_ == NULL)
            return;

        if (inicio_ == NULL) {

#ifdef _DEBUG
            assert(fin_ == NULL);
#endif
            inicio_ = lista.inicio_;
            fin_ = lista.fin_;

        } else {
            fin_->next_ = lista.inicio_;
            fin_ = lista.fin_;
        }

        size_ += lista.size_;

        lista.softClean();

    }

    void sll_t::copyFrom(sll_t& lista) {

        if (lista.inicio_ == NULL)
            return;

        sll_item_t* l_aux = lista.inicio_;

        while (l_aux != NULL) {
            push_back(l_aux->copy());
            l_aux = l_aux->next_;
        }

    }
	

    void sll_t::push_back(sll_item_t* nodo) {

#ifdef _DEBUG
        assert(nodo != NULL);
#endif

        if (!inicio_) {
            inicio_ = nodo;
            fin_ = inicio_;
        } else {
            fin_->next_ = nodo;
            nodo->prev_ = fin_;
            fin_ = nodo;
        }

        size_++;
    }

    bool sll_t::empty(void) {
        return (inicio_ == NULL);
    }

    sll_item_t* sll_t::pop_front(void) {

#ifdef _DEBUG
        assert(inicio_ != NULL);
#endif

        sll_item_t* aux = inicio_;

        inicio_ = inicio_->next_;

        if (inicio_)
            inicio_->prev_ = NULL;
        else
            fin_ = NULL;

        size_--;

        return aux;
    }

    sll_item_t* sll_t::pop_back(void) {

#ifdef _DEBUG
        assert(fin_ != NULL);
#endif

        sll_item_t* aux = fin_;

        fin_ = fin_->prev_;

        if (fin_)
            fin_->next_ = NULL;
        else
            inicio_ = NULL;

        size_--;

        return aux;
    }

#ifdef _DEBUG
    void sll_t::write(std::ostream& os) {
		
        sll_item_t* aux = inicio_;

        while (aux != NULL) {
            aux->write(os);
            aux = aux->next_;
        }
    }
#endif

    void sll_t::remove(sll_item_t* nodo) {
		
#ifdef _DEBUG		
        assert(nodo != NULL);
#endif

        if (nodo->prev_ != NULL)
            nodo->prev_->next_ = nodo->next_;
        else
            inicio_ = nodo->next_;

        if (nodo->next_ != NULL)
            nodo->next_->prev_ = nodo->prev_;
        else
            fin_ = nodo->prev_;

        size_--;

    }

    int sll_t::size(void) {
        return size_;
    }


	
	
}