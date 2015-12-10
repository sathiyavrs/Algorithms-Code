#include <iostream>
#include <string>

#define VERTEX_COUNT_MAX 100

using namespace std;

int GraphCurrentID = 0;

void DebugPrint(string message)
{
	cout << message << endl;
}

class DirectedGraph
{
	private:
		int **_graphMatrix;
		int **_badEdgeMatrix;

		int *_childCount;
		int *_parentCount;

		int _vertexCount;
		int _edgeCount;
		int _leafCount;
		int _badEdgeCount;
		int _id;

		bool _accessToMatrix;
		bool _debugGraph;

		void InitializeMatrix(int **matrix)
		{
			for (int i = 0; i < VERTEX_COUNT_MAX; i++)
				for (int j = 0; j < VERTEX_COUNT_MAX; j++)
					matrix[i][j] = 0;

			matrix = 0;
		}

		void InitializeParameters()
		{
			_accessToMatrix = false;
			_debugGraph = true;
			_edgeCount = 0;
			_leafCount = _vertexCount;
			_badEdgeCount = 0;
		}

		int** InstantiateMatrix()
		{
			int **matrix = new int*[VERTEX_COUNT_MAX];
			for (int i = 0; i < VERTEX_COUNT_MAX; i++)
				matrix[i] = new int[VERTEX_COUNT_MAX];

			return matrix;
		}

		void InitializeArray(int* array)
		{
			for (int i = 0; i < VERTEX_COUNT_MAX; i++)
				array[i] = 0;
		}

	public:
		DirectedGraph(int V)
		{
			_graphMatrix = InstantiateMatrix();
			_childCount = new int[VERTEX_COUNT_MAX];
			_parentCount = new int[VERTEX_COUNT_MAX];
			_badEdgeMatrix = InstantiateMatrix();

			Reconstruct(V);

			_id = GraphCurrentID;
			GraphCurrentID++;
		}

		void Reconstruct(int V)
		{
			_vertexCount = V;

			InitializeMatrix(_graphMatrix);
			InitializeMatrix(_badEdgeMatrix);
			InitializeParameters();
			InitializeArray(_childCount);
			InitializeArray(_parentCount);
		}

		~DirectedGraph()
		{
			for (int i = 0; i < VERTEX_COUNT_MAX; i++)
				delete[] _graphMatrix[i];
			
			delete[] _graphMatrix;

			for (int i = 0; i < VERTEX_COUNT_MAX; i++)
				delete[] _badEdgeMatrix[i];
			
			delete[] _badEdgeMatrix;

			delete[] _childCount;
			delete[] _parentCount;

			if (_debugGraph)
				cout << "Directed graph with id = " << _id << " has been destroyed!" << endl;
		}

		bool IsEdge(int i, int j)
		{
			return _graphMatrix[i][j] = 1 ? true : false;
		}

		bool IsEdgeInLimits(int i, int j)
		{
			return (i > _vertexCount || j > _vertexCount) ? false : true;
		}

		void SetEdgeTrue(int i, int j)
		{
			int badEdgeCount = 0;

			if (!IsEdgeInLimits(i, j))
			{
				if (_debugGraph)
					DebugPrint("Outside Graph Vertex Count");

				return;
			}

			_graphMatrix[i][j] = 1;
			_edgeCount++;
			_childCount[i]++;
			_parentCount[j]++;

			if (_childCount[i] == 1)
				_leafCount--;

			if (_parentCount[j] == 2)
			{
				for (int iterator = 0; iterator < _vertexCount; iterator++)
				{
					if (_graphMatrix[iterator][j] == 1)
					{
						_badEdgeMatrix[iterator][j] = 1;
						_badEdgeCount++;
						badEdgeCount++;
					}
					
					if (badEdgeCount >= 2)
						return;
				}
			}

			if (_parentCount[j] > 2)
			{
				_badEdgeMatrix[i][j] = 1;
				_badEdgeCount++;
			}
		}

		void SetEdgeFalse(int i, int j)
		{
			if (!IsEdgeInLimits(i, j))
			{
				if (_debugGraph)
					DebugPrint("Outside Graph Vertex Count");

				return;
			}

			if (_badEdgeMatrix[i][j] == 1)
				_badEdgeCount--;

			_graphMatrix[i][j] = 0;
			_badEdgeMatrix[i][j] = 0;
			_edgeCount--;
			_childCount[i]--;
			_parentCount[j]--;

			if (_childCount[i] == 0)
				_leafCount++;

			if (_parentCount[j] == 1)
			{
				_badEdgeMatrix[i][j] = 0;
				_badEdgeCount--;
			}
		}

		int GetChildCount(int index)
		{
			return _childCount[index];
		}

		int GetVertexCount()
		{
			return _vertexCount;
		}

		int** GetMatrixCopy()
		{
			int** matrixCopy;
			matrixCopy = InstantiateMatrix();

			for (int i = 0; i < _vertexCount; i++)
				for (int j = 0; j < _vertexCount; j++)
					matrixCopy[i][j] = _graphMatrix[i][j];

			if (_debugGraph)
				DebugPrint("Matrix Copy created for id " + _id);

			return matrixCopy;
		}

		void AllowAccess()
		{
			_accessToMatrix = true;
			if (_debugGraph)
				DebugPrint("Access to graph Matrix given for graph id " + _id);
		}

		void ResetAccess()
		{
			_accessToMatrix = false;
			if (_debugGraph)
				DebugPrint("Access to graph Matrix reset for graph id " + _id);
		}

		int** ForcegetGraphMatrix()
		{
			if (_debugGraph)
				DebugPrint("Forceget Matrix called!");
			return _graphMatrix;
		}

		int** GetGraphMatrix()
		{
			if (_accessToMatrix)
				return _graphMatrix;

			if (_debugGraph)
				DebugPrint("Matrix Access denied");

		}

		void PrintGraph()
		{
			cout << "The graph matrix is: " << endl << endl;
			PrintMatrix(_graphMatrix);
		}

		void PrintMatrix(int** matrix)
		{
			for (int i = 0; i < _vertexCount; i++)
			{
				for (int j = 0; j < _vertexCount; j++)
					cout << matrix[i][j] << ' ';

				cout << endl;
			}
			cout << endl;

		}

		void PrintData()
		{
			cout << endl;
			PrintGraph();
			
			cout << "The bad-edge matrix is: " << endl << endl;
			PrintMatrix(_badEdgeMatrix);

			PrintNodeDetails();
			cout << "Leaf Count : " << _leafCount << endl;
			cout << "Edge Count : " << _edgeCount << endl;
			cout << "Vertex Count : " << _vertexCount << endl;
			cout << "Bad Edge Count : " << _badEdgeCount << endl;

			cout << endl;
		}

		void PrintNodeDetails()
		{
			cout << "The child counts are : " << endl << endl;
			for (int i = 0; i < _vertexCount; i++)
				cout << i << " : " << _childCount[i] << endl;

			cout << endl;

			cout << "The parent counts are : " << endl << endl;
			for (int i = 0; i < _vertexCount; i++)
				cout << i << " : " << _parentCount[i] << endl;

			cout << endl;
		}

		int GetEdgeCount()
		{
			return _edgeCount;
		}

		int GetLeafCount()
		{
			return _leafCount;
		}

		int GetBadEdgeCount()
		{
			return _badEdgeCount;
		}

};

void GetInput(DirectedGraph& graph)
{
	bool debug = false;

	int N, M, p, q;
	cin >> N;
	cin >> M;

	graph.Reconstruct(N);

	for (int i = 0; i < M; i++)
	{
		cin >> p;
		cin >> q;

		graph.SetEdgeTrue(p - 1, q - 1);
	}

	if (debug)
		graph.PrintData();
}

int main()
{
	int T;
	DirectedGraph graph(-1);

	cin >> T;
	while (T--)
	{
		GetInput(graph);
		graph.PrintData();
	}
	
	return 0;
}
