#ifndef _SCC_H_
#define _SCC_H_

#include <stdint.h>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <sstream>
#include <fstream>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>

#define CHECK_AND_THROW(expression, text) if (!expression) throw std::runtime_error(text);

class DirectedGraph
{
	typedef uint32_t VertexId;
	struct Vertex
	{
		uint32_t id;
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
	
	DirectedGraph ReverseGraph(const std::vector<uint32_t>& newOrder)
	{
		DirectedGraph gRev;
		
		BOOST_FOREACH(const auto& v, m_vertexes)
		{
			Vertex vRev;
			std::cout << v.first << std::endl;
			int pos = (std::find(newOrder.begin(), newOrder.end(), v.first) - newOrder.begin());
			CHECK_AND_THROW(pos != newOrder.size(), "Out of border");
			vRev.id = pos;

			BOOST_FOREACH(const auto& link, v.second.links)
			{
				// v -> link, link -> v

			}
		}

		return gRev;
	}

	class DFSWalker
	{
	public:
		DFSWalker(const VertexArray& va) : m_vertexes(va) 
		{
			m_visitedVertexes = GetAllNodesAsUnvisited();
			m_newOrder.resize(m_vertexes.size());
		}

		std::map<uint32_t, bool> GetAllNodesAsUnvisited()
		{
			std::map<uint32_t, bool> keys;
			BOOST_FOREACH(auto& vertex, m_vertexes)
				keys.insert(std::make_pair(vertex.first, false));
		}

		bool IsVertexVisited(uint32_t v)
		{
			BOOST_FOREACH(auto& vv, m_visitedVertexes)
				std::cout << "IsVisited: " << vv.first << " " << vv.second << std::endl;
			return m_visitedVertexes[v];
		};

		void SetVertexVisited(uint32_t v)
		{
			m_visitedVertexes[v] = true;
		};

		void Walk(std::vector<uint32_t>& newOrder)
		{
			m_newOrderCounter = 0;

			BOOST_FOREACH(const auto& vertex, m_vertexes)
			{
				if (!IsVertexVisited(vertex.first))
				{
					std::cout << "Walk " << vertex.first << std::endl;
					DFSWalk(vertex.second, 0);
				}
			}
			newOrder = m_newOrder;
			std::cout << "New order:";
			BOOST_FOREACH(const auto& n, m_newOrder)
			{
				std::cout << n << " ";
			}
			std::cout << std::endl;
		}

		void DFSWalk(const Vertex& vertex, uint32_t visitedLinks)
		{
			SetVertexVisited(vertex.id);

			BOOST_FOREACH(const auto& link, vertex.links)
			{
				std::cout << "DFSWalk " << link << std::endl;
				if (!IsVertexVisited(link))
				{
					DFSWalk(m_vertexes.at(link), visitedLinks);
				}
				else
				{
					visitedLinks++;
				}
			}
			m_newOrder[m_newOrderCounter++] = vertex.id;
		}
		uint32_t 				 m_newOrderCounter;

	private:
		const VertexArray& 			 m_vertexes;
		std::map<uint32_t, bool> m_visitedVertexes;
		std::vector<uint32_t> 	 m_newOrder;
	};

	void DFS(std::vector<uint32_t>& newOrder)
	{
		DFSWalker walker(m_vertexes);
		walker.Walk(newOrder);
	}

private:

	void Read(std::istream& input)
	{
		std::vector<std::string> nodes;
		nodes.resize(2);
		for (std::string line; std::getline(input, line);)
		{
			nodes.clear();
			boost::split(nodes, line, boost::is_any_of(" "));
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
				v.id = intTail;
				v.links.push_back(intHead);
				m_vertexes.insert(lb, VertexArray::value_type(intTail, v));    // Use lb as a hint to insert,
																// so it can avoid another lookup
			}
		}
	}
	
};

#endif // _SCC_H_
