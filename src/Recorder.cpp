#include "SDL.h"
#include "Recorder.h"

Recorder::Recorder(): m_FirstPlayback(true)
{
	m_TimeElapsed.QuadPart = 0;
}

Recorder::~Recorder()
{
	m_Events.clear();
}

void Recorder::RecordInput(const SDL_KeyboardEvent &event, LARGE_INTEGER time)
{
	m_TimeElapsed.QuadPart += time.QuadPart;
	if(m_Events.empty() || event.type != m_Events.front().first.type || event.keysym.sym != m_Events.front().first.keysym.sym)
	{
		m_Events.push_back(std::pair<SDL_KeyboardEvent, LARGE_INTEGER>(event, m_TimeElapsed));
		m_TimeElapsed.QuadPart = 0;
	}
}

const SDL_KeyboardEvent *Recorder::PlayBack(LARGE_INTEGER time)
{
	if(m_FirstPlayback)
	{
		m_TimeElapsed.QuadPart = 0;
		m_FirstPlayback = false;
		m_Current = m_Events.begin();
	}
	m_TimeElapsed.QuadPart += time.QuadPart;

	if(m_Current != m_Events.end() && m_TimeElapsed.QuadPart > m_Current->second.QuadPart)
	{
		m_TimeElapsed.QuadPart = 0;//-= m_Current->second.QuadPart;
		++m_Current;
	}
	return m_Current == m_Events.end()?NULL:&m_Current->first;
}

void Recorder::Clear()
{
	m_Events.clear();
	m_TimeElapsed.QuadPart = 0;
	m_FirstPlayback = true;
}

void Recorder::ResetPlayback()
{
	m_TimeElapsed.QuadPart = 0;
	m_FirstPlayback = true;
}

