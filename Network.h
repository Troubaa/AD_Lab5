/*
 * Network.h
 *
 * Sweetnam 28808
 *
 *  Created on: Nov 5, 2018
 *      Author: rivest
 */

#ifndef NETWORK_H_
#define NETWORK_H_

#include <string>
#include <vector>
#include <unordered_map>

/** This class is a node in the adjacency linked list of edges
 *  between a server and all the servers it is connected to
 */
struct EdgeListNode {
	/** This is the starting index (server or node) */
	int v1;
	/** This is the destination index. */
	int v2;
	/** This is a reference to the next connection in the list. */
	EdgeListNode* next;
};

/** List all possible colors using enums  */
enum color {WHITE, GRAY, BLACK};

/** Network object
 *
 *  All the information is stored using arrays where the index corresponds to a server
 *  vertex2IP contains the corresponding IP for a given server index
 *  IP2Vertex is a hash table allowing to quickly retrieve the index for a given server IP
 *
 *  @author Sweetnam 28808
 */
class Network {
private:

	/** This is the number of server on the network. */
	int m_NetworkSize;
	/** This is the array of adjacency singly-linked list of connected servers for each server.
	 *  Note that this is an array of pointer. */
	EdgeListNode** m_EdgeLists;
	/** This is the IP of each server. Can be used like an array.*/
	vector<string> m_Vertex2IP;
	/** This is the reverse mapping of IP to index in edgeLists and vertex2IP array.
	 *  Look at http://www.cplusplus.com/reference/unordered_map/unordered_map/insert/
	 *  and http://www.cplusplus.com/reference/unordered_map/unordered_map/operator[]/
	 *  for an example */
	std::unordered_map<std::string, int> m_IP2Vertex;
	/** Coloring variable for each server. */
	color* m_Colors;

	//Put any extra network variables you want here


	/** This method colors all vertices in the graph WHITE. */
	void whiten();

	//Put any extra private helper methods you want here


public:
	/** Constructs a network given a list of IP addresses */
	Network(const vector<string>& IPList);
	/** Frees up all allocated memory. */
	virtual ~Network();
	/** Number of servers in the network */
	int GetNetworkSize();
	/** Adds a connection between two servers */
	void AddConnection(const string& server1, const string& server2);
	/** Finds and returns the shortest path between two servers.*/
	string FindShortestPath(const string& homeServer, const string& targetServer);
};

#endif /* NETWORK_H_ */
