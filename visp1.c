#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define debug(m,e) printf("%s:%d: %s:",__FILE__,__LINE__,m); printObject(e,1); puts("");
typedef struct List {
  struct List * next;
  void * data;
} List;
List *symbols = 0;
static int lookahead; /* look ahead character */
#define TOKENMAX  32
static char token[TOKENMAX]; /* token */
int isSpace(char x)  { return x == ' ' || x == '\n'; }
int isParens(char x) { return x == '[' || x == ']'; }

static void getToken() {
  int index = 0;
  while(isSpace(look)) { look = getchar(); }
  if (isParens(look)) {
    token[index++] = lookahead;  lookahead = getchar();
  } else {
    while(index < TOKENMAX - 1 && lookahead != EOF && !isSpace(lookahead) && !isParens(lookahead)) {
      token[index++] = lookahead;  lookahead = getchar();
    }
  }
  token[index] = '\0';
}

#define isPair(x) (((uintptr_t)x & 0x1) == 0x1)  /* tag pointer to pair with 0x1 (alignment dependent)*/
#define isAtom(x) (((uintptr_t)x & 0x1) == 0x0)
#define untag(x)   ((uintptr_t) x & ~0x1)
#define tag(x)     ((uintptr_t) x | 0x1)
#define car(x)     (((List*)untag(x))->data)
#define cdr(x)     (((List*)untag(x))->next)
#define e_true     cons( putSymbol("quote"), cons( putSymbol("t"), 0))
#define e_false    0

List * cons(void *_car, void *_cdr) {
  List *_pair = calloc( 1, sizeof (List) );
  _pair->data = _car;
  _pair->next = _cdr;
  return (List*) tag(_pair);
}

void *putSymbol(char *sym) {
  List *_pair = symbols;
  for ( ; _pair ; _pair = cdr(_pair))
    if (strncmp(sym, (char*) car(_pair), 32)==0) return car(_pair);
  symbols = cons(strdup(sym), symbols);
  return car(symbols);
}

List * getList();

void * getObjectect() {
  if (token[0] == '(') return getList();
  return putSymbol(token);
}

List * getList() {
  List *tmp;
  getToken();
  if (token[0] == ')') return 0;
  tmp = getObjectect();
  return cons(tmp, getList());
}

void printObject(List *ob, int head_of_list) {
  if (!isPair(ob) ) {
    printf("%s", ob ? (char*) ob : "null" );
  } else {
    if (head_of_list) printf("(");
    printObject(car(ob), 1);
    if (cdr(ob) != 0) {
      printf(" ");
      printObject(cdr(ob), 0);
    } else  printf(")");
  }
}

List *fcons(List *a)    {  return cons(car(a), car(cdr(a)));  }
List *fcar(List *a)     {  return car(car(a));  }
List *fcdr(List *a)     {  return cdr(car(a));  }
List *feq(List *a)      {  return car(a) == car(cdr(a)) ? e_true : e_false;  }
List *fpair(List *a)    {  return is_pair(car(a))       ? e_true : e_false;  }
List *fatom(List *a)    {  return isAtom(car(a))       ? e_true : e_false;  }
List *fnull(List *a)    {  return car(a) == 0           ? e_true : e_false; }
List *freadobj(List *a) {  look = getchar(); getToken(); return getObject();  }
List *fwriteobj(List *a){  printObj(car(a), 1); puts(""); return e_true;  }

List * eval(List *exp, List *env);

List * evalList(List *list, List *env) {
  /* http://cslibrary.stanford.edu/105/LinkedListProblems.pdf */
  List *head = 0, **args = &head;
  for ( ; list ; list = cdr(list) ) {
    *args = cons( eval(car(list), env) , 0);
    args = &( (List *) untag(*args) )->next;
  }
  return head;
}

List * applyPrimitive(void *primfn, List *args) {
  return ((List * (*) (List *)) primfn)  ( args );
}

List * eval(List *exp, List *env) {
  if (isAtom(exp) ) {
    for ( ; env != 0; env = cdr(env) )
      if (exp == car(car(env)))  return car(cdr(car(env)));
    return 0;
  } else if (isAtom( car (exp))) { /* special forms */
    if (car(exp) == putSymbol("quote")) {
      return car(cdr(exp));
    } else if (car(exp) == putSymbol("if")) {
      if (eval (car(cdr(exp)), env) != 0)
        return eval (car(cdr(cdr(exp))), env);
      else
        return eval (car(cdr(cdr(cdr(exp)))), env);
    } else if (car(exp) == putSymbol("lambda")) {
      return exp; /* todo: create a closure and capture free vars */
    } else if (car(exp) == putSymbol("apply")) { /* apply function to list */
      List *args = evalList (cdr(cdr(exp)), env);
      args = car(args); /* assumes one argument and that it is a list */
      return applyPrimitive( eval(car(cdr(exp)), env), args);
    } else { /* function call */
      List *primop = eval (car(exp), env);
      if (is_pair(primop)) { /* user defined lambda, arg list eval happens in binding  below */
        return eval( cons(primop, cdr(exp)), env );
      } else if (primop) { /* built-in primitive */
        return applyPrimitive(primop, evalList(cdr(exp), env));
      }
    }
  } else if (car(car(exp)) == putSymbol("lambda")) { /* should be a lambda, bind names into env and eval body */
    List *extenv = env, *names = car(cdr(car(exp))), *vars = cdr(exp);
    for (  ; names ; names = cdr(names), vars = cdr(vars) )
      extenv = cons (cons(car(names),  cons(eval (car(vars), env), 0)), extenv);
    return eval (car(cdr(cdr(car(exp)))), extenv);
  }
  puts("cannot evaluate expression");
  return 0;
}

int main(int argc, char *argv[]) {
  List *env = cons (cons(putSymbol("car"), cons((void *)fcar, 0)),
              cons (cons(putSymbol("cdr"), cons((void *)fcdr, 0)),
              cons (cons(putSymbol("cons"), cons((void *)fcons, 0)),
              cons (cons(putSymbol("eq?"), cons((void *)feq, 0)),
              cons (cons(putSymbol("pair?"), cons((void *)fpair, 0)),
              cons (cons(putSymbol("symbol?"), cons((void *)fatom, 0)),
              cons (cons(putSymbol("null?"), cons((void *)fnull, 0)),
              cons (cons(putSymbol("read"), cons((void *)freadobj, 0)),
              cons (cons(putSymbol("write"), cons((void *)fwriteobj, 0)),
              cons (cons(putSymbol("null"), cons(0,0)), 0))))))))));
  look = getchar();
getToken();
  printObj( eval(getObject(), env), 1 );
  printf("\n");
  return 0;
}
