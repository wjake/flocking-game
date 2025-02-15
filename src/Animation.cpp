#include "Animation.h"

void Animation::update()
{
    /**
     * Compares (current time - last frame) with animation duration time
     * Progresses next frame if greater than animation duration
     */
    Uint32 current_time = SDL_GetTicks64();
    if (current_time - m_last_frame > m_frame_dur)
    {
        m_curr_frame = (m_curr_frame + 1) % m_frames.size();
        m_last_frame = current_time;
    }
}

void Animation::update(bool& io_state_flag)
{
    /**
     * Compares (current time - last frame) with animation duration time
     * Progresses next frame if greater than animation duration
     * Set io_state_flag to false if animation is complete
     */
    Uint32 current_time = SDL_GetTicks64();
    if (current_time - m_last_frame > m_frame_dur)
    {
        m_curr_frame++;
        if (m_curr_frame >= m_frames.size())
        {
            m_curr_frame = 0;
            io_state_flag = false;
        }
        m_last_frame = current_time;
    }
}