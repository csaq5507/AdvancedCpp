#ifndef __EVENT__
#define __EVENT__

struct Event {
	virtual void StartEvent() {};
	virtual void Execute() {};
};

#endif