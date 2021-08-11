
#ifndef _OBJECT_H
#define _OBJECT_H

//-----------------------------------------------------------------------------------------
// class Object
//
// @brief  Ancestor class for all other classes.
//

class Object{

	public:

		Object(const char *pTag);

		virtual void init();

		const char *getTag();

		virtual ~Object();

	protected:

		const char *tag;

};// end of class Object  
//-----------------------------------------------------------------------------------------

#endif // _OBJECT_H
