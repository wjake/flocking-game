#include <gtest/gtest.h>
#include "Flocking.h"

Flocking flocking;

TEST(Flocking, ctor)
{
    flocking = Flocking(1.0f, 1.0f, 1.0f, 1.0f);
    EXPECT_FLOAT_EQ(flocking.m_cohesion_weight, 1.0f);
    EXPECT_FLOAT_EQ(flocking.m_alignment_weight, 1.0f);
    EXPECT_FLOAT_EQ(flocking.m_separation_weight, 1.0f);
    EXPECT_FLOAT_EQ(flocking.m_attraction_weight, 1.0f);
}

TEST(Flocking, cohesion)
{
    Entity entity({1, 1}, {0,0}, {16, 16}, 100, 1, 0.05f);

    std::vector<std::unique_ptr<Entity>> flock;
    flock.push_back(std::make_unique<Entity>(Vec2<float>(5, 5), Vec2<float>(), Vec2<float>(16, 16), 100, 1, 0.05f));
    
    Vec2<float> cohesion = flocking.cohesion(flock, entity);

    EXPECT_FLOAT_EQ(cohesion.m_x, 0.707107f);
    EXPECT_FLOAT_EQ(cohesion.m_y, 0.707107f);
}

TEST(Flocking, alignment)
{
    Entity entity({1, 1}, {0,0}, {16, 16}, 100, 1, 0.05f);

    std::vector<std::unique_ptr<Entity>> flock;
    flock.push_back(std::make_unique<Entity>(Vec2<float>(100, 100), Vec2<float>(), Vec2<float>(16, 16), 100, 1, 0.05f));
    
    Vec2<float> alignment = flocking.alignment(flock, entity);

    EXPECT_FLOAT_EQ(alignment.m_x, 0.0f);
    EXPECT_FLOAT_EQ(alignment.m_y, 0.0f);
}

TEST(Flocking, separation)
{
    Entity entity({1, 1}, {0,0}, {16, 16}, 100, 1, 0.05f);

    std::vector<std::unique_ptr<Entity>> flock;
    flock.push_back(std::make_unique<Entity>(Vec2<float>(100, 100), Vec2<float>(), Vec2<float>(16, 16), 100, 1, 0.05f));
    
    Vec2<float> separation = flocking.separation(flock, entity);
    
    EXPECT_FLOAT_EQ(separation.m_x, 0.0f);
    EXPECT_FLOAT_EQ(separation.m_y, 0.0f);
}

TEST(Flocking, attraction)
{
    Entity entity({1, 1}, {0,0}, {16, 16}, 100, 1, 0.05f);
    Vec2<float> attraction = flocking.attraction(entity, {5, 5});

    EXPECT_FLOAT_EQ(attraction.m_x, 0.70710677f);
    EXPECT_FLOAT_EQ(attraction.m_y, 0.70710677f);
}

TEST(Flocking, update)
{
    Entity entity({1, 1}, {0,0}, {16, 16}, 100, 1, 0.05f);

    std::vector<std::unique_ptr<Entity>> flock;
    flock.push_back(std::make_unique<Entity>(Vec2<float>(100, 100), Vec2<float>(), Vec2<float>(16, 16), 100, 1, 0.05f));
    
    flocking.update(flock, entity, 10);

    // TODO
}
