#include <gtest/gtest.h>
#include "Prop.h"

TEST(Prop, ctor)
{
    Prop prop({1.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 1.0f});
    EXPECT_FLOAT_EQ(prop.m_position.m_x, 1.0f);
    EXPECT_FLOAT_EQ(prop.m_position.m_y, 1.0f);
    EXPECT_FLOAT_EQ(prop.m_velocity.m_x, 1.0f);
    EXPECT_FLOAT_EQ(prop.m_velocity.m_y, 1.0f);
    EXPECT_FLOAT_EQ(prop.m_size.m_x, 1.0f);
    EXPECT_FLOAT_EQ(prop.m_size.m_y, 1.0f);
}

TEST(Prop, collision)
{
    Prop prop_1({1.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 1.0f});
    Prop prop_2({5.0f, 5.0f}, {1.0f, 1.0f}, {1.0f, 1.0f});
    // Prop prop_3({1.0f, 1.0f}, {1.0f, 1.0f}, {1.0f, 1.0f});

    EXPECT_FALSE(prop_1.collision(prop_2));
    // EXPECT_TRUE(prop_1.collision(prop_3));
}
