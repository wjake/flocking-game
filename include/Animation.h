#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <vector>
#include <SDL2/SDL.h>

struct Frame
{
    int m_x, m_y, m_w, m_h;
};

class Animation
{
public:
    std::vector<Frame> m_frames;
    int m_curr_frame = 0;
    int m_frame_dur = 100;
    Uint32 m_last_frame = 0;

    /**
     * @brief Construct a new Animation object
     */
    Animation() = default;

    /**
     * @brief Construct a new Animation object
     * @param _curr_frame The current frame of the animation
     * @param _frame_dur The duration of each frame
     * @param _frames The frames of the animation
     * @return A new Animation object
     */
    Animation(const int _curr_frame, const int _frame_dur, const std::vector<Frame> _frames) :
        m_curr_frame(_curr_frame), m_frame_dur(_frame_dur), m_frames(_frames) {};
    
    /**
     * @brief Update the current frame of the animation
     */
    void update();

    /**
     * @brief Update the current frame of the animation
     * @param io_state_flag A flag to indicate the state of the animation
     */
    void update(bool& io_state_flag);
};

#endif