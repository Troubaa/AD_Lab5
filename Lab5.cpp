/** CSE250 Lab5 Main file.
 *  Assigned:  18 Mar 2020
 *  Due:  30 Mar 2020
 *
 * Sweetnam 28808
 *
 * In this lab, you will read a network description file
 * (consisting of server IPs and connection), create the corresponding
 * graph and find the shortest path between two given
 * servers by displaying the list of IP addresses on that path
 *
 * Note: Before you begin
 *          Add your name and ID in each file (and in the project name)
 * 			Read this code carefully.. very carefully.. you need to understand it
 *       	Read the Network1.txt file and draw the network on paper
 *       	Trace the code and variables to see how the graph works
 *       	Write your own findShortestPath method (based on breadth first search)
 *       	Initially, debug your method using IPs that are directly connected
 *
 *			In this lab, we will use C++ string instead of C const char*
 *			In this lab, we will use C++ vector which is like a resizable array
 *			In this lab, we will use C++ unordered_map which is a hash table
 *			In this lab, we will use C++ stack
 *			In this lab, we will use C++ queue
 *			In this lab, we will use an enum
 *			In this lab, you will program a singly linked list with only 'addfirst'
 *			In this lab, you will program your own graph (network) class
 *			In this lab, you will program breadth first search on a graph
 *
 *
 */

#include <iostream>		//general IO stream
#include <fstream>		//file IO stream
#include <sstream> 		//string IO stream
#include <vector>		//C++ vector ADT
#include <string>		//C++ string
using namespace std;

#include "Network.h"


/** This function split will help you convert each line of text into a list of IPs
 *  Solution 1.3 from https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
 *  Each line of the network file will have a comma delimited list of IP addresses.
 *
 *  It takes a line stored as a C++ string,
 *  breaks it down using delimiter, and
 *  returns it into a vector ADT
 */
vector<string> split(const string& s, char delimiter)
{
   vector<string> tokens;							//Vector to store each tokens
   string token;									//Temp token string variable
   istringstream tokenStream(s);					//Turn the string s into a stream
   while (getline(tokenStream, token, delimiter))  {//Read one token at a time
      tokens.push_back(token);						//Put it at the end of the vector
   }
   return tokens;									//Return the vector of tokens
}

int main() {

	//Open the file
	ifstream myfile;
	myfile.open("C:/Users/noahs/CLionProjects/28808_Lab5/AD_Lab5/Network1.txt");

	//Read the first line, and use it to create a disconnected network
	//A split method is provided for you above
	string line;
	getline(myfile, line);
	vector<string> split_line = split(line, ',');
	Network* net = new Network(split_line);

	//Read the file line by line in order to add the connections to the network object
	//The first IP on each line is a server IP
	//Each following IP on the same line is a server connected to the 1st IP of the line
    cout << endl << "Testing Question #1" << endl << endl;
    while (!myfile.eof()){
	    getline(myfile, line);          //grab the next line
	    split_line = split(line, ',');          //split the line into an array of strings
	    for(int i=1; i < split_line.size(); i++){           //loop through the array adding connections from the first IP address to the following ones
	        net->AddConnection(split_line[0], split_line[i]);
	    }//for
	}//while

	//Don't forget to close the file once your done
	myfile.close();

	cout << endl << "Testing Question #2" << endl << endl;
	//Answer the following Query, output the shortest path in IP order..
	cout << net->FindShortestPath("168.213.182.122","7.9.30.185") << endl << endl;
	//Correct output: 168.213.182.122,83.27.248.234,7.9.30.185
	cout << net->FindShortestPath("189.126.251.225", "150.220.177.120") << endl << endl;
	cout << net->FindShortestPath("189.126.251.225", "106.140.246.211") << endl << endl;
	cout << net->FindShortestPath("189.126.251.225", "102.130.212.124") << endl << endl;
	cout << net->FindShortestPath("189.126.251.225", "168.135.60.189") << endl << endl;

    //delete the network
    delete(net);

	return 0;
}
