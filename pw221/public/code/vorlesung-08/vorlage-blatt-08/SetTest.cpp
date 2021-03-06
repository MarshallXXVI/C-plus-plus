// Copyright 2022, University of Freiburg,
// Chair of Algorithms and Data Structures.
// Authors: Axel Lehmann <lehmann@cs.uni-freiburg.de>,
//          Claudius Korzen <korzen@cs.uni-freiburg.de>,
//          Johannes Kalmbach <kalmbach@cs.uni-freiburg.de>.

#include <limits.h>
#include <gtest/gtest.h>
#include "./Set.h"

// _____________________________________________________________________________
TEST(SetTest, insertAndEraseAndLookup) {
  Set<int> set;

  // Test if the set is empty.
  ASSERT_FALSE(set.lookup(0));
  ASSERT_FALSE(set.lookup(1));
  ASSERT_FALSE(set.lookup(INT_MIN));
  ASSERT_FALSE(set.lookup(INT_MAX));
  ASSERT_EQ(0u, set.size());

  // Insert element '0'.
  set.insert(0);
  ASSERT_TRUE(set.lookup(0));
  ASSERT_FALSE(set.lookup(1));
  ASSERT_FALSE(set.lookup(INT_MIN));
  ASSERT_FALSE(set.lookup(INT_MAX));
  ASSERT_EQ(1u, set.size());

  // Insert element '0' again. This should result in no change.
  set.insert(0);
  ASSERT_TRUE(set.lookup(0));
  ASSERT_FALSE(set.lookup(1));
  ASSERT_FALSE(set.lookup(INT_MIN));
  ASSERT_FALSE(set.lookup(INT_MAX));
  ASSERT_EQ(1u, set.size());

  // Insert element '1'.
  set.insert(1);
  ASSERT_TRUE(set.lookup(0));
  ASSERT_TRUE(set.lookup(1));
  ASSERT_FALSE(set.lookup(INT_MIN));
  ASSERT_FALSE(set.lookup(INT_MAX));
  ASSERT_EQ(2u, set.size());

  // Insert element 'INT_MIN'.
  set.insert(INT_MIN);
  ASSERT_TRUE(set.lookup(0));
  ASSERT_TRUE(set.lookup(1));
  ASSERT_TRUE(set.lookup(INT_MIN));
  ASSERT_FALSE(set.lookup(INT_MAX));
  ASSERT_EQ(3u, set.size());

  // Insert element 'INT_MAX'.
  set.insert(INT_MAX);
  ASSERT_TRUE(set.lookup(0));
  ASSERT_TRUE(set.lookup(1));
  ASSERT_TRUE(set.lookup(INT_MIN));
  ASSERT_TRUE(set.lookup(INT_MAX));
  ASSERT_EQ(4u, set.size());

  // Erase element '0'.
  set.erase(0);
  ASSERT_FALSE(set.lookup(0));
  ASSERT_TRUE(set.lookup(1));
  ASSERT_TRUE(set.lookup(INT_MIN));
  ASSERT_TRUE(set.lookup(INT_MAX));
  ASSERT_EQ(3u, set.size());

  // Erase element '0' again. This should result in no change.
  set.erase(0);
  ASSERT_FALSE(set.lookup(0));
  ASSERT_TRUE(set.lookup(1));
  ASSERT_TRUE(set.lookup(INT_MIN));
  ASSERT_TRUE(set.lookup(INT_MAX));
  ASSERT_EQ(3u, set.size());

  // Erase element 'INT_MIN'.
  set.erase(INT_MIN);
  ASSERT_FALSE(set.lookup(0));
  ASSERT_TRUE(set.lookup(1));
  ASSERT_FALSE(set.lookup(INT_MIN));
  ASSERT_TRUE(set.lookup(INT_MAX));
  ASSERT_EQ(2u, set.size());

  // Erase non-existing element '3'. This should result in no change.
  set.erase(3);
  ASSERT_FALSE(set.lookup(0));
  ASSERT_TRUE(set.lookup(1));
  ASSERT_FALSE(set.lookup(INT_MIN));
  ASSERT_TRUE(set.lookup(INT_MAX));
  ASSERT_EQ(2u, set.size());

  // Insert negative element '-1'.
  set.insert(-1);
  ASSERT_TRUE(set.lookup(-1));
  ASSERT_FALSE(set.lookup(0));
  ASSERT_TRUE(set.lookup(1));
  ASSERT_FALSE(set.lookup(INT_MIN));
  ASSERT_TRUE(set.lookup(INT_MAX));
  ASSERT_EQ(3u, set.size());
}
