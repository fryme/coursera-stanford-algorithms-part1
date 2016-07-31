#include <iostream>
#include <gtest/gtest.h>
#include "mincut.h"


using namespace std;

class ContractTest : public ::testing::Test
{

public:
	void SetUp()
	{
	}

	void TearDown()
	{
	}
};

const string input = "0 2 1\n1 2 0 2\n2 1 0 1\n";

TEST_F(ContractTest, ReadingFromStringSimpleTest) 
{
	Graph g;
	g.ReadFromString(input);
	stringstream s;
	g.Print(s);

	ASSERT_TRUE(s.str() == input);
}

TEST_F(ContractTest, ContractEdge20) 
{
	Graph g;
	g.ReadFromString(input);
	g.ContractEdge(2, 0);
	stringstream s;
	g.Print(s);
	
	const string rightAnswer = "0 1 1 1\n1 0 0 0\n";

	ASSERT_TRUE(rightAnswer == s.str());
}

TEST_F(ContractTest, ContractEdge01) 
{
	Graph g;
	g.ReadFromString(input);
	g.Print(cout);
	cout << endl;
	g.ContractEdge(0, 1);
	g.Print(cout);
}

TEST_F(ContractTest, ContractEdge10) 
{
	Graph g;
	g.ReadFromString(input);
	g.Print(cout);
	g.ContractEdge(1, 0);
	stringstream s;
	g.Print(s);
	
	g.Print(cout);
	const string rightAnswer = "0 2 2 2\n2 0 0 0\n";

	ASSERT_TRUE(rightAnswer == s.str());
}

TEST_F(ContractTest, ContractEdge02) 
{
	Graph g;
	g.ReadFromString(input);
	g.Print(cout);
	g.ContractEdge(0, 2);
	stringstream s;
	g.Print(s);
	
	g.Print(cout);
	const string rightAnswer = "1 2 2 2\n2 1 1 1\n";

	ASSERT_TRUE(rightAnswer == s.str());
}

TEST_F(ContractTest, ContractEdge21) 
{
	Graph g;
	g.ReadFromString(input);
	g.Print(cout);
	g.ContractEdge(2, 1);
	stringstream s;
	g.Print(s);
	
	g.Print(cout);
	const string rightAnswer = "0 1 1\n1 0 0\n";

	ASSERT_TRUE(rightAnswer == s.str());
}

TEST_F(ContractTest, ContractEdge12) 
{
	Graph g;
	g.ReadFromString(input);
	g.Print(cout);
	g.ContractEdge(1, 2);
	stringstream s;
	g.Print(s);
	
	g.Print(cout);
	const string rightAnswer = "0 2 2\n2 0 0\n";

	ASSERT_TRUE(rightAnswer == s.str());
}

// Generates random between a and b
int GenerateRandom(int a, int b)
{
	std::random_device r;
	std::default_random_engine e1(r());
	std::uniform_int_distribution<int> uniform_dist(a, b);
	
	return uniform_dist(e1);
}

int CalculateMinCut(Graph& g)
{
	while (g.GetSize() != 2)
	{
		size_t size = g.GetSize();
		int r1 = GenerateRandom(1, size);	
		uint32_t node = g.GetNodeByIndex(r1-1);
		size_t edgeSize = g.GetEdgeSizeByKey(node);
		int r2 = GenerateRandom(1, edgeSize);
		//cout << "r2: " << node << " " << edgeSize << " " << r2 << endl;
		g.ContractEdge(node, g.GetEdgeByIndex(node, r2-1));
	}
	return g.GetMinCut();
}

TEST(MincutTest, MTSmall)
{
	Graph g;
	g.ReadFromString(input);
	CalculateMinCut(g);
}

TEST(MincutTest, MTBig)
{
	Graph g;
	g.ReadFromFile("..//artefacts//_f370cd8b4d3482c940e4a57f489a200b_kargerMinCut.txt");
	CalculateMinCut(g);
}

TEST(MincutTest, MTBigRun50Times)
{
	vector<int> results;
	int counter(0);
	while(counter != 50)
	{
		Graph g;
		g.ReadFromFile("..//artefacts//_f370cd8b4d3482c940e4a57f489a200b_kargerMinCut.txt");
		results.push_back(CalculateMinCut(g));
		counter ++;
	}
	sort(results.begin(), results.end());
	cout << "Result: " << results[0] << endl;
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}