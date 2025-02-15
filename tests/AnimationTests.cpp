#include <gtest/gtest.h>
#include "Animation.h"

std::unique_ptr<Animation> anim;

TEST(Animation, ctor)
{
    anim = std::make_unique<Animation>(0, 100, std::vector<Frame>{ {0, 128, 16, 32} });
    EXPECT_EQ(anim->m_curr_frame, 0);
    EXPECT_EQ(anim->m_frame_dur, 100);
    EXPECT_EQ(anim->m_frames.size(), 1);
    EXPECT_EQ(anim->m_frames[anim->m_curr_frame].m_x, 0);
    EXPECT_EQ(anim->m_frames[anim->m_curr_frame].m_y, 128);
    EXPECT_EQ(anim->m_frames[anim->m_curr_frame].m_w, 16);
    EXPECT_EQ(anim->m_frames[anim->m_curr_frame].m_h, 32);
}

TEST(Animation, update)
{
    anim = std::make_unique<Animation>(0, 0, std::vector<Frame>{
        {0, 128, 16, 32}, {0, 128, 16, 32}, {0, 128, 16, 32}
    });
    EXPECT_EQ(anim->m_curr_frame, 0);
    anim->update();
}
