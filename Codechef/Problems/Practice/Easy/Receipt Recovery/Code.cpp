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
		int _vertexCount;
		int _edgeCount;
		int _id;

		bool _accessToMatrix;
		bool _debugGraph;

		void InitializeMatrix()
		{
			for (int i = 0; i < VERTEX_COUNT_MAX; i++)
				for (int j = 0; j < VERTEX_COUNT_MAX; j++)
					_graphMatrix[i][j] = 0;

			_edgeCount = 0;
		}

		void InitializeParameters()
		{
			_accessToMatrix = false;
			_debugGraph = true;
			_edgeCount = 0;

			_id = GraphCurrentID;
			GraphCurrentID++;
		}

		int** InstantiateMatrix()
		{
			int **matrix = new int*[VERTEX_COUNT_MAX];
			for (int i = 0; i < VERTEX_COUNT_MAX; i++)
				matrix[i] = new int[VERTEX_COUNT_MAX];

			return matrix;
		}

	public:
		DirectedGraph(int V)
		{
			_vertexCount = V;
			_graphMatrix = InstantiateMatrix();
			InitializeMatrix();
			InitializeParameters();
		}

		void Reconstruct(int V)
		{
			_vertexCount = V;

			/*
				_graphMatrix = new int*[VERTEX_COUNT_MAX];
				for (int i = 0; i < _vertexCount; i++)
					_graphMatrix[i] = new int[VERTEX_COUNT_MAX];

			*/
			InitializeMatrix();
			InitializeParameters();
		}

		~DirectedGraph()
		{
			for (int i = 0; i < _vertexCount; i++)
				delete[] _graphMatrix[i];
			
			delete[] _graphMatrix;
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
			if(!IsEdgeInLimits(i, j))
			{
				if (_debugGraph)
					DebugPrint("Outside Graph Vertex Count");

				return;
			}

			_graphMatrix[i][j] = 1;
			_edgeCount++;
		}

		void SetEdgeFalse(int i, int j)
		{
			if(!IsEdgeInLimits(i, j))
			{
				if (_debugGraph)
					DebugPrint("Outside Graph Vertex Count");

				return;
			}

			_graphMatrix[i][j] = 0;
			_edgeCount--;
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

			if(_debugGraph)
				DebugPrint("Matrix Copy created for id " + _id);

			return matrixCopy;
		}

		void AllowAccess()
		{
			_accessToMatrix = true;
			if(_debugGraph)
				DebugPrint("Access to graph Matrix given for graph id " + _id);
		}

		void ResetAccess()
		{
			_accessToMatrix = false;
			if(_debugGraph)
				DebugPrint("Access to graph Matrix reset for graph id " + _id);
		}

		int** ForcegetGraphMatrix()
		{
			if(_debugGraph)
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

		void PrintMatrix()
		{
			for (int i = 0; i < _vertexCount; i++)
			{
				for (int j = 0; j < _vertexCount; j++)
					cout << _graphMatrix[i][j] << ' ';

				cout << endl;
			}
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
		graph.PrintMatrix();
}

int main()
{
	int T;
	DirectedGraph graph(-1);

	cin >> T;
	while (T--)
	{
		GetInput(graph);
	}

}
