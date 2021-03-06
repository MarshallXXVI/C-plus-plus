/* Copyright 2022 */
//  HeatMapMain.cpp
//  Clang
//
//  Created by Paramie Willmann on 30.06.22.
//

#include <string>
#include <iostream>
#include "./HeatMap.h"
#include "./TerminalManager.h"

int main() {
  std::cout << "Enter file.tsv name: ";
  std::string input;
  std::cin >> input;
  TerminalManager tm;
  HeatMap hm;
  hm.readPointsFromFile(input);
  hm.computeHeatMap(tm.numRows(), tm.numCols());
  hm.drawHeatMap(&tm);
}
