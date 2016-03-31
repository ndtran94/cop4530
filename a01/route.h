/*
 Name : Nhi Tran
 Course: COP4530
 Assignment #1
 Due Date: 01/30/2015
*/
#ifndef ROUTE_H
#define ROUTE_H

#include <iostream>
#include <string.h>
#include <vector>
#include <stdio.h>
void parse_BGS        ( std::string* , std::string*  );                // parse BGS # for ASPATH
void parse_ASPATH     ( std::string* , std::vector<std::string>* );    // parse ASPATH into vector elements
bool find_ASSET       ( std::vector<std::string>* );                   // search ASPATH special case: ASSET
void check_Neighbors  ( std::vector<std::string>* );
int count_Neighbors   ( std::vector<std::string>* );

#endif
