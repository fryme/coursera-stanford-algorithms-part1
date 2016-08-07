#ifndef _SCC_H_
#define _SCC_H_

#include <stdint.h>
#include <vector>
#include <list>
#include <map>
#include <sstream>
#include <fstream>

#define CHECK_AND_THROW(expression, text) if (!expression) throw std::runtime_error(text);

class DirectedGraph
{
	typedef uint32_t VertexId;
	struct Vertex
	{
		std::list<VertexId> links;
	};

	typedef std::map<VertexId, Vertex> VertexArray;
	VertexArray m_vertexes;

public:
	DirectedGraph()
	{
	}

	void ReadFromString(const std::string& input)
	{
		std::istringstream stream(input);
		Read(stream);
	}

	void ReadFromFile(const std::string& fileName)
	{
		std::ifstream input(fileName);
		for (std::string line; std::getline(input, line);)
		{
			Vertex v;
			std::vector<std::string> nodes;
			//boost::split(nodes, line, boost::is_any_of("\t "));

			for (int index = 1; index < nodes.size() - 1; ++index)
			{
				v.links.push_back(stoi(nodes[index]));
			}

			m_vertexes.insert(std::make_pair(stoi(nodes[0]), v));
		}
	}

	void Print(std::ostream& stream) const
	{
		for (auto& vertex : m_vertexes)
		{
			stream << vertex.first;
			for (auto& link : vertex.second.links)
				stream << " " << link;
			stream << std::endl;
		}
	}

	void DFS()
	{
		std::map<uint32_t, bool> visitedVertexes = GetAllNodes();
		visitedVertexes;
		m_vertexes;
		for each(auto& vertex in m_vertexes)
		{
			auto& links = vertex.second.links;
			for each (auto& link in links)
			{
				if (!visitedVertexes[link])
				{
					visitedVertexes[link] = true;
				}
			}
		}
		//visitedVertexes
	}

private:
	
	std::map<uint32_t, bool> GetAllNodes()
	{
		std::map<uint32_t, bool> keys;
		for each(auto& vertex in m_vertexes)
			keys.insert(std::make_pair(vertex.first, false));
	}

	void split(const std::string &s, char delim, std::vector<std::string> &elems)
	{
		std::stringstream ss(s);
		std::string item;
		while (getline(ss, item, delim)) {
			elems.push_back(item);
		}
	}

	void Read(std::istream& input)
	{
		std::vector<std::string> nodes;
		nodes.resize(2);
		for (std::string line; std::getline(input, line);)
		{
			nodes.clear();
			//boost::split(nodes, line, boost::is_any_of(" "));
			split(line, ' ', nodes);
			CHECK_AND_THROW(nodes.size() == 2, "More than two nodes given");
			
			auto& tail = nodes[0];
			auto& head = nodes[1];
			auto intTail = std::stoi(tail);
			auto intHead = std::stoi(head);

			VertexArray::iterator lb = m_vertexes.lower_bound(intTail);

			if (lb != m_vertexes.end() && !(m_vertexes.key_comp()(intTail, lb->first)))
			{
				// key already exists
				// update lb->second if you care to
				lb->second.links.push_back(intHead);
			}
			else
			{
				// the key does not exist in the map
				// add it to the map
				Vertex v;
				v.links.push_back(intHead);
				m_vertexes.insert(lb, VertexArray::value_type(intTail, v));    // Use lb as a hint to insert,
																// so it can avoid another lookup
			}
		}
	}
	
};

#endif // _SCC_H_