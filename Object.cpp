//-----------------------------------------------------------------------------------------
// Object.cpp
//
//

#include "Object.h"

//-----------------------------------------------------------------------------------------
// class Object
//
// The ancestor class for all other classes.
// All classes should be descendants of Object.
//
//

const char *type;
const char *tag;

//-----------------------------------------------------------------------------------------
// Object::Object (constructor)
//

Object::Object(const char *pType, const char *pTag){

	type = pType;
	tag = pTag;

}// end of Object::Object (constructor)
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// Object::init
//
// top-level init that handles basic initialization
// called after instantiation to complete setup.
//

void Object::init(){

}// end of Object::init
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// Object::~Object (destructor)
//
// This is declared as virtual in the header file. Virtual methods should always be
// used when polymorphic behavior is to be used, such as when a pointer of the Base class
// type is used to delete the object. The virtual method will call the overriden method of
// the derived class. Non-virtual methods result in undefined behavior in this case.
//

Object::~Object(){


}// end of Object::~Object (destructor)
//-----------------------------------------------------------------------------------------


//end of class Object
//-----------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------
