//
//  EulerPath.cpp
//  k-assembler
//
//  Created by Joe Song on 11/23/15.
//  Copyright © 2015 Joe Song. All rights reserved.
//
//  Updated:
//  3/19/2018
//  4/6/2018

#include "k-assembler.hpp"
#include <iostream>

using namespace std;

size_t source(const DiGraph & g)
// Find a source node from g: the node has one more
// outgoing edge than incoming edge. When such a node
// does not exist, a value of the total number of nodes
// is returned.
{
    size_t i;
    
    for (i=0; i<g.m_nodes.size(); ++i) {
        if (g.m_nodes[i].m_outgoing.size()
            == g.m_nodes[i].m_num_of_incoming + 1) {
            break;
        }
    }
    return i;
}

size_t sink(const DiGraph & g)
// Find a source node from g: the node has one more
// outgoing edge than incoming edge. When such a node
// does not exist, a value of the total number of nodes
// is returned.
{
    size_t i;
    for (i=0; i<g.m_nodes.size(); ++i) {
        if (g.m_nodes[i].m_outgoing.size() + 1
            == g.m_nodes[i].m_num_of_incoming) {
            break;
        }
    }
    return i;
}


list<size_t> find_Eulerian_cycle(DiGraph & g)
// find an Eulerian cycle from graph g
{
    list <size_t> E_cycle; // main cycle
    
    // TO-DO: insert code to find Eulerian cycle represented
    //   as a list of node id.
    // E.g., 3 -> 2 -> 0 -> 3 -> 4 -> 1 -> 3 is a cycle on
    //   a graph with 5 nodes.
    
    // BEGIN your code here:
    
    // creates vector of references to nodes equal to those in the input
    vector<Node> & nodes = g.m_nodes;
    
    // puts starting node into the cycle
    E_cycle.push_back(0);
    
    // iterates through nodes in the cycle
    for (auto iterator = E_cycle.begin(); iterator != E_cycle.end(); ++iterator){
		
		// sets cursor to help navigate
        size_t cursor = *iterator;
        
        // catches outgoing node in variable
        auto & outgoing = nodes[cursor].m_outgoing;
        
        // if the node @ cursor element has at least one outgoing edge
        while (outgoing.size() > 0){
            
            // value for destination node            
            size_t next = outgoing.front();
            
            // loops connecting at cursor element
            list <size_t> loop;

            // erases edge to destination, and decrements incoming 
            outgoing.pop_front();
            nodes[next].m_num_of_incoming --;
            
            // for alternate edges
            loop.push_back(next);
            
            // while still behind the cursor element
            while (next != cursor){
                size_t current = next;
                
                // if the current node still has outgoing edges
                if (nodes[current].m_outgoing.size() > 0){
                    
                    // append data member for "next" node
                    next = nodes[current].m_outgoing.front();
                    
                    // remove the edge and decrement
                    nodes[current].m_outgoing.pop_front();
                    nodes[next].m_num_of_incoming --;
                    
                    // updates the loop
                    loop.push_back(next);
                    // iterates
                    current = next;
                    
                } // end if
            } // end while
            
            // error case
            if(next != cursor){
                throw "ERROR: finding Eulerian path failed!";
            } // end if
            
            // otherwise increment secondary iterator 
            // (so as not to lose track primary position)
            else {
                auto secondary_iterator = iterator;
                secondary_iterator ++;
                
                // pasting loop onto graph
                E_cycle.insert(secondary_iterator, loop.begin(), loop.end());
            } // end else
        } // end while
    } // end for
    
    // END your code above

    return E_cycle;
}

list<size_t> find_Eulerian_path(DiGraph & g)
// find an Eulerian path from graph g, assuming g has such a path
{
    list <size_t> path, cycle;
    	    
    size_t src = source(g);    // find the source node
    size_t dest = sink(g);     // find the sink node
    
    // In the special case graph with only cycles
    //   and no source nor sink, we choose node 0 as the
    //   start and end of the Eulerian path:
    src = src >= g.m_nodes.size() ? 0 : src;
    dest = dest >= g.m_nodes.size() ? 0 : dest;
    
    vector<Node> & nodes = g.m_nodes;

	// add an edge from the sink node to the source node
    nodes[dest].m_outgoing.push_back(src);
    
    // increase the incoming degree of the source node by one
    nodes[src].m_num_of_incoming ++;

    cycle = find_Eulerian_cycle(g);

    list<size_t>::iterator pos_src, pos_dest;
       
    for (pos_dest = cycle.begin(); pos_dest != cycle.end(); ++ pos_dest) {
        pos_src = pos_dest;
        pos_src ++;
        if(pos_src != cycle.end()) {
            if (*pos_src == src && *pos_dest == dest) {
                break;
            }
        } else {
            break;
        }
    }

    if (pos_src != cycle.end() && pos_dest != cycle.end()) {
        
        /*
        // remove the last element on the cycle which is the same
        //   with the first element on the cycle:
        cycle.pop_back();
        
        // Formulate a path from the cycle such that src is
        //   the first and dest is the last on the path:
        path.splice(path.end(), cycle, pos_src, cycle.end());
        path.splice(path.end(), cycle, cycle.begin(), ++ pos_dest);
         */
        
        auto pos = pos_src;
        do {
            path.push_back(*pos);
            pos ++;
            if (pos == cycle.end()) {
                pos = cycle.begin();
                pos ++; // skip the first node in the cycle
                        // which is the same with the last
                        // last node in the cycle.
            }
        } while (pos != pos_src);
        
    } else {
        throw "Searching for Eulerian path has failed!";
    }
    // return the path
    return path;
}

bool has_Eulerian_path(const DiGraph & g)
// determine if graph g has an Eulerian path. This path could
//   be a cycle in special cases.
{
    bool exist = true;
    
    size_t numSources=0;
    size_t numSinks=0;
    
    for (auto & node : g.m_nodes) {
        size_t out = node.m_outgoing.size();
        size_t in = node.m_num_of_incoming;
        if(out == in) { // check for intermediate balanced node
            continue;
        } else if(out == in + 1) { // check for source node
            numSources ++;
            if (numSources > 1) {
                exist = false;
                break;
            }
        } else if(out + 1 == in) { // check for sink node
            numSinks ++;
            if (numSinks > 1) {
                exist = false;
                break;
            }
        } else {
            exist = false;
            break;
        }
    }
    
    return exist;
}


