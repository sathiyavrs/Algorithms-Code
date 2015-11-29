#include <iostream>

#define MAX_PARTICIPANTS 400

using namespace std;

class Person
{
	public: 
		int ID;
		bool IsBoy;
		
		Person()
		{

		}

		void SetValue(int id, bool isBoy)
		{
			ID = id;
			IsBoy = isBoy;
		}

		void SetValue(Person person)
		{
			ID = person.ID;
			IsBoy = person.IsBoy;
		}
};

class TimeData 
{
	public: 
		long Time;
		Person Identity;
		bool IsStartingTime;

		TimeData()
		{

		}

		void SetValue(int time, Person identity, bool isStartingTime)
		{
			Time = time;
			Identity.SetValue(identity);
			IsStartingTime = isStartingTime;
		}

		void SetValue(TimeData timeData)
		{
			Time = timeData.Time;
			Identity.SetValue(timeData.Identity);
			IsStartingTime = timeData.IsStartingTime;
		}
};

void InitializeGraph(int** MatchingGraph)
{
	for (int i = 0; i < MAX_PARTICIPANTS; i++)
	{
		for (int j = 0; j < MAX_PARTICIPANTS; j++)
		{
			MatchingGraph[i][j] = 0;
		}
	}
}

void GetInput(int& NumberOfBoys, int& NumberOfGirls, long& TimeOfDance, long BoyTimes[MAX_PARTICIPANTS / 2][2], long GirlTimes[MAX_PARTICIPANTS / 2][2], int** MatchingGraph)
{
	int numberOfPartners;
	int partnerNumber;

	cin >> NumberOfBoys;
	cin >> NumberOfGirls;
	cin >> TimeOfDance;

	InitializeGraph(MatchingGraph);

	for (int i = 0; i < NumberOfBoys; i++)
	{
		cin >> BoyTimes[i][0];
		cin >> BoyTimes[i][1];

		cin >> numberOfPartners;
		
		for (int j = 0; j < numberOfPartners; j++)
		{
			cin >> partnerNumber;
			MatchingGraph[i][partnerNumber + NumberOfBoys] = 1;
		}
	}

	for (int i = 0; i < NumberOfGirls; i++)
	{
		cin >> GirlTimes[i][0];
		cin >> GirlTimes[i][1];

		cin >> numberOfPartners;

		for (int j = 0; j < numberOfPartners; j++)
		{
			cin >> partnerNumber;
			MatchingGraph[i + NumberOfBoys][partnerNumber] = 1;
		}
	}
}

void MergeSortTimeline(TimeData timeline[MAX_PARTICIPANTS], int start, int end)
{
	if(start == end)
		return;

	if(start > end)
		return;

	int middle = start + (end - start) / 2;

	// cout << "(" << start << ", " << middle << ", " << end << ")" << endl;

	MergeSortTimeline(timeline, start, middle);
	MergeSortTimeline(timeline, middle + 1, end);

	int iterator = start;
	int leftIterator = start;
	int rightIterator = middle + 1;
	
	// cout << endl << "Start situation " << iterator << ' ' << leftIterator << ' ' << rightIterator << endl;

	TimeData newTimeline[MAX_PARTICIPANTS];

	while (iterator <= end)
	{
		if(leftIterator <= middle && rightIterator <= end)
		{
			if (timeline[leftIterator].Time < timeline[rightIterator].Time)
			{
				newTimeline[iterator].SetValue(timeline[leftIterator]);
				leftIterator++;
				iterator++;
			}
			else 
			{
				newTimeline[iterator].SetValue(timeline[rightIterator]);
				rightIterator++;
				iterator++;
			}
		}
		else 
		{
			if (leftIterator > middle)
			{
				newTimeline[iterator].SetValue(timeline[rightIterator]);
				rightIterator++;
				iterator++;
			}

			if (rightIterator > end)
			{
				// cout << "Right Iterator and end is " << rightIterator << ' ' << end << endl;
				newTimeline[iterator].SetValue(timeline[leftIterator]);
				leftIterator++;
				iterator++;
			}

		}

		
	}

	for (int i = start; i <= end; i++)
	{
		timeline[i].SetValue(newTimeline[i]);
	}

}

void PrintTimeData(TimeData timeData)
{
	cout << '(' << timeData.Time << ", " << timeData.Identity.ID << ", " << timeData.Identity.IsBoy << ", " << timeData.IsStartingTime << ')';
}

void PrintTimeline(TimeData timeline[MAX_PARTICIPANTS], int dimension)
{
	for (int i = 0; i < dimension; i++)
	{
		PrintTimeData(timeline[i]);
		cout << endl;
	}
}

void BuildTimeline(long BoyTimes[MAX_PARTICIPANTS / 2][2], long GirlTimes[MAX_PARTICIPANTS / 2][2], TimeData Timeline [MAX_PARTICIPANTS], int NumberOfBoys, int NumberOfGirls) 
{
	bool DebugBuild = false;

	int iterator = 0;
	Person iteratorPerson;

	for (int i = 0; i < NumberOfBoys; i++)
	{
		iteratorPerson.SetValue(i, true);
		Timeline[iterator].SetValue(BoyTimes[i][0], iteratorPerson, true); 
		
		iterator++;
		Timeline[iterator].SetValue(BoyTimes[i][1], iteratorPerson, false);
		
		iterator++;
	}

	for (int i = 0; i < NumberOfGirls; i++)
	{
		iteratorPerson.SetValue(i, false);
		Timeline[iterator].SetValue(GirlTimes[i][0], iteratorPerson, true);

		iterator++;
		Timeline[iterator].SetValue(GirlTimes[i][1], iteratorPerson, false);

		iterator++;
	}

	// (time, id, isboy, startingTime)
	int length = 2 * (NumberOfGirls + NumberOfBoys);

	if (DebugBuild)
	{
		cout << endl << endl;
		PrintTimeline(Timeline, length);
		cout << endl << endl;
	}

	MergeSortTimeline(Timeline, 0, length - 1);

	if (DebugBuild)
		PrintTimeline(Timeline, length);
}

void PrintGraph(int MatchingGraph[MAX_PARTICIPANTS][MAX_PARTICIPANTS], int dimensions)
{
	for (int i = 0; i < dimensions; i++)
	{
		for(int j = 0; j < dimensions; j++)
		{
			cout << MatchingGraph[i][j] << ' ';
		}
		cout << endl;
	}
}

void PrintGraph(int** MatchingGraph, int dimensions)
{
	for (int i = 0; i < dimensions; i++)
	{
		for(int j = 0; j < dimensions; j++)
		{
			cout << MatchingGraph[i][j] << ' ';
		}
		cout << endl;
	}
}


int Min(int x, int y)
{
	return (x < y) ? x : y;
}

void InitializeAnalysis(int BoysActive[MAX_PARTICIPANTS / 2], int GirlsActive[MAX_PARTICIPANTS / 2], int Output[MAX_PARTICIPANTS / 2], int NumberOfBoys, int NumberOfGirls)
{
	int min = Min(NumberOfGirls, NumberOfBoys);
	
	for (int i = 0; i < min; i++)
		Output[i] = 0;

	for (int i = 0; i < NumberOfBoys; i++)
		BoysActive[i] = 0;

	for (int i = 0; i < NumberOfGirls; i++)
		GirlsActive[i] = 0;
}

void NextTimeActiveAnalysis(long& time, long& nextTime, int BoysActive[MAX_PARTICIPANTS / 2], int GirlsActive[MAX_PARTICIPANTS / 2], TimeData Timeline[MAX_PARTICIPANTS], int& timelineIterator, int totalTime)
{
	while (time == nextTime)
	{
		if(Timeline[timelineIterator].Identity.IsBoy)
		{
			if (Timeline[timelineIterator].IsStartingTime)
			{
				BoysActive[Timeline[timelineIterator].Identity.ID] = 1;
			}
			else
			{
				BoysActive[Timeline[timelineIterator].Identity.ID] = 0;
			}
		}
		else
		{
			if(Timeline[timelineIterator].IsStartingTime)
			{
				GirlsActive[Timeline[timelineIterator].Identity.ID] = 1;
			}
			else
			{
				GirlsActive[Timeline[timelineIterator].Identity.ID] = 0;
			}
		}

		timelineIterator++;
		nextTime = Timeline[timelineIterator].Time;

		if(nextTime > totalTime)
			break;
	}
}

void CreateWorkingGraph(int NumberOfBoys, int NumberOfGirls, int BoysActive[MAX_PARTICIPANTS / 2], int GirlsActive[MAX_PARTICIPANTS / 2], int** workingGraph, int** MatchingGraph)
{
	int graphDimension = NumberOfGirls + NumberOfBoys;
	int identityCheck = -1;

	for (int i = 0; i < graphDimension; i++)
	{
		for (int j = 0; j < graphDimension; j++)
		{
			if (i < NumberOfBoys)
			{
				identityCheck = i;
				if (BoysActive[identityCheck] == 0)
				{
					workingGraph[i][j] = 0;
				}
				else
				{
					if (j < NumberOfBoys)
					{
						workingGraph[i][j] = 0;
					}
					else
					{
						if (GirlsActive[j - NumberOfBoys] == 0)
						{
							workingGraph[i][j] = 0;
						}
						else
						{
							workingGraph[i][j] = MatchingGraph[i][j];
						}

					}
				}
			}
			else
			{
				identityCheck = i - NumberOfBoys;
				if (GirlsActive[identityCheck] == 0)
				{
					workingGraph[i][j] = 0;
				}
				else
				{
					if (j >= NumberOfBoys)
					{
						workingGraph[i][j] = 0;
					}
					else
					{
						if (BoysActive[j] == 0)
							workingGraph[i][j] = 0;
						else
							workingGraph[i][j] = MatchingGraph[i][j];
					}
				}
			}

		}
	}
}

void PerformSessionAnalysis(TimeData Timeline[MAX_PARTICIPANTS], int** MatchingGraph, int Output[MAX_PARTICIPANTS / 2], int NumberOfBoys, int NumberOfGirls, long totalTime, int BoysActive[MAX_PARTICIPANTS / 2], int GirlsActive[MAX_PARTICIPANTS / 2], int **workingGraph)
{
	// HIGHLIGHT
	bool workingGraphDebugging = true;

	long time = 0;
	long nextTime = Timeline[0].Time;
	int timelineIterator = 0;

	int min = Min(NumberOfGirls, NumberOfBoys);

	InitializeAnalysis(BoysActive, GirlsActive, Output, NumberOfBoys, NumberOfGirls);
	NextTimeActiveAnalysis(time, nextTime, BoysActive, GirlsActive, Timeline, timelineIterator, totalTime);

	
	// The following is a comment I used for debugging.
	if (workingGraphDebugging)
	{

		cout << endl;
		cout << "Matching Graph: " << endl;
		PrintGraph(MatchingGraph, NumberOfGirls + NumberOfBoys);

		cout << endl << endl;
		cout << "Working Graphs: " << endl << endl;
		cout << "Total time is " << totalTime << endl;
	}

	while (time < totalTime)
	{
		if (timelineIterator >= 2 * (NumberOfBoys + NumberOfGirls))
		{
			nextTime = totalTime;
		}

		CreateWorkingGraph(NumberOfBoys, NumberOfGirls, BoysActive, GirlsActive, workingGraph, MatchingGraph);


		// The following is code used for debugging purposes.
		if (workingGraphDebugging)
		{
			cout << "Time time is: " << time << endl;
			cout << "The next time is: " << nextTime << endl << endl;
		

			cout << "Boys Active: ";
			for (int i = 0; i < NumberOfBoys; i++)
			{
				cout << BoysActive[i] << ' ';
			}
			cout << endl;

			cout << "Girls Active: ";
			for (int i = 0; i < NumberOfGirls; i++)
			{
				cout << GirlsActive[i] << ' ';
			}
			cout << endl << endl;
		
			cout << "Working Graph: " << endl;
			PrintGraph(workingGraph, NumberOfGirls + NumberOfBoys);
			cout << endl << endl;
		}
		// Working Graph Created.
		// TODO: Finish Graph Analysis here.

		// Assume output Done.
		time = nextTime;
		NextTimeActiveAnalysis(time, nextTime, BoysActive, GirlsActive, Timeline, timelineIterator, totalTime);
	}

}

int main()
{
	int TestCases = 0;
	int NumberOfBoys;
	int NumberOfGirls;
	long TimeOfDance;

	long BoyTimes[MAX_PARTICIPANTS / 2][2];
	long GirlTimes[MAX_PARTICIPANTS / 2][2];

	int **MatchingGraph = new int*[MAX_PARTICIPANTS];
	for (int i = 0; i < MAX_PARTICIPANTS; i++)
		MatchingGraph[i] = new int[MAX_PARTICIPANTS];


	TimeData Timeline[MAX_PARTICIPANTS];

	int Output[MAX_PARTICIPANTS / 2];
	int BoysActive[MAX_PARTICIPANTS / 2];
	int GirlsActive[MAX_PARTICIPANTS / 2];
	int **workingGraph = new int*[MAX_PARTICIPANTS];
	for (int i = 0; i < MAX_PARTICIPANTS; i++)
		workingGraph[i] = new int[MAX_PARTICIPANTS];

	cin >> TestCases;

	while (TestCases--)
	{
		GetInput(NumberOfBoys, NumberOfGirls, TimeOfDance, BoyTimes, GirlTimes, MatchingGraph);
		BuildTimeline(BoyTimes, GirlTimes, Timeline, NumberOfBoys, NumberOfGirls);
		
		// void PerformSessionAnalysis(TimeData Timeline[MAX_PARTICIPANTS], int MatchingGraph[MAX_PARTICIPANTS][MAX_PARTICIPANTS], int Output[MAX_PARTICIPANTS / 2], int NumberOfBoys, int NumberOfGirls, long totalTime)

		PerformSessionAnalysis(Timeline, MatchingGraph, Output, NumberOfBoys, NumberOfGirls, TimeOfDance, BoysActive, GirlsActive, workingGraph);
	}

	for (int i = 0; i < MAX_PARTICIPANTS; i++)
		delete[] workingGraph[i];

	delete[] workingGraph;

	for (int i = 0; i < MAX_PARTICIPANTS; i++)
		delete[] MatchingGraph[i];

	delete[] MatchingGraph;
	return 0;
}
