#include <iostream>
#include <string>

#define TYPE_MAX 50000
#define NUMBER_MAX 200000

#define CHECK_NONE 0
#define CHECK_X 1
#define CHECK_Y 2
#define CHECK_XY 3

using namespace std;

void DebugPrint(string s)
{
	cout << s << endl;
}

struct OrderedPair
{
	int x;
	int y;
	OrderedPair* next;
	OrderedPair* previous;
};

class DayInformation
{
	private:
		int _day;
		int _count;
		bool _debug = false;
		
		OrderedPair* _head;
		OrderedPair* _tail;
	
	public:
		DayInformation(int day)
		{
			_day = day;
			_count = 0;
		}
		
		void Reconstruct(int day)
		{
			DeleteAll();
			_day = day;
			_count = 0;
			
			if(_debug)
				DebugPrint("Reconstructed!");
		}
		
		void DeleteAll()
		{
			OrderedPair* temp = _head;
			OrderedPair* toDelete;
			
			while (temp != NULL) 
			{
				toDelete = temp;
				temp = temp -> next;
				delete toDelete;
			}
		}
		
		~DayInformation()
		{
			DeleteAll();
			
			if (_debug)
				DebugPrint("Memory Freed for DayInformation!");
		}
		
		void Append(int lower, int upper)
		{
			_count++;
			
			if (_head == NULL)
			{
				_head = new OrderedPair();
				_head -> x = lower;
				_head -> y = upper;
				_tail = _head;
				
				return;
			}
			
			OrderedPair* newPair = new OrderedPair();
			newPair -> x = lower;
			newPair -> y = upper;
			
			_tail -> next = newPair;
			newPair -> previous = _tail;
			_tail = newPair;
		}
		
		void DeleteHead()
		{
			if (_head == NULL)
				return;
				
			OrderedPair* toDelete = _head;
			_head = _head -> next;
			
			if (_count == 1)
				_tail = _head;
				
			delete toDelete;
			_count--;
		}
		
		void DeleteTail()
		{
			if (_tail == NULL)
				return;
			
			OrderedPair* toDelete = _tail;
			
			_tail = _tail -> previous;
			
			if (_count == 1)
				_head = _tail;
				
			delete toDelete;
			_count--;
		}
		
		int GetDay()
		{
			return _day;
		}
		
		int GetCount()
		{
			return _count;
		}
		
		OrderedPair* GetHead()
		{
			return _head;
		}
		
		OrderedPair* GetTail()
		{
			return _tail;
		}
		
		void PrintData()
		{
			cout << endl;
			
			cout << "Day: " << _day << endl;
			cout << "Count: " << _count << endl;
			cout << endl;
			
			if (_count == 0)
				return;
			
			OrderedPair* iteratorPair = _head;
			
			cout << "Pairs: " << endl;
			for (int i = 0; i < _count; i++)
			{
				cout << iteratorPair -> x << " " << iteratorPair -> y << endl;
				iteratorPair = iteratorPair -> next;
			}
			
			cout << endl;
		}
		
		
};

struct RelationNode
{
	int Content;
	RelationNode* next;
	void* head;
};

struct RelationHead
{
	int Content;
	int Count;
	RelationNode* first;
	RelationNode* last;
	RelationHead* next;
};

class RelationshipList
{
	private:
		int _headCount;
		RelationHead* _head;
		bool _debug = true;
		
		void DeleteRelationHead(RelationHead* head)
		{
			if (head == NULL)
				return;
			
			if (head -> Count == 0)
			{
				delete head;
				return;
			}
			
			RelationNode* toDelete = head -> first;
			RelationNode* iterator = head -> first;
			
			for (int i = 0; i < head -> Count; i++)
			{
				iterator = iterator -> next;
				delete toDelete;
				toDelete = iterator;
			}
			
			delete head;
		}
		
		void DeleteRelationships()
		{
			if (_headCount == 0)
				return;
			
			RelationHead* toDelete = _head;
			for (int i = 0; i < _headCount; i++)
			{
				_head = _head -> next;
				DeleteRelationHead(toDelete);
				toDelete = _head;
			}
			
			_headCount = 0;
		}
	
	public:
		RelationshipList()
		{
			_headCount = 0;
		}
		
		~RelationshipList()
		{
			DeleteRelationships();
		}
		
		void AddRelationship(int x, int y)
		{
			if (x == y)
				return;
			
			if (_headCount == 0)
			{
				_head = new RelationHead();
				_head -> Count = 1;
				_head -> Content = x;
				
				_head -> first = new RelationNode();
				_head -> first -> Content = y;
				
				_head -> last = _head -> first;
				
				_head -> next = new RelationHead();
				_head -> next -> Count = 1;
				_head -> next -> Content = y;
				
				_head -> next -> first = new RelationNode();
				_head -> next -> first -> Content = x;
				
				_head -> next -> first -> head = _head;
				_head -> first -> head = _head -> next;
				
				_head -> next -> last = _head -> next -> first;
				
				_headCount = 2;
				
				return;
			}
			
			int check = 0;
			RelationHead* iterator = _head;
			RelationHead* previous;
			RelationNode* node;
			
			// xHead -> content = x; yHead -> content = y;
			RelationHead* xHead;
			RelationHead* yHead;
			
			// xNode -> content = x; yNode -> content = y;
			RelationNode* xNode;
			RelationNode* yNode;
			
			for (int i = 0; i < _headCount; i++)
			{
				if (iterator -> Content == x)
				{
					if (check == CHECK_Y)
						check = CHECK_XY;
					else
						check = CHECK_X;
						
					node = iterator -> last;
					
					node -> next = new RelationNode();
					node -> next -> Content = y;
					yNode = node -> next;
					
					iterator -> last = node -> next;
					
					xHead = iterator;
					
					iterator -> Count++;
				}
				
				if (iterator -> Content == y)
				{
					if (check == CHECK_X)
						check = CHECK_XY;
					else
						check = CHECK_Y;
						
					node = iterator -> last;
					
					node -> next = new RelationNode();
					node -> next -> Content = x;
					xNode = node -> next;
					
					iterator -> last = node -> next;
					
					yHead = iterator;
					
					iterator -> Count++;
				}
				
				if (check == CHECK_XY)
					break;
				
				previous = iterator;
				iterator = iterator -> next;
			}
			
			iterator = previous;
			
			switch (check)
			{
				case CHECK_NONE:
					iterator -> next = new RelationHead();
					iterator = iterator -> next;
					
					iterator -> Content = x;
					iterator -> Count = 1;
					
					iterator -> first = new RelationNode();
					iterator -> first -> Content = y;
					
					iterator -> last = iterator -> first;
					
					xHead = iterator;
					yNode = iterator -> first;
					
					iterator -> next = new RelationHead();
					iterator = iterator -> next;
					
					iterator -> Content = y;
					iterator -> Count = 1;
					
					iterator -> first = new RelationNode();
					iterator -> first -> Content = x;
					
					iterator -> last = iterator -> first;
					
					yHead = iterator;
					xNode = iterator -> first;
					
					_headCount += 2;
					
					break;
				
				case CHECK_X:
					iterator -> next = new RelationHead();
					iterator = iterator -> next;
					
					iterator -> Content = y;
					iterator -> Count = 1;
					
					iterator -> first = new RelationNode();
					iterator -> first -> Content = x;
					
					iterator -> last = iterator -> first;
					
					yHead = iterator;
					xNode = iterator -> first;
					
					_headCount++;
					break;
				
				case CHECK_Y:
					iterator -> next = new RelationHead();
					iterator = iterator -> next;
					
					iterator -> Content = x;
					iterator -> Count = 1;
					
					iterator -> first = new RelationNode();
					iterator -> first -> Content = y;
					
					iterator -> last = iterator -> first;
					
					xHead = iterator;
					yNode = iterator -> first;
					
					_headCount++;
					break;
			}
			
			// We now have xNode, xHead, yNode, yHead
			
			xNode -> head = xHead;
			yNode -> head = yHead;
			
			if (_debug)
			{
				cout << endl;
				
				cout << "xNode : " << xNode -> Content << " xHead: " << xHead -> Content << endl;
				cout << "yNode : " << yNode -> Content << " yHead: " << yHead -> Content << endl;
				
				cout << endl;
			}
			
			if (_debug)
			{
				if (xHead -> Content == 7)
					PrintRelationships();
					
				RelationHead* temp = (RelationHead*)(yHead -> first -> head);
				cout << xHead -> Content << " " << temp -> Content << " " << yHead -> first -> Content << endl;
			}
			
			/*
				list.AddRelationship(5, 2);
				list.AddRelationship(2, 3);
				list.AddRelationship(1, 7);
				list.AddRelationship(7, 5);
			*/
			
			// We now have to take care of xHead and yHead
			
			node = xHead -> first;
			RelationHead* secondHead;
			
			for (int i = 0; i < xHead -> Count; i++)
			{
				iterator = (RelationHead*)node -> head;
				
				if (HeadContainsX(iterator, y))
					continue;
				
				iterator -> last -> next = new RelationNode();
				iterator -> last -> next -> Content = y;
				iterator -> last -> next -> head = yHead;
				
				iterator -> Count++;
				
				iterator -> last = iterator -> last -> next;
				node = node -> next;
				
				if (!HeadContainsX(yHead, iterator -> Content))
				{
					if (_debug)
					{
						cout << yHead -> Content << " doesn't contain " << iterator -> Content << endl;
					}
					
					// continue;
					yHead -> last -> next = new RelationNode();
					yHead -> last -> next -> Content = iterator -> Content;
					yHead -> last -> next -> head = (void *)iterator;
					
					yHead -> Count++;
					yHead -> last = yHead -> last -> next;
				}
				
				
			}
			
			node = yHead -> first;
			for (int i = 0; i < yHead -> Count; i++)
			{
				iterator = (RelationHead*)node -> head;
				
				if (HeadContainsX(iterator, x))
					continue;
				
				iterator -> last -> next = new RelationNode();
				iterator -> last -> next -> Content = x;
				iterator -> last -> next -> head = xHead;
				
				iterator -> Count++;
				
				iterator -> last = iterator -> last -> next;
				node = node -> next;
				
				if (!HeadContainsX(xHead, iterator -> Content))
				{
					if(_debug)
						cout << xHead -> Content << " doesn't contain " << iterator -> Content << endl;
					
					// continue;
					xHead -> last -> next = new RelationNode();
					xHead -> last -> next -> Content = iterator -> Content;
					xHead -> last -> next -> head = (void* )iterator;
					
					xHead -> Count++;
					xHead -> last = xHead -> last -> next;
				}
				
				
			}
		}
		
		bool HeadContainsX(RelationHead* head, int x)
		{
			if (head -> Count == 0)
				return false;
			
			RelationNode* iterator = head -> first;
			for (int i = 0; i < head -> Count; i++)
			{
				if (iterator -> Content == x)
					return true;
				
				iterator = iterator -> next;
			}
			
			return false;
		}
		
		void PrintRelationships()
		{
			if (_headCount == 0)
				return;
			
			RelationHead* iterator = _head;
			RelationNode* node;
			
			cout << endl << endl << "Relationship data: " << endl;
			cout << "RelationShip _headCount: " << _headCount << endl << endl;
			
			for (int i = 0; i < _headCount; i++)
			{
				cout << "From: " << iterator -> Content << endl;
				cout << "To: ";
				
				node = iterator -> first;
				for (int j = 0; j < iterator -> Count; j++)
				{
					cout << node -> Content << " ";
					node = node -> next;
				}
				
				cout << endl << endl;
				
				iterator = iterator -> next;
			}
		}
};

struct DayList
{
	int Day;
	DayInformation* Information;
	DayList* next;
	DayList* previous;
};

class Data
{
	private:
		DayList* _dayListHead;
		DayList* _dayListTail;
		
		int* _profitArray;
		int* _initialInventory;
		
		long _dayCount;
		long _initialInputCount;
		
		bool _debug = false;
		
		int* GetMemoryArray()
		{
			int* intArray = new int[TYPE_MAX];
			return intArray;
		}
		
		void InitializeMemoryArrays()
		{
			_profitArray = GetMemoryArray();
			_initialInventory = GetMemoryArray();
			
			ZeroMemoryArrays();
		}
		
		void ZeroMemoryArrays()
		{
			for (long i = 0; i < TYPE_MAX; i++)
			{
				_profitArray[i] = 0;
				_initialInventory[i] = 0;
			}
		}
		
		void DeleteMemoryArrays()
		{
			delete[] _profitArray;
			delete[] _initialInventory;
			
			if (_debug)
				DebugPrint("Memory Arrays Freed!");
		}
		
		void ZeroMemoryInitialArray()
		{
			for (long i = 0; i < TYPE_MAX; i++)
				_initialInventory[i] = 0;
		}
		
		void DeleteDayList()
		{
			if (_dayCount == 0)
				return;
				
			DayList* iterator = _dayListHead;
			DayList* toDelete;
			
			for (int i = 0; i < _dayCount; i++)
			{
				toDelete = iterator;
				iterator = iterator -> next;
				
				delete toDelete -> Information;
				delete iterator;
			}
			
			_dayCount = 0;
		}
		
	public:
		Data()
		{
			InitializeMemoryArrays();
			Construct();
		}
		
		void Construct()
		{
			_dayCount = 0;
		}
		
		~Data()
		{
			if (_debug)
				DebugPrint("Memory Free process started!");
							
			DeleteMemoryArrays();
			DeleteDayList();
			
			if (_debug)
				DebugPrint("Memory Freed for Data!");
		}
		
		void AddInfo(int day, int x, int y)
		{
			if (_dayCount == 0)
			{
				_dayListHead = new DayList();
				_dayListHead -> Day = day;
				
				_dayListHead -> Information = new DayInformation(day);
				_dayListHead -> Information -> Append(x, y);
				
				_dayListTail = _dayListHead;
				
				_dayCount++;
				return;
			}
			
			DayList* iterator = _dayListHead;
			while (iterator -> Day < day)
			{
				iterator = iterator -> next;
				if (iterator == NULL)
					break;
			}
			
			DayList* toAdd;
			if (iterator == NULL)
			{
				toAdd = new DayList();
				toAdd -> Day = day;
				
				toAdd -> Information = new DayInformation(day);
				toAdd -> Information -> Append(x, y);
				
				toAdd -> previous = _dayListTail;
				_dayListTail -> next = toAdd;
				_dayListTail = toAdd;
				
				_dayCount++;
				return;
			}
			
			if (iterator -> Day == day)
			{
				iterator -> Information -> Append(x, y);
				return;
			}
			
			if (iterator -> Day > day)
			{
				iterator = iterator -> previous;
				toAdd = new DayList();
				
				toAdd -> Information = new DayInformation(day);
				toAdd -> Information -> Append(x, y);
				
				toAdd -> previous = iterator;
				toAdd -> next = iterator -> next;
				iterator -> next = toAdd;
				
				_dayCount++;
				return;
			}
		}
		
		void InputInitialState(long count)
		{
			ZeroMemoryInitialArray();
			int input;
			
			_initialInputCount = count;

			while (count-- > 0)
			{
				// cout << "Input please: ";
				cin >> input;
				_initialInventory[input - 1] += 1;
				
				// Commenting the following line causes an error for some unknown reason
				// TODO: FIND OUT WHY
				
				cout << _initialInventory[input - 1] << " : " << input << endl;
			}
		}
		
		void PrintData()
		{
			PrintInitialData();
			
			PrintDayData();
		}
		
		void PrintInitialData()
		{
			if (_initialInputCount == 0)
			{
				cout << endl << "No input avaliable at the moment" << endl;
				return;
			}
			
			cout << endl;
			cout << "Inventory Data: " << endl;
			
			int count = 0;
			
			for (int i = 0; i < TYPE_MAX; i++)
			{
				if (_initialInventory[i] != 0)
				{
					cout << i + 1 << " : " << _initialInventory[i] << endl;
					count++;					
				}
				
				if (count >= _initialInputCount)
					break;
			}
			
			cout << endl;
		}
		
		void PrintReverseData()
		{
			cout << endl << endl;
			
			cout << "Reverse data logs: " << endl << endl;
			cout << "DayCount = " << _dayCount << endl;
			
			if (_dayCount == 0)
				return;
			
			DayList* iterator = _dayListTail;
			
			for (int i = 0; i < _dayCount; i++)
			{
				iterator -> Information -> PrintData();
				iterator = iterator -> previous;
			}
			
			cout << endl;
		}
		
		void PrintDayData()
		{
			cout << endl << endl;
			cout << "Data logs: " << endl << endl;
			cout << "DayCount = " << _dayCount << endl;
			
			if (_dayCount == 0)
				return;
			
			DayList* iterator = _dayListHead;
			
			for (int i = 0; i < _dayCount; i++)
			{
				iterator -> Information -> PrintData();
				iterator = iterator -> next;
			}
			
			cout << endl;
		}
		
		void CalculateProfitArray()
		{
			if (_initialInputCount == 0)
			{
				if (_debug)
					DebugPrint("Input probably hasn't been entered yet!");
				
				DebugPrint("Can't calculate profit!");
				return;
			}
			
			if (_dayCount == 0)
				return;
			
			DayList* iterator = _dayListTail;
			for (int i = 0; i < _dayCount; i++)
			{
				CalculateDayProfit(iterator -> Information);
				iterator = iterator -> previous;
			}
		}
		
		void CalculateDayProfit(DayInformation* information)
		{
			
		}
};

int main()
{
	Data data;
	
	data.InputInitialState(2);
	
	data.AddInfo(1, 2, 3);
	data.AddInfo(1, 4, 2);
	data.AddInfo(2, 4, 3);
	data.AddInfo(3, 5, 6);
	data.AddInfo(2, 5, 7);
	data.AddInfo(4, 5, 7);
	data.AddInfo(7, 5, 7);
	
	// data.PrintData();
	// data.PrintReverseData();
	
	
	RelationshipList list;
	list.AddRelationship(5, 2);
	list.AddRelationship(2, 3);
	list.AddRelationship(1, 7);
	list.AddRelationship(7, 5);
	
	list.PrintRelationships();
	
	return 0;
}