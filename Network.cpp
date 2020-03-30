/*
 * Network.cpp - this file contains the functions for the Network class in Network.h
 *
 * Sweetnam 28808
 *
 *  Created on: Nov 5, 2018
 *      Author: rivest
 */

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

#include "Network.h"


/** This method colors all vertices in the graph WHITE. */
void Network::whiten() {
	for (int i=0 ;i<m_NetworkSize; i++){
		m_Colors[i] = WHITE;
	}
}


/** Constructs a network given a list of IP addresses
 *
 * @param IPList	Array of strings of each server's IP
 *
  */
Network::Network(const vector<string>& IPList) {
	//Debug statement
	cout << "Building a network of " << IPList.size() << " servers" << endl;
	//Fix the network size
	m_NetworkSize = IPList.size();
	//Saves the server IPs
	m_Vertex2IP = IPList;
	//Allocate space for adjacency lists and colors
	//By default there are no connections, so all nullptr
	m_EdgeLists = new EdgeListNode*[m_NetworkSize];
	for (int i=0; i<IPList.size(); i++) {
		m_EdgeLists[i] = nullptr;
	}
	m_Colors = new color[m_NetworkSize];
	//Fill a hash table for fast search using IP
	for (int i=0; i<IPList.size(); i++) {
		m_IP2Vertex.insert({IPList[i], i});
	}
	//Color the graph white
	whiten();
}

/** Frees up all allocated memory. */
Network::~Network() {
	delete[] m_EdgeLists;
	delete[] m_Colors;
}

/** Number of servers in the network */
int Network::GetNetworkSize(){
	return m_NetworkSize;
}

/** This adds a connection between two computers based on their IPs
 *  (in the adjacency edge linked list).
 *
 *  Note that it will add the edge to the adjacency list of both servers.
 *
 * @param server1	IP of the server at one end
 * @param server2	IP of the server at the other end
 */
void Network::AddConnection(const string& server1, const string& server2){
	//Extract servers index from IPs
	int v1 =  m_IP2Vertex[server1];
	int v2 =  m_IP2Vertex[server2];
	//Debug statement
	cout << "Adding edge (" << server1 << "," << server2 << ")" << endl;
	//Add the edge v1 to s2
	EdgeListNode* edge1 = new EdgeListNode();
	edge1->v1 = v1;
	edge1->v2 = v2;
	edge1->next = m_EdgeLists[v1];
	m_EdgeLists[v1] = edge1;
	//Add the edge v2 to v1
	//Note that since this is in the adjacency list of v2, we flip the vs
	EdgeListNode* edge2 = new EdgeListNode();
	edge2->v1 = v2;//see!
	edge2->v2 = v1;//so the index adjacent to v2 is v1
	edge2->next = m_EdgeLists[v2];
	m_EdgeLists[v2] = edge2;
}

/** This method must search the graph, starting on the homeServer
 * vertex, for the shortest path (in numbers of connections) to
 * the targetServer (or destination).
 *
 *   When such a path is found, it should be in the following format:
 *   homeServer,IP(1),IP(2),IP(k-1),targetServer
 *   eg: net.findShortestPath("168.213.182.122","7.9.30.185")
 *   Correct output: 168.213.182.122,83.27.248.234,7.9.30.185
 *
 * @param homeServer	IP of the starting point
 * @param targetServer	IP of the destination server
 * @return a C++ string as described above
 */

string Network::FindShortestPath(const string& homeServer, const string& targetServer) {
	//You can use a queue... for breadth first search
	queue<int> myqueue;
	//You can use a stack... if you need to ;-)
	stack<string> mystack;
	//Don't forget to whiten the graph
	whiten();
	//I suggest you first convert the IP strings back into indexes
	int home = m_IP2Vertex[homeServer];
	int destination = m_IP2Vertex[targetServer];
	//Debug statement
	cout << "Finding fastest path from  " << home << " to " << destination << endl;

	int* distances = new int[m_NetworkSize];
	int* parents = new int[m_NetworkSize];
	for (int i=0; i<m_NetworkSize; i++) {
		distances[i] = -1;
		parents[i] = -2;
	}

    //push the homeserver into the search queue and update the distance, parent, and colour array
    distances[home] = 0;
	parents[home] = home;
	myqueue.push(home);

	int indexAt;            //contains the index for the IP address we are currently looking at
	indexAt = myqueue.front();
	//loop through going through breadth first search until all connections have been looked at.
	while(!myqueue.empty()){
	    indexAt = myqueue.front(); //update the index to the next index in the queue
        EdgeListNode* child = m_EdgeLists[indexAt];     //the child of the IP address we are looking at
        //loop through all the connections that the IP address we are looking at has
        while (child!=NULL) {
            //if the distance has not changed from initialization or is smaller than what was previously there update information
            if (distances[child->v2] > distances[indexAt] + 1 || distances[child->v2] == -1){
                distances[child->v2] = distances[indexAt] + 1;
                parents[child->v2] = indexAt;
                //if the connection has not been seen yet at it to the search queue and gray it out.
                if(m_Colors[child->v2] == WHITE){
                    m_Colors[child->v2] = GRAY;
                    myqueue.push(child->v2);
                }//if
            }//if
            //update to look at the next connection
            child = child->next;
        }//while
        //all children have been seen update colour of the address we were looking at and pop it out of the queue
        m_Colors[indexAt] = BLACK;
        myqueue.pop();
	}//while

	//push the path into a stack then pop it out into a new string, this will get the path in the right order
	string path;
	int at = destination;       //the index that we are looking at, start at destination loop through parent till home address
    for(int i=0; i <= distances[destination]; i++){
        mystack.push(m_Vertex2IP[at]);
        at = parents[at];
    }//for
    for(int i=0; i < distances[destination]; i++){
        path.append(mystack.top() + ",");
        mystack.pop();
    }//for
    //add the last IP address without the , at the end
    path.append(mystack.top());
    mystack.pop();

    //if the distance does not change this means a new path could not be determined
    if(distances[destination] == -1){
        return "Path from " + homeServer + " to " + targetServer + " not found!";
    } else {
        return "Path from " + homeServer + " to " + targetServer + " is\n" + path;
    }//else
}

