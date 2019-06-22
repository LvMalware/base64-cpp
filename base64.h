/*
 * base64.h
 */

#ifndef _BASE64_H
#define _BASE64_H 1

#include <iostream>

using std::string;

typedef unsigned long u64;

string
base64Encode(const string &str);

string
base64Decode(const string &str);

#endif