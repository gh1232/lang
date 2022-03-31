#include <stdio.h>

typedef char* nameType;
typedef void* typeType;
typedef void* valueType;
#ifdef paObject
typedef void** objectType;
typedef objectType object;
#define getAddress(o) ((void*) (&(o->)))
#endif 

#ifdef psObject
typedef {
 typeType type;
 valueType value;

} sObject;
typedef sObject objectType;
typedef objectType object;
#define setType(o,t) (o->type=(t))
#define setValue(o,t) (o->value=(t))

#define getType(o) (o->type)
#define getValue(o) (o->value)

 #define printObjectAddress(o) (printf("address=%p\n",getAddress(o)))
 #define printObjectType(o) (printf("type=%llu",getType(o,t)))
 #define printObjectValue(o) (printf("type=",getValue(o,v)))
#endif 

#ifdef sObject
typedef {
 typeType type;
 valueType value;
} sObject;
typedef sObject objectType;
typedef objectType object;
#define setType(o,t) (o.type=(t))
#define setValue(o,t) (o.value=(t))

#define getType(o) (o.type)
#define getValue(o) (o.value)

#endif 
#ifdef rObject

typedef {
 nameType  name;
 typeType type;
 valueType value;
} obj; 
typedef rObject objectType;
typedef objectType object;
#define setType(o,t) (o->type=(t))
#define setValue(o,t) (o->value=(t))

#define setName(o,t) (o->name=(t))

#define getType(o) (o->type)
#define getValue(o) (o->value)

#define getName(o) (o->name)


#endif 

#ifdef pObject
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
 objectType o;
 setType(o,t);
 setValue(o,v);
 return o;
}
objectType printObject(objectType o){

 printObjectAddress(o);
 printObjectType(o);
 printObjectValue(o);


 return o;
}
object newType(typeNameType typeName){
 static typeType typeCounter =(typeType)1;
 objectType o=newObject(typeCounter,typeName);

/* void* attributes[3];
 attributes[0]=(int)3;
 attributes[1]=(int)typeCounter;
 attributes[2]= (char*) type;
*/
 typeCounter=(typeType)(((long int)(typeCounter))+1);
 return o;  
}
// fullprogablatrt introsp refl unlikepy,lisp,js

int main (int argc, char* args){
 object object1;
 object1 = newType("String");
 
 return 0;
}