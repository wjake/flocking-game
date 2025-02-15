#include <gtest/gtest.h>
#include "Entity.h"

Entity entity;

TEST(Entity, ctor)
{
    // default constructor
    entity = Entity();
    EXPECT_EQ(entity.m_position.m_x, 0.0f);
    EXPECT_EQ(entity.m_position.m_y, 0.0f);
    EXPECT_EQ(entity.m_cur_health, 0);
    EXPECT_EQ(entity.m_max_health, 0);

    // custom constructor
    entity = Entity({1.0f, -1.0f}, {0, 0}, {16, 32}, 50, 10, 10);
    EXPECT_EQ(entity.m_position.m_x, 1.0f);
    EXPECT_EQ(entity.m_position.m_y, -1.0f);
    EXPECT_EQ(entity.m_cur_health, 50);
    EXPECT_EQ(entity.m_cur_health, 50);
}

TEST(Entity, damage)
{    
    // within bounds damage
    entity = Entity({0.0f, 0.0f}, {0, 0}, {16, 32}, 100, 10, 10);
    entity.damage(10);
    EXPECT_EQ(entity.m_cur_health, 90);

    // out of bounds damage
    entity = Entity({0.0f, 0.0f}, {0.0f, 0.0f}, {16, 32}, 100, 10, 10);
    entity.damage(110);
    EXPECT_EQ(entity.m_cur_health, 0);
}

TEST(Entity, heal)
{
    // within bounds heal
    entity = Entity({0.0f, 0.0f}, {0.0f, 0.0f}, {16, 32}, 100, 10, 10);
    entity.damage(10);
    entity.heal(5);
    EXPECT_EQ(entity.m_cur_health, 95);

    // out of bounds heal
    entity = Entity({0.0f, 0.0f}, {0.0f, 0.0f}, {16, 32}, 100, 10, 10);
    entity.damage(10);
    entity.heal(20);
    EXPECT_EQ(entity.m_cur_health, 100);
}

TEST(Entity, alive)
{
    entity = Entity({0.0f, 0.0f}, {0.0f, 0.0f}, {16, 32}, 100, 10, 10);
    EXPECT_TRUE(entity.alive());
    entity.damage(100);
    EXPECT_FALSE(entity.alive());
}
