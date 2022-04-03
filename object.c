#include <stdio.h>

#define sObjectRep 1
typedef char* Name;
typedef void* Type;
typedef void* Value;
int printError(char* m){
  printf ("Error= %s=\n",m);
  return 0;
}

#ifdef paObjectRep
typedef void** Object;
typedef Object object;
#define getAddress(o) ((void*) (&(o->)))
#endif 

#ifdef psObjectRep
typedef struct {
 Type type;
 Value value;

} sObject;
typedef sObject* Object;
typedef Object object;
#define setType(o,t) (o->type=(t))
#define setValue(o,t) (o->value=(t))

#define getType(o) (o->type)
#define getValue(o) (o->value)

 #define printObjectAddress(o) (printf("address=%p\n",getAddress(o)))
 #define printObjectType(o) (printf("type=%llu",getType(o,t)))
 #define printObjectValue(o) (printf("type=",getValue(o,v)))
#endif 

#ifdef sObjectRep
typedef struct {
 Type type;
 Value value;
} sObject;
typedef sObject Object;
typedef Object object;
#define setType(o,t) (o.type=(t))
#define setValue(o,t) (o.value=(t))

#define getType(o) (o.type)
#define getValue(o) (o.value)

#define getAddress(o) ((void*) (&(o)))
 #define printObjectAddress(o) (printf("%p ",getAddress(o)))
 #define printObjectType(o) (printf("%10llu ",getType(o)))
 #define printObjectValue(o) (printf("%10llu \n",(long long int)getValue(o)))
#endif 
#ifdef rObjectRep

typedef struct {
 Name  name;
 Type type;
 Value value;
} rObject; 
typedef rObject Object;
typedef Object object;
#define setType(o,t) (o->type=(t))
#define setValue(o,t) (o->value=(t))

#define setName(o,t) (o->name=(t))

#define getType(o) (o->type)
#define getValue(o) (o->value)

#define getName(o) (o->name)


#endif 

#ifdef pObjectRep
typedef void* Object;
typedef Object object;
#define setType(o,t) (o.type=(t))
#define setValue(o,t) (o.value=(t))
#define getType(o) (o->type)
#define getValue(o) (o->value)
#endif 




Object newObject(Type t, Value v){
 Object o;
 setType(o,t);
 setValue(o,v);
 return o;
}

typedef char* typeNameType;

Object deleteObject(Object o){
 return o;
}
Object printObject(Object o){
 printf("address                type value\n");
  printObjectAddress(o);
 printObjectType(o);
 printObjectValue(o);
 return o;
}
Object newType(typeNameType typeName){
 static Type typeCounter =(Type)1;
 Object o=newObject(typeCounter,typeName);

/* void* attributes[3];
 attributes[0]=(int)3;
 attributes[1]=(int)typeCounter;
 attributes[2]= (char*) type;
*/
 typeCounter=(Type)(((long long int)(typeCounter))+1);
 return o;  
}
Object Nat64;
Object nullObject;

Object newNat64(long long int a){
 
 return newObject(getType(Nat64),(void*)a);
}

int isNat64 (Object a){
 if (getType(a)==getType(Nat64)){
   return 1;

 }
 return 0;
}

Object addNat64 (Object a, Object b){
 long long int c;
  
 if (isNat64(a)){
 if (isNat64(b)){

 c=(long long int)(getValue(a) + (long long int)(getValue(b)));
  return newObject(getType(a),c);    
 } else {
  printError("is not Nat64");
  return (Object) nullObject;
 }

 } else {
  printError("is not Nat64");
 return (Object) nullObject;
 }

}

// fullprogablatrt introsp refl unlikepy,lisp,js
int main (int argc, char* args[]){
 Object o1;
 o1 = newType("String");
 
 Object a;
 Object b;
 Object c;
 Object Nat64;
 Object Null;
 Null=newType("Null");
 nullObject=newObject(getType(Null),NULL);
// printObject(o1); 
// printObject(newType("Int")); 
 printObject(Nat64=newType("Nat64")); 
// printObject(newType("Real")); 
 a=newNat64(10009);
 b=newNat64(2001);
 c=addNat64(a,b);
 printObject(a);
 printObject(b);
 printObject(c);
 printObject(Nat64);

 return 0;
}