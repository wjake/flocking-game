#include <gtest/gtest.h>
#include "Consumable.h"

Consumable consumable;

TEST(Consumable, ctor)
{
    consumable = Consumable(ConsumableType::HEALTH, Vec2<float>(0.0f, 0.0f));
    EXPECT_EQ(consumable.m_position.m_x, 0.0f);
    EXPECT_EQ(consumable.m_position.m_y, 0.0f);
    EXPECT_EQ(consumable.m_type, ConsumableType::HEALTH);

    consumable = Consumable(ConsumableType::POWER, Vec2<float>(1.0f, -1.0f));
    EXPECT_EQ(consumable.m_position.m_x, 1.0f);
    EXPECT_EQ(consumable.m_position.m_y, -1.0f);
    EXPECT_EQ(consumable.m_type, ConsumableType::POWER);
}
