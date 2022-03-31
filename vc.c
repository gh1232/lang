#include <stdio.h>

typedef void** object;
typedef struct {

}* Shell;

object newObject(){


}

object newType(char* type){
 

}


Shell newShell(){
 Shell s; 
  return s;
} 

int newRepl(){
 Interpreter i;

 i=evalute("");
 deleteInterpreter(i);
 return 0;
}
int main (int argc, char* args){
 Shell s;
 s=executeInShell("");
 deleteShell(s);
 return 0;
}