#include "event_handler.h"

#include <gtest/gtest.h>

// Test of Hook
TEST(EventHandlerTest, Hook) {
  {
    warble::EventHandler event_handler;
    EXPECT_TRUE(event_handler.Hook(1, "registeruser"));
    EXPECT_TRUE(event_handler.Hook(2, "warble"));
  }
  {
    warble::EventHandler event_handler;
    EXPECT_TRUE(event_handler.Hook(1, "registeruser"));
    EXPECT_FALSE(event_handler.Hook(1, "warble"));  // Event type is used
  }
  {
    warble::EventHandler event_handler;
    EXPECT_FALSE(event_handler.Hook(1, "random"));  // Invalid function name
  }
  {
    warble::EventHandler event_handler;
    EXPECT_FALSE(event_handler.Hook(1, "random"));  // Invalid function name
    EXPECT_TRUE(event_handler.Hook(1, "warble"));
  }
}

// Test of Unhook
TEST(EventHandlerTest, Unhook) {
  {
    warble::EventHandler event_handler;
    EXPECT_TRUE(event_handler.Hook(1, "registeruser"));
    EXPECT_TRUE(event_handler.Unhook(1));
  }
  {
    warble::EventHandler event_handler;
    EXPECT_TRUE(event_handler.Hook(1, "registeruser"));
    EXPECT_FALSE(event_handler.Unhook(2));  // Does not exist
  }
  {
    warble::EventHandler event_handler;
    EXPECT_TRUE(event_handler.Hook(1, "registeruser"));
    EXPECT_TRUE(event_handler.Unhook(1));
    EXPECT_FALSE(event_handler.Unhook(1));  // Already removed
  }
}