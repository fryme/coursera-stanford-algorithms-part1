#include <iostream>
#include <random>
#include <stdint.h>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

// Generates random between a and b
int GenerateRandom(int a, int b)
{
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist(a, b);
	return uniform_dist(e1);
}

class Graph
{
public:
	Graph(uint32_t nVertexes)
	{
		m_vertexes.resize(nVertexes);
	}

	Graph()
	{
	}

	void ReadFromString(const string& input)
	{
		istringstream stream(input);
		Read(stream);
	}

	void ReadFromFile(const string& fileName, uint32_t numberOfLines = 0)
	{
		if (numberOfLines != 0)
			m_vertexes.resize(numberOfLines);

		std::ifstream input(fileName);
		Read(input);
	}

private:
	void Read(istream& input)
	{
		for (std::string line; std::getline(input, line);)
		{
			//	line;
			//	arr.push_back();
			Vertex v;
			v.links.push_back(0);
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

	std::vector<Vertex> m_vertexes;
};

int main()
{
	Graph g;
	return 0;
}