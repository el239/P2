//
//  sequence.hpp
//  k-assembler
//
//  Created by Joe Song on 12/14/15.
//  Copyright © 2015 Joe Song. All rights reserved.
//

#ifndef sequence_h
#define sequence_h

#include <string>
#include <vector>

using namespace std;

string random_DNA_sequence(size_t min_length=10, size_t max_length=10000);

vector<string> get_kmers(string seq, size_t k, bool randomized=true);

bool compare_spectrum(const string & s1, const string & s2, size_t k);

#endif /* sequence_h */
