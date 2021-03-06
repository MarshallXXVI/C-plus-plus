/* Copyright 2022 */
//  HeatMapTest.cpp
//  Clang
//
//  Created by Paramie Willmann on 27.05.22.
//

#include <gtest/gtest.h>
#include <utility>
#include "./HeatMap.h"
#include "./TerminalManager.h"

// ____________________________________________________________________________
TEST(HeatMapTest, Readfile) {
    HeatMap hm1;
    hm1.readPointsFromFile("osm-test.tsv");
    // check if last Point is read.
    std::pair<float, float>LastPair = hm1.getLastPair();
    float last_x = LastPair.first;
    float last_y = LastPair.second;
    ASSERT_FLOAT_EQ(10, last_x);
    ASSERT_FLOAT_EQ(53.5547483, last_y);
    // check if first Point is read.
    std::pair<float, float>FirstPair = hm1.getFirstPair();
    float first_x = FirstPair.first;
    float first_y = FirstPair.second;
    ASSERT_FLOAT_EQ(10, first_x);
    ASSERT_FLOAT_EQ(53.6807170, first_y);
    // then all of point in file is read.
}

// ____________________________________________________________________________
TEST(HeatMapTest, ComputeHeatMap1) {
    // Test if max intensity was correct distributed.
    HeatMap hm2;
    hm2.readPointsFromFile("osm-test.tsv");
    hm2.computeHeatMap(50, 50);
    ASSERT_FLOAT_EQ(8, hm2.getMaxInt());
}

// ____________________________________________________________________________
TEST(HeatMapTest, ComputeHeatMap2) {
    HeatMap hm3;
    hm3.readPointsFromFile("osm-test.tsv");
    hm3.computeHeatMap(100, 100);
    ASSERT_FLOAT_EQ(5, hm3.getMaxInt());
}
