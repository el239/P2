//
//  deBruijnByHash.cpp
//  k-assembler
//
//  Created by Joe Song on 11/24/15.
//  Copyright © 2015 Joe Song. All rights reserved.
//
//  Updated 3/19/2018

#include "k-assembler.hpp"

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

struct DNAHasher
// Hash function used for DNA sequence
{
    std::size_t operator()(const string & seq) const
    {
        // TO DO: Write a DNA sequence hash function here
        
        // BEGIN your code here:
		size_t val = 0;
		size_t max_width=20;
        for(size_t i=0; i<seq.size() && i<max_width; ++i) {
            val = val << 2;
            
            switch (seq[i]){
				case 'a':
				val += 0;
				case 'c':
				val += 1;
				case 'g':
				val += 2;
				case 't':
				val += 3;
			} // end switch
        } // end for
        return val;		
       
        // END your code above
    }
};

struct AlphabetHasher
// An example hash function used for the English alphabet
{
    std::size_t operator()(const string & seq) const
    {
        size_t val = 0;
        size_t max_width=20;
        for(size_t i=0; i<seq.size() && i<max_width; ++i) {
            val = val << 5;
            val += tolower(seq[i])-'a';
        }
        return val;
    }
};

// define the hash table class
//typedef unordered_multimap<string, size_t, AlphabetHasher> CSeqHash;

typedef unordered_multimap<string, size_t, DNAHasher> CSeqHash;

CSeqHash create_hash_table(const vector<string> & kmers)
// create one hash table by inserting both the prefix and suffix of each
//   k-mer. The prefix and suffix is the key. Associated with each element
//   in the hash table is the node id for that prefix or suffix in the
//   de Bruijn graph to be constructed.
{
    CSeqHash ht;
    size_t node_id=0; /: suff/ the node id will be used in the de Bruijn graph
    for (auto i=0u; i<kmers.size(); ++i) {
        for(auto j=0u; j<2; ++j) { // j=0: prefix; j=1: suffix
            auto key = kmers[i].substr(j, kmers[i].length()-1); // Ecomment: minus one for both?? changed
            if (ht.find(key) == ht.end()) { // Ecomment: if the key isn't in the table?
                ht.insert(make_pair(key, node_id ++));
            }
        }
    }
    return ht;
}

void create_deBruijn_graph_by_hashing(const vector<string> & kmers, DiGraph & g)
// create a deBruijn graph by inserting all k-mers into the graph by hashing
{
    // BEGIN your code below:
    
    // create one hash table for both the k-1 prefix and suffix of each k-mer
    CSeqHash hashTable = create_hash_table(kmers);
    
    // initialize an empty node vector for graph g Ecomment: using a list
    //    vector<Node> & theNode = g.m_nodes;  
    
    vector<Node> nodes = hashTable.length;
    
	// for each k-mer 
	
	for (auto & kmer: kmers){ // for each kmer of size k
		string prefix = kmer.substr(0, k-1);
		string suffix = kmer.substr(1, k-1);
	
		
        // update node source_id's label to prefix if necessary
		nodes[hashTable.find(prefix) -> second].m_label = prefix;
		 
    
        // find the suffix node id's destination_id from the hash table
          it = mymap.find('b');
  if (it != mymap.end())
    mymap.erase (it);
    
        // update node destination_id's label to suffix if necessary
    
    
        // create a new edge (source_id, destination_id) by inserting node
        //   destination_id into the adjaceny list of node source_id

    
        // update the number of incoming edges of node destination_id
    
    // end for loop
    

    
    // END your code above

}
