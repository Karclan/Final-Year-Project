#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

//template class for components
//revise template classes


class Component
{
public:
	int getTag(){return myTag;};
protected:
	void setTag(int t){myTag = t;};
	int myTag;
};
#endif