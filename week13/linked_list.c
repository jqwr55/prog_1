#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct Link {
    struct Link* prev;
    struct Link* next;
};
struct List {
    struct Link* first;
    struct Link* last;
};

// initialize lst to empty
void init(struct List* lst) {

    assert(lst);
    lst->first = NULL;
    lst->last = NULL;
}

// make a new empty list on free store
struct List* create() {

    struct List* list = (struct List*)malloc(sizeof(struct List));
    init(list);
    return list;
}

// free all elements of lst
void clear(struct List* lst) {

    assert(lst);
    struct Link* it = lst->first;
    while(it) {

        struct Link* next = it->next;
        free(it);
        it = next;
    }
    lst->first = NULL;
    lst->last = NULL;
}

// free all elements of lst, then free lst
void destroy(struct List* lst) {

    assert(lst);
    clear(lst);
    free(lst);
}

// add p at end of lst
void push_back(struct List* lst, struct Link* p) {

    assert(lst);
    struct Link* last = lst->last;
    if(last) {
        last->next = p;
        p->prev = last;
    }
    else {
        lst->first = p;
        p->prev = NULL;
    }

    lst->last = p;
    p->next = NULL;
}

// add p at front of lst
void push_front(struct List* lst, struct Link* p) {

    assert(lst);
    struct Link* first = lst->first;
    if(first) {
        first->prev = p;
        p->next = first;
    }
    else {
        p->next = NULL;
    }

    lst->first = p;
    p->prev = NULL;
}

// insert q before p in lst:
void insert(struct List* lst, struct Link* p, struct Link* q) {

    assert(lst);
    assert(p);
    assert(q);

    q->next = p;
    q->prev = p->prev;

    if(p->prev) {
        p->prev->next = q;
    }
    p->prev = p;
}

// remove p from lst
struct Link* erase(struct List* lst, struct Link* p) {

    assert(lst);
    if(p == NULL) return NULL;

    if(p == lst->first) {

        if(p->next) {

            lst->first = p->next;
            p->next->prev = NULL;
            return p->next;
        }
        else {

            lst->last = NULL;
            lst->last = NULL;
            return NULL;
        }
    }
    else if(p == lst->last) {

        if(p->prev) {
            lst->last = p->prev;
            p->prev->next = NULL;
        }
        else {
            lst->first = NULL;
            lst->last = NULL;
            return NULL;
        }
    }
    else {

        p->next->prev = p->prev;
        p->prev->next = p->next;
        return p->next;
    }
}

// return link n “hops” before or after p:
struct Link* advance(struct Link* p, int n) {

    struct Link* it = p;
    if(n > 0) {

        for(int i = 0; i != n; i++) {
            if(p->next == NULL) break;
            it = p->next;
        }
    }
    else if(n < 0) {

        for(int i = 0; i != n; i--) {
            if(p->prev == NULL) break;
            it = p->prev;
        }
    }

    return it;
}

struct Name {
    struct Link lnk;
    char* str;
};
struct Name* make_name(char* n) {

    struct Name* lnk = (struct Name*)malloc(sizeof(struct Name));
    lnk->lnk.next = NULL;
    lnk->lnk.prev = NULL;
    lnk->str = n;
    return lnk;
}

int main() {

    int count = 0;
    struct List names;
    struct Link* curr;
    // make a list
    init(&names);
    
    // make a few Names and add them to the list:
    push_back(&names,(struct Link*)make_name("Norah"));
    push_back(&names,(struct Link*)make_name("Annemarie"));
    push_back(&names,(struct Link*)make_name("Kris"));
    
    // remove the second name (with index 1):
    struct Link* middle = advance(names.first, 1);
    erase(&names, middle );
    free(middle);
       
    curr = names.first;
    // write out all names
    for (; curr != NULL; curr = curr->next ) {
        count++;
        printf("element %d: %s\n", count, ((struct Name*)curr)->str);
    }

    destroy(&names);

    return 0;
}