#include <iostream>
#include <string>

#define TYPE_MAX 50000
#define NUMBER_MAX 200000

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
		bool _debug = true;
		
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
				cout << "\t" << iteratorPair -> x << " " << iteratorPair -> y << endl;
				iteratorPair = iteratorPair -> next;
			}
			
			cout << endl;
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
		
		bool _debug = true;
		
		void InitializeMemoryArrays()
		{
			_profitArray = new int[TYPE_MAX];
			_initialInventory = new int[TYPE_MAX];
			
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
				cout << "Memory Freed for Data!" << endl;
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
			ZeroMemoryArrays();
			int input;
			
			_initialInputCount = count;

			while (count--)
			{
				cin >> input;
				_initialInventory[input - 1] += 1;
			}
			
		}
		
		void PrintData()
		{
			PrintInitialData();
			
			PrintDayData();
		}
		
		void PrintInitialData()
		{
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
		
		void PrintDayData()
		{
			cout << "Day data logs: " << endl;
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
		
		void PrintTail()
		{
			if (_dayCount == 0)
				return;
			
			cout << endl;
			cout << "Tail Information: " << endl;
			
			_dayListTail -> Information -> PrintData();
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
	
	data.PrintData();
	// data.PrintTail();
	
	return 0;
}