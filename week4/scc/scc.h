#ifndef _SCC_H_
#define _SCC_H_

#define CHECK_AND_THROW(expression, text) if (!expression) throw std::runtime_error(text);

class DirectedGraph
{
	typedef uint32_t VertexId;
	struct Vertex
	{
		list<VertexId> links;
	};

	typedef std::map<VertexId, Vertex> VertexArray;
	VertexArray m_vertexes;

public:
	DirectedGraph()
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

private:
	
	void Read(istream& input)
	{
		vector<string> nodes;
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
				v.links.push_back(intHead);
				m_vertexes.insert(lb, MapType::value_type(intTail, intHead));    // Use lb as a hint to insert,
																// so it can avoid another lookup
			}
		}
	}
	
};

#endif // _SCC_H_