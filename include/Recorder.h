#ifndef RECORDER_H
#define RECORDER_H

#include <list>
#include <utility>
#include <windows.h>

class Recorder
{
public:
	Recorder();
	~Recorder();

	void RecordInput(const SDL_KeyboardEvent &event, LARGE_INTEGER liTime);
	const SDL_KeyboardEvent *PlayBack(LARGE_INTEGER liTime);
	void Clear();
	void ResetPlayback();
private:
	std::list<std::pair<SDL_KeyboardEvent, LARGE_INTEGER> > m_Events;
	std::list<std::pair<SDL_KeyboardEvent, LARGE_INTEGER> >::iterator m_Current;
	LARGE_INTEGER m_TimeElapsed;
	bool m_FirstPlayback;
};

#endif

