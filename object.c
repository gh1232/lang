#include <stdio.h>

#define sObjectRep 1
typedef char* nameType;
typedef void* typeType;
typedef void* valueType;
#ifdef paObjectRep
typedef void** objectType;
typedef objectType object;
#define getAddress(o) ((void*) (&(o->)))
#endif 

#ifdef psObjectRep
typedef struct {
 typeType type;
 valueType value;

} sObject;
typedef sObject* objectType;
typedef objectType object;
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
 typeType type;
 valueType value;
} sObject;
typedef sObject objectType;
typedef objectType object;
#define setType(o,t) (o.type=(t))
#define setValue(o,t) (o.value=(t))

#define getType(o) (o.type)
#define getValue(o) (o.value)

#define getAddress(o) ((void*) (&(o)))
 #define printObjectAddress(o) (printf("%p ",getAddress(o)))
 #define printObjectType(o) (printf("%10llu ",getType(o)))
 #define printObjectValue(o) (printf("%p \n",(valueType)getValue(o)))
#endif 
#ifdef rObjectRep

typedef struct {
 nameType  name;
 typeType type;
 valueType value;
} rObject; 
typedef rObject objectType;
typedef objectType object;
#define setType(o,t) (o->type=(t))
#define setValue(o,t) (o->value=(t))

#define setName(o,t) (o->name=(t))

#define getType(o) (o->type)
#define getValue(o) (o->value)

#define getName(o) (o->name)


#endif 

#ifdef pObjectRep
typedef void* objectType;
typedef objectType object;
#define setType(o,t) (o.type=(t))
#define setValue(o,t) (o.value=(t))
#define getType(o) (o->type)
#define getValue(o) (o->value)
#endif 




objectType newObject(typeType t, valueType v){
 objectType o;
 setType(o,t);
 setValue(o,v);
 return o;
}

typedef char* typeNameType;

objectType deleteObject(objectType o){
 return o;
}
objectType printObject(objectType o){
 printf("address                type value\n");
  printObjectAddress(o);
 printObjectType(o);
 printObjectValue(o);
 return o;
}
objectType newType(typeNameType typeName){
 static typeType typeCounter =(typeType)1;
 objectType o=newObject(typeCounter,typeName);

/* void* attributes[3];
 attributes[0]=(int)3;
 attributes[1]=(int)typeCounter;
 attributes[2]= (char*) type;
*/
 typeCounter=(typeType)(((long long int)(typeCounter))+1);
 return o;  
}
// fullprogablatrt introsp refl unlikepy,lisp,js
int main (int argc, char* args[]){
 objectType o1;
 o1 = newType("String");
 printObject(o1); 
 printObject(newType("Int")); 
 printObject(newType("Nat")); 
 printObject(newType("Real")); 
 return 0;
}