#ifndef MINCUT_H
#define MINCUT_H

#include <iostream>
#include <random>
#include <stdint.h>
#include <list>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <boost/algorithm/string.hpp>

using namespace std;

class Graph
{
public:
	Graph()
	{
	}

	void ReadFromString(const string& input)
	{
		istringstream stream(input);
		Read(stream);
	}

	void ReadFromFile(const string& fileName)
	{
		std::ifstream input(fileName);
		for (std::string line; std::getline(input, line);)
		{
			Vertex v;
			vector<string> nodes;
			boost::split(nodes, line, boost::is_any_of("\t "));

			for (int index = 1; index < nodes.size() - 1; ++index)
			{
				v.links.push_back(stoi(nodes[index]));
			}

			m_vertexes.insert(std::make_pair(stoi(nodes[0]), v));
		}
	}

	void Print(ostream& stream) const
	{
		for (auto& vertex : m_vertexes)	
		{
			stream << vertex.first;
			for (auto& link : vertex.second.links)
				stream << " " << link;
			stream << endl;
		}
	}

	// deleting edge between lIndex and rIndex
	// deleting node at lIndex
	// replacing links in other edges to rIndex
	void ContractEdge(uint32_t lIndex, uint32_t rIndex)
	{
		auto& lLinks = m_vertexes[lIndex].links;
		std::list<uint32_t> probablySelfLoops = m_vertexes[lIndex].links;
		auto toRemove = std::find(lLinks.begin(), lLinks.end(), rIndex);
		auto& links = m_vertexes[*toRemove].links;
		auto it = std::find(links.begin(), links.end(), lIndex);
		
		if (it == links.end())
		{
			cout << lIndex << " " << rIndex << endl;
			Print(cout);
			throw std::runtime_error("bad find");	
		} 

		links.erase(it);
		lLinks.erase(toRemove);

		for (auto llink : lLinks)
		{
			auto& links = m_vertexes[llink].links;
			auto value = std::find(links.begin(), links.end(), lIndex);			
			*value = rIndex;
			m_vertexes[rIndex].links.push_back(llink);
		}

		m_vertexes.erase(lIndex);

		// remove self loops
		probablySelfLoops.unique();
		for (auto link : probablySelfLoops)
		{
			auto& links = m_vertexes[link].links;
			links.remove(link);
		}
		
	}

	size_t GetMinCut() const
	{
		if (GetSize() != 2)
		{
			Print(cout);
			throw std::runtime_error("size != 2");
		}

		auto it1 = m_vertexes.begin(), it2 = m_vertexes.begin();
		it2++;

		if (it1->second.links.size() != it2->second.links.size()) 
		{
			Print(cout);
			throw std::runtime_error("links size not equal");
		}

		return it1->second.links.size();
	}

	size_t GetSize() const
	{
		return m_vertexes.size();
	}

	uint32_t GetNodeByIndex(int index) const
	{
		int temp = 0;
		for (auto it = m_vertexes.begin(); it != m_vertexes.end(); ++it)
		{
			if (temp == index)
				return it->first;
			temp += 1;
		}

		cout << index << endl;
		Print(cout);
		throw std::runtime_error("wrong index 1"); 
		return 0;
	}

	size_t GetEdgeSizeByKey(uint32_t key)
	{
		return m_vertexes[key].links.size();
	}

	uint32_t GetEdgeByIndex(uint32_t key, int index)
	{
		int temp = 0;
		for (auto it = m_vertexes[key].links.begin(); it != m_vertexes[key].links.end(); ++it)
		{
			if (temp == index)
				return *it;
			temp += 1;
		}

		cout << key << " " << index << endl;
		Print(cout);
		throw std::runtime_error("wrong index 2"); 
	}

private:
	void Read(istream& input)
	{
		for (std::string line; std::getline(input, line);)
		{
			Vertex v;
			vector<string> nodes;
			boost::split(nodes, line, boost::is_any_of("\t "));

			for (int index = 1; index < nodes.size(); ++index)
				v.links.push_back(stoi(nodes[index]));

			m_vertexes.insert(std::make_pair(stoi(nodes[0]), v));
		}
	}

	void split(const string &s, char delim, vector<string> &elems) 
	{
		stringstream ss(s);
		string item;
		while (getline(ss, item, delim)) {
			elems.push_back(item);
		}
	}

	struct Vertex
	{
		list<uint32_t> links;
	};

	std::map<uint32_t, Vertex> m_vertexes;
};


#endif // MINCUT_H