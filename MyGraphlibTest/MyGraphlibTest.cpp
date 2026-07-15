#include "pch.h"
#include "CppUnitTest.h"
#include <string>
#include <vector>
#include "../MyGraph.h"
#include "../WeighedGraph.h"
#include "../CompleteGraph.h"
#include "../DirectedGraph.h"
#include "../CostGraph.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace P1
{
	TEST_CLASS(ZusammenhangsKomponenteTest)
	{
	public:
		TEST_METHOD(Graph1_2)
		{
			int expected = 2;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P1/Graph1.txt";
			MyGraph<Edge> graph(path);

			int result = graph.zusammenhagsKomp();

			string message = "Zusammenhangskomponenten: " + std::to_string(result);
			Logger::WriteMessage(message.c_str());
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(Graph2_4)
		{
			int expected = 4;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P1/Graph2.txt";
			MyGraph<Edge> graph(path);
			int result = graph.zusammenhagsKomp();

			string message = "Zusammenhangskomponenten: " + std::to_string(result);
			Logger::WriteMessage(message.c_str());
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(Graph3_4)
		{
			int expected = 4;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P1/Graph3.txt";
			MyGraph<Edge> graph(path);
			int result = graph.zusammenhagsKomp();

			string message = "Zusammenhangskomponenten: " + std::to_string(result);
			Logger::WriteMessage(message.c_str());
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(Graph_gross_222)
		{
			int expected = 222;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P1/Graph_gross.txt";
			MyGraph<Edge> graph(path);
			int result = graph.zusammenhagsKomp();

			string message = "Zusammenhangskomponenten: " + std::to_string(result);
			Logger::WriteMessage(message.c_str());
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(Graph_ganzgross_9560)
		{
			int expected = 9560;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P1/Graph_ganzgross.txt";
			MyGraph<Edge> graph(path);
			int result = graph.zusammenhagsKomp();

			string message = "Zusammenhangskomponenten: " + std::to_string(result);
			Logger::WriteMessage(message.c_str());
			Assert::AreEqual(expected, result);
		}

		TEST_METHOD(Graph_ganzganzgross_306)
		{
			int expected = 306;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P1/Graph_ganzganzgross.txt";
			MyGraph<Edge> graph(path);
			int result = graph.zusammenhagsKomp();

			string message = "Zusammenhangskomponenten: " + std::to_string(result);
			Logger::WriteMessage(message.c_str());
			Assert::AreEqual(expected, result);
		}
	};
}

namespace P2
{
	TEST_CLASS(PrimAlgorithmusTest)
	{
	public:
		TEST_METHOD(G_1_2_287_32286)
		{
			double expected = 287.32286;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P2/G_1_2.txt";
			WeighedGraph graph(path);
			double result = graph.primMST(0);

			string message = "Gewicht: " + std::to_string(result);
			Logger::WriteMessage(message.c_str());
			Assert::AreEqual(expected, result, 0.00001);
		}

		TEST_METHOD(G_1_20_36_86275)
		{
			double expected = 36.86275;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P2/G_1_20.txt";
			WeighedGraph graph(path);
			double result = graph.primMST(0);

			string message = "Gewicht: " + std::to_string(result);
			Logger::WriteMessage(message.c_str());
			Assert::AreEqual(expected, result, 0.00001);
		}

		TEST_METHOD(G_1_200_12_68182)
		{
			double expected = 12.68182;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P2/G_1_200.txt";
			WeighedGraph graph(path);
			double result = graph.primMST(0);

			string message = "Gewicht: " + std::to_string(result);
			Logger::WriteMessage(message.c_str());
			Assert::AreEqual(expected, result, 0.00001);
		}

		TEST_METHOD(G_10_20_2785_62417)
		{
			double expected = 2785.62417;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P2/G_10_20.txt";
			WeighedGraph graph(path);
			double result = graph.primMST(0);

			string message = "Gewicht: " + std::to_string(result);
			Logger::WriteMessage(message.c_str());
			Assert::AreEqual(expected, result, 0.00001);
		}

		TEST_METHOD(G_10_200_372_14417)
		{
			double expected = 372.14417;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P2/G_10_200.txt";
			WeighedGraph graph(path);
			double result = graph.primMST(0);

			string message = "Gewicht: " + std::to_string(result);
			Logger::WriteMessage(message.c_str());
			Assert::AreEqual(expected, result, 0.00001);
		}

		TEST_METHOD(G_100_200_27550_51488)
		{
			double expected = 27550.51488;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P2/G_100_200.txt";
			WeighedGraph graph(path);
			double result = graph.primMST(0);

			string message = "Gewicht: " + std::to_string(result);
			Logger::WriteMessage(message.c_str());
			Assert::AreEqual(expected, result, 0.00001);
		}
	};

	TEST_CLASS(KruskalAlgorithmusTest)
	{
	public:
		TEST_METHOD(G_1_2_287_323)
		{
			double expected = 287.32286;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P2/G_1_2.txt";
			WeighedGraph graph(path);
			double result = graph.kruskalMST();

			string message = "Gewicht: " + std::to_string(result);
			Logger::WriteMessage(message.c_str());
			Assert::AreEqual(expected, result, 0.00001);
		}

		TEST_METHOD(G_1_20_36_86275)
		{
			double expected = 36.86275;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P2/G_1_20.txt";
			WeighedGraph graph(path);
			double result = graph.kruskalMST();

			string message = "Gewicht: " + std::to_string(result);
			Logger::WriteMessage(message.c_str());
			Assert::AreEqual(expected, result, 0.00001);
		}

		TEST_METHOD(G_1_200_12_68182)
		{
			double expected = 12.68182;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P2/G_1_200.txt";
			WeighedGraph graph(path);
			double result = graph.kruskalMST();

			string message = "Gewicht: " + std::to_string(result);
			Logger::WriteMessage(message.c_str());
			Assert::AreEqual(expected, result, 0.00001);
		}

		TEST_METHOD(G_10_20_2785_62417)
		{
			double expected = 2785.62417;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P2/G_10_20.txt";
			WeighedGraph graph(path);
			double result = graph.kruskalMST();

			string message = "Gewicht: " + std::to_string(result);
			Logger::WriteMessage(message.c_str());
			Assert::AreEqual(expected, result, 0.00001);
		}

		TEST_METHOD(G_10_200_372_14417)
		{
			double expected = 372.14417;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P2/G_10_200.txt";
			WeighedGraph graph(path);
			double result = graph.kruskalMST();

			string message = "Gewicht: " + std::to_string(result);
			Logger::WriteMessage(message.c_str());
			Assert::AreEqual(expected, result, 0.00001);
		}

		TEST_METHOD(G_100_200_27550_51488)
		{
			double expected = 27550.51488;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P2/G_100_200.txt";
			WeighedGraph graph(path);
			double result = graph.kruskalMST();

			string message = "Gewicht: " + std::to_string(result);
			Logger::WriteMessage(message.c_str());
			Assert::AreEqual(expected, result, 0.00001);
		}
	};
}

string printHamiltonKreis(std::vector<int>& hk) {
	std::string message;

	for (int i = 0; i < hk.size(); i++) {
		if (i != 0)
			message += "->";
		message += std::to_string(hk[i]);
	}

	return message;
}

namespace P3
{
	TEST_CLASS(DoppelterBaumAlgorithmusTest)
	{
	public:
		TEST_METHOD(K_10)
		{
			double notExpected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_10.txt";
			CompleteGraph graph(path);
			auto result = graph.bestPath(&CompleteGraph::doppelterBaumAlg);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreNotEqual(notExpected, result.weight, 0.01);
		}

		TEST_METHOD(K_10e)
		{
			double notExpected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_10e.txt";
			CompleteGraph graph(path);
			auto result = graph.bestPath(&CompleteGraph::doppelterBaumAlg);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreNotEqual(notExpected, result.weight, 0.01);
		}

		TEST_METHOD(K_12)
		{
			double notExpected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_12.txt";
			CompleteGraph graph(path);
			auto result = graph.bestPath(&CompleteGraph::doppelterBaumAlg);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreNotEqual(notExpected, result.weight, 0.01);
		}

		TEST_METHOD(K_12e)
		{
			double notExpected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_12e.txt";
			CompleteGraph graph(path);
			auto result = graph.bestPath(&CompleteGraph::doppelterBaumAlg);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreNotEqual(notExpected, result.weight, 0.01);
		}

		TEST_METHOD(K_15)
		{
			double notExpected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_12.txt";
			CompleteGraph graph(path);
			auto result = graph.bestPath(&CompleteGraph::doppelterBaumAlg);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreNotEqual(notExpected, result.weight, 0.01);
		}

		TEST_METHOD(K_15e)
		{
			double notExpected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_12e.txt";
			CompleteGraph graph(path);
			auto result = graph.bestPath(&CompleteGraph::doppelterBaumAlg);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreNotEqual(notExpected, result.weight, 0.01);
		}

		TEST_METHOD(K_20)
		{
			double notExpected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_20.txt";
			CompleteGraph graph(path);
			auto result = graph.bestPath(&CompleteGraph::doppelterBaumAlg);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreNotEqual(notExpected, result.weight, 0.01);
		}

		TEST_METHOD(K_30)
		{
			double notExpected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_30.txt";
			CompleteGraph graph(path);
			auto result = graph.bestPath(&CompleteGraph::doppelterBaumAlg);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreNotEqual(notExpected, result.weight, 0.01);
		}

		TEST_METHOD(K_50)
		{
			double notExpected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_50.txt";
			CompleteGraph graph(path);
			auto result = graph.bestPath(&CompleteGraph::doppelterBaumAlg);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreNotEqual(notExpected, result.weight, 0.01);
		}

		TEST_METHOD(K_70)
		{
			double notExpected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_70.txt";
			CompleteGraph graph(path);
			auto result = graph.bestPath(&CompleteGraph::doppelterBaumAlg);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreNotEqual(notExpected, result.weight, 0.01);
		}

		TEST_METHOD(K_100)
		{
			double notExpected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_100.txt";
			CompleteGraph graph(path);
			auto result = graph.bestPath(&CompleteGraph::doppelterBaumAlg);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreNotEqual(notExpected, result.weight, 0.01);
		}
	};

	TEST_CLASS(NearestNeighbourAlgorithmusTest)
	{
	public:
		TEST_METHOD(K_10)
		{
			double notExpected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_10.txt";
			CompleteGraph graph(path);
			auto result = graph.bestPath(&CompleteGraph::nearestNeighbourAlg);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreNotEqual(notExpected, result.weight, 0.01);
		}

		TEST_METHOD(K_10e)
		{
			double notExpected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_10e.txt";
			CompleteGraph graph(path);
			auto result = graph.bestPath(&CompleteGraph::nearestNeighbourAlg);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreNotEqual(notExpected, result.weight, 0.01);
		}

		TEST_METHOD(K_12)
		{
			double notExpected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_12.txt";
			CompleteGraph graph(path);
			auto result = graph.bestPath(&CompleteGraph::nearestNeighbourAlg);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreNotEqual(notExpected, result.weight, 0.01);
		}

		TEST_METHOD(K_12e)
		{
			double notExpected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_12e.txt";
			CompleteGraph graph(path);
			auto result = graph.bestPath(&CompleteGraph::nearestNeighbourAlg);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreNotEqual(notExpected, result.weight, 0.01);
		}

		TEST_METHOD(K_15)
		{
			double notExpected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_12.txt";
			CompleteGraph graph(path);
			auto result = graph.bestPath(&CompleteGraph::nearestNeighbourAlg);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreNotEqual(notExpected, result.weight, 0.01);
		}

		TEST_METHOD(K_15e)
		{
			double notExpected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_12e.txt";
			CompleteGraph graph(path);
			auto result = graph.bestPath(&CompleteGraph::nearestNeighbourAlg);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreNotEqual(notExpected, result.weight, 0.01);
		}

		TEST_METHOD(K_20)
		{
			double notExpected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_20.txt";
			CompleteGraph graph(path);
			auto result = graph.bestPath(&CompleteGraph::nearestNeighbourAlg);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreNotEqual(notExpected, result.weight, 0.01);
		}

		TEST_METHOD(K_30)
		{
			double notExpected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_30.txt";
			CompleteGraph graph(path);
			auto result = graph.bestPath(&CompleteGraph::nearestNeighbourAlg);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreNotEqual(notExpected, result.weight, 0.01);
		}

		TEST_METHOD(K_50)
		{
			double notExpected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_50.txt";
			CompleteGraph graph(path);
			auto result = graph.bestPath(&CompleteGraph::nearestNeighbourAlg);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreNotEqual(notExpected, result.weight, 0.01);
		}

		TEST_METHOD(K_70)
		{
			double notExpected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_70.txt";
			CompleteGraph graph(path);
			auto result = graph.bestPath(&CompleteGraph::nearestNeighbourAlg);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreNotEqual(notExpected, result.weight, 0.01);
		}

		TEST_METHOD(K_100)
		{
			double notExpected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_100.txt";
			CompleteGraph graph(path);
			auto result = graph.bestPath(&CompleteGraph::nearestNeighbourAlg);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreNotEqual(notExpected, result.weight, 0.01);
		}
	};

	TEST_CLASS(VollstaendigeSucheTest)
	{
	public:
		TEST_METHOD(OhneBNB_K_10_38_41)
		{
			double expected = 38.41;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_10.txt";
			CompleteGraph graph(path);
			auto result = graph.completeSearch(0);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result.weight, 0.01);
		}

		TEST_METHOD(OhneBNB_K_10e_27_26)
		{
			double expected = 27.26;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_10e.txt";
			CompleteGraph graph(path);
			auto result = graph.completeSearch(0);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result.weight, 0.01);
		}

		TEST_METHOD(MitBNB1_K_10_38_41)
		{
			double expected = 38.41;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_10.txt";
			CompleteGraph graph(path);
			auto result = graph.completeSearch(1);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result.weight, 0.01);
		}

		TEST_METHOD(MitBNB1_K_10e_27_26)
		{
			double expected = 27.26;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_10e.txt";
			CompleteGraph graph(path);
			auto result = graph.completeSearch(1);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result.weight, 0.01);
		}

		TEST_METHOD(MitBNB1_K_12_45_19)
		{
			double expected = 45.19;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_12.txt";
			CompleteGraph graph(path);
			auto result = graph.completeSearch(1);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result.weight, 0.01);
		}

		TEST_METHOD(MitBNB1_K_12e_36_13)
		{
			double expected = 36.13;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_12e.txt";
			CompleteGraph graph(path);
			auto result = graph.completeSearch(1);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result.weight, 0.01);
		}

		TEST_METHOD(MitBNB2_K_10_38_41)
		{
			double expected = 38.41;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_10.txt";
			CompleteGraph graph(path);
			auto result = graph.completeSearch(2);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result.weight, 0.01);
		}

		TEST_METHOD(MitBNB2_K_10e_27_26)
		{
			double expected = 27.26;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_10e.txt";
			CompleteGraph graph(path);
			auto result = graph.completeSearch(2);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result.weight, 0.01);
		}

		TEST_METHOD(MitBNB2_K_12_45_19)
		{
			double expected = 45.19;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_12.txt";
			CompleteGraph graph(path);
			auto result = graph.completeSearch(2);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result.weight, 0.01);
		}

		TEST_METHOD(MitBNB2_K_12e_36_13)
		{
			double expected = 36.13;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P3/K_12e.txt";
			CompleteGraph graph(path);
			auto result = graph.completeSearch(2);

			std::string message = "Result: " + std::to_string(result.weight) + "\n";
			Logger::WriteMessage(message.c_str());
			message = "Path: " + printHamiltonKreis(result.path);
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result.weight, 0.01);
		}
	};
}

namespace P4
{
	TEST_CLASS(DijkstraAlgorithmusTest)
	{
	public:
		TEST_METHOD(Start2_Ende0_Wege1_6)
		{
			double expected = 6;
			int start = 2, end = 0;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P4/Wege1.txt";
			DirectedGraph graph(path);
			double result = graph.dijkstraAlg(start, end);

			std::string message = "Result: " + std::to_string(result) + "\n";
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result, 0.1);
		}

		TEST_METHOD(Start2_Ende0_Wege2_fail)
		{
			double expected = -1;
			int start = 2, end = 0;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P4/Wege2.txt";
			DirectedGraph graph(path);
			double result = graph.dijkstraAlg(start, end);

			std::string message = "Result: " + std::to_string(result) + "\n";
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result, 0.1);
		}

		TEST_METHOD(Start2_Ende0_Wege3_fail)
		{
			double expected = -1;
			int start = 2, end = 0;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P4/Wege3.txt";
			DirectedGraph graph(path);
			double result = graph.dijkstraAlg(start, end);

			std::string message = "Result: " + std::to_string(result) + "\n";
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result, 0.1);
		}

		TEST_METHOD(Start0_Ende1_G_1_2_gerichtet_5_56283)
		{
			double expected = 5.56283;
			int start = 0, end = 1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P2/G_1_2.txt";
			DirectedGraph graph(path);
			double result = graph.dijkstraAlg(start, end);

			std::string message = "Result: " + std::to_string(result) + "\n";
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result, 0.00001);
		}

		TEST_METHOD(Start0_Ende1_G_1_2_ungerichtet_2_36802)
		{
			double expected = 2.36802;
			int start = 0, end = 1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P2/G_1_2.txt";
			WeighedGraph graph(path);
			double result = graph.dijkstraAlg(start, end);

			std::string message = "Result: " + std::to_string(result) + "\n";
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result, 0.00001);
		}
	};

	TEST_CLASS(MooreBellmanFordAlgorithmTest)
	{
	public:
		TEST_METHOD(Start2_Ende0_Wege1_6)
		{
			double expected = 6;
			int start = 2, end = 0;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P4/Wege1.txt";
			DirectedGraph graph(path);
			double result = graph.mooreBellmanFordAlg(start, end);

			std::string message = "Result: " + std::to_string(result) + "\n";
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result, 0.1);
		}

		TEST_METHOD(Start2_Ende0_Wege2_2)
		{
			double expected = 2;
			int start = 2, end = 0;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P4/Wege2.txt";
			DirectedGraph graph(path);
			double result = graph.mooreBellmanFordAlg(start, end);

			std::string message = "Result: " + std::to_string(result) + "\n";
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result, 0.1);
		}

		TEST_METHOD(Start2_Ende0_Wege3_fail)
		{
			double expected = -1;
			int start = 2, end = 0;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P4/Wege3.txt";
			DirectedGraph graph(path);
			double result = graph.mooreBellmanFordAlg(start, end);

			std::string message = "Result: " + std::to_string(result) + "\n";
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result, 0.1);
		}

		TEST_METHOD(Start0_Ende1_G_1_2_gerichtet_5_56283)
		{
			double expected = 5.56283;
			int start = 0, end = 1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P2/G_1_2.txt";
			DirectedGraph graph(path);
			double result = graph.mooreBellmanFordAlg(start, end);

			std::string message = "Result: " + std::to_string(result) + "\n";
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result, 0.00001);
		}

		TEST_METHOD(Start0_Ende1_G_1_2_ungerichtet_2_36802)
		{
			double expected = 2.36802;
			int start = 0, end = 1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P2/G_1_2.txt";
			WeighedGraph graph(path);
			double result = graph.mooreBellmanFordAlg(start, end);

			std::string message = "Result: " + std::to_string(result) + "\n";
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result, 0.00001);
		}
	};
}

namespace P5
{
	TEST_CLASS(EdmondsKarpAlgorithmusTest)
	{
	public:
		TEST_METHOD(Start0_Ende7_Fluss_4)
		{
			double expected = 4;
			int start = 0, end = 7;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P5/Fluss.txt";
			DirectedGraph graph(path);
			double result = graph.EdmondsKarpAlg(start, end);

			std::string message = "Result: " + std::to_string(result) + "\n";
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result, 0.1);
		}

		TEST_METHOD(Start0_Ende7_Fluss2_5)
		{
			double expected = 5;
			int start = 0, end = 7;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P5/Fluss2.txt";
			DirectedGraph graph(path);
			double result = graph.EdmondsKarpAlg(start, end);

			std::string message = "Result: " + std::to_string(result) + "\n";
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result, 0.1);
		}

		TEST_METHOD(Start0_Ende7_G_1_2_0_75447)
		{
			double expected = 0.75447;
			int start = 0, end = 7;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P2/G_1_2.txt";
			DirectedGraph graph(path);
			double result = graph.EdmondsKarpAlg(start, end);

			std::string message = "Result: " + std::to_string(result) + "\n";
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result, 0.00001);
		}
	};
}

namespace P6
{
	TEST_CLASS(CycleCancelingAlgorithmusTest)
	{
	public:
		TEST_METHOD(Kostenminimal1_3)
		{
			double expected = 3;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P6/Kostenminimal1.txt";
			CostGraph graph(path);
			vector<double> flow = graph.CycleCancelingAlg();
			double result = graph.getCost(flow);

			std::string message = "Result: " + std::to_string(result) + "\n";
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result, 1);
		}

		TEST_METHOD(Kostenminimal2_0)
		{
			double expected = 0;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P6/Kostenminimal2.txt";
			CostGraph graph(path);
			vector<double> flow = graph.CycleCancelingAlg();
			double result = graph.getCost(flow);

			std::string message = "Result: " + std::to_string(result) + "\n";
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result, 1);
		}

		TEST_METHOD(Kostenminimal3_fail)
		{
			double expected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P6/Kostenminimal3.txt";
			CostGraph graph(path);
			vector<double> flow = graph.CycleCancelingAlg();
			double result = graph.getCost(flow);

			std::string message = "Result: " + std::to_string(result) + "\n";
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result, 1);
		}

		TEST_METHOD(Kostenminimal4_fail)
		{
			double expected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P6/Kostenminimal4.txt";
			CostGraph graph(path);
			vector<double> flow = graph.CycleCancelingAlg();
			double result = graph.getCost(flow);

			std::string message = "Result: " + std::to_string(result) + "\n";
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result, 1);
		}

		TEST_METHOD(Kostenminimal_gross1_1537)
		{
			double expected = 1537;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P6/Kostenminimal_gross1.txt";
			CostGraph graph(path);
			vector<double> flow = graph.CycleCancelingAlg();
			double result = graph.getCost(flow);

			std::string message = "Result: " + std::to_string(result) + "\n";
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result, 1);
		}

		TEST_METHOD(Kostenminimal_gross2_1838)
		{
			double expected = 1838;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P6/Kostenminimal_gross2.txt";
			CostGraph graph(path);
			vector<double> flow = graph.CycleCancelingAlg();
			double result = graph.getCost(flow);

			std::string message = "Result: " + std::to_string(result) + "\n";
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result, 1);
		}

		TEST_METHOD(Kostenminimal_gross3_fail)
		{
			double expected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P6/Kostenminimal_gross3.txt";
			CostGraph graph(path);
			vector<double> flow = graph.CycleCancelingAlg();
			double result = graph.getCost(flow);

			std::string message = "Result: " + std::to_string(result) + "\n";
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result, 1);
		}
	};

	TEST_CLASS(SuccessiveShortestPathAlgorithmusTest)
	{
	public:
		TEST_METHOD(Kostenminimal1_3)
		{
			double expected = 3;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P6/Kostenminimal1.txt";
			CostGraph graph(path);
			vector<double> flow = graph.successiveShortestPathAlg();
			double result = graph.getCost(flow);

			std::string message = "Result: " + std::to_string(result) + "\n";
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result, 1);
		}

		TEST_METHOD(Kostenminimal2_0)
		{
			double expected = 0;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P6/Kostenminimal2.txt";
			CostGraph graph(path);
			vector<double> flow = graph.successiveShortestPathAlg();
			double result = graph.getCost(flow);

			std::string message = "Result: " + std::to_string(result) + "\n";
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result, 1);
		}

		TEST_METHOD(Kostenminimal3_fail)
		{
			double expected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P6/Kostenminimal3.txt";
			CostGraph graph(path);
			vector<double> flow = graph.successiveShortestPathAlg();
			double result = graph.getCost(flow);

			std::string message = "Result: " + std::to_string(result) + "\n";
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result, 1);
		}

		TEST_METHOD(Kostenminimal4_fail)
		{
			double expected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P6/Kostenminimal4.txt";
			CostGraph graph(path);
			vector<double> flow = graph.successiveShortestPathAlg();
			double result = graph.getCost(flow);

			std::string message = "Result: " + std::to_string(result) + "\n";
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result, 1);
		}

		TEST_METHOD(Kostenminimal_gross1_1537)
		{
			double expected = 1537;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P6/Kostenminimal_gross1.txt";
			CostGraph graph(path);
			vector<double> flow = graph.successiveShortestPathAlg();
			double result = graph.getCost(flow);

			std::string message = "Result: " + std::to_string(result) + "\n";
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result, 1);
		}

		TEST_METHOD(Kostenminimal_gross2_1838)
		{
			double expected = 1838;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P6/Kostenminimal_gross2.txt";
			CostGraph graph(path);
			vector<double> flow = graph.successiveShortestPathAlg();
			double result = graph.getCost(flow);

			std::string message = "Result: " + std::to_string(result) + "\n";
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result, 1);
		}

		TEST_METHOD(Kostenminimal_gross3_fail)
		{
			double expected = -1;

			std::string path = "C:/Users/aschu/Documents/FH Aachen/MAP/Praktikum/P6/Kostenminimal_gross3.txt";
			CostGraph graph(path);
			vector<double> flow = graph.successiveShortestPathAlg();
			double result = graph.getCost(flow);

			std::string message = "Result: " + std::to_string(result) + "\n";
			Logger::WriteMessage(message.c_str());

			Assert::AreEqual(expected, result, 1);
		}
	};
}