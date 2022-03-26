


#include <stdio.h>

int main (int argc, char * args){
 Shell* s=newShell();
 runShell(s);
 deleteShell(s);
 return 0;
}
typedef struct {


} Shell;

Shell* newShell(){
 Shell* s; 
  return s;
} 

int newRepl(){
 Interpreter* i= newInterpreter();
 runInterpreter(i);
 deleteInterpreter(i);
 return 0;
}
