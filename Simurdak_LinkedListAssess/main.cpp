#include "tList.h"

int main()
{
	tList<int> test;

	cout << "TEST LIST CREATED\nPUSHING FIVE ELEMENTS TO THE FRONT: 24, 6, 6, 97, 38" << endl;
	test.push_front(24);
	test.push_front(6);
	test.push_front(6);
	test.push_front(97);
	test.push_front(38);
	test.printList();
	
	cout << "\nPUSHING FIVE ELEMENTS TO THE BACK: 53, 6, 45, 19, 6" << endl;
	test.push_back(53);
	test.push_back(6);
	test.push_back(45);
	test.push_back(19);
	test.push_back(6);
	test.printList();

	cout << "\nREMOVING ALL 6's:" << endl;
	test.remove(6);
	test.printList();

	cout << "\nRESIZING TO TWO ELEMENTS LESS:" << endl;
	test.resize(4);
	test.printList();

	cout << "\nRESIZING TO THREE ELEMENTS MORE:" << endl;
	test.resize(7);
	test.printList();
	
	cout << "\nPOPPING FRONT AND BACK ELEMENT:" << endl;
	test.pop_back();
	test.pop_front();
	test.printList();

	cout << "\nPRINTING FRONT AND BACK ELEMENT:" << endl;
	cout << test.front() << ", " << test.back() << endl << endl;
	system("pause");

	auto iterator = test.begin();
	cout << "\nITERATOR CREATED" << endl;
	cout << "Iterator currently pointing to: " << *test.begin() << endl << endl;
	system("pause");

	cout << "\nDOES THE ITERATOR POINT TO TEST'S HEAD?" << endl;
	if (test.begin() == iterator)
	{
		cout << "Yes\n" << endl;
	}
	else
	{
		cout << "No\n" << endl;
	}
	system("pause");

	cout << "\nINCREMENTING ITERATOR TWO TIMES..." << endl;
	for (int i = 0; i < 2; ++i)
	{
		iterator++;
	}
	cout << "Current iterator location: " << *iterator << endl << endl;
	system("pause");

	cout << "\nDECREMENTING ITERATOR ONE TIME..." << endl;
	iterator--;
	cout << "Current iterator location: " << *iterator << endl << endl;
	system("pause");

	test.push_back(1);
	for (iterator = test.begin(); !(iterator == test.end());)
	{
		iterator++;	
	}
	iterator--;
	cout << "\nTail: " << *iterator << endl << endl;
	system("pause");

	cout << "\nIS LIST EMPTY?" << endl;
	if (test.empty())
	{
		cout << "Yes\n" << endl;
	}
	else
	{
		cout << "No\n" << endl;
	}
	system("pause");

	cout << "\nCLEARING LIST...\n" << endl;
	test.clear();
	system("pause");

	cout << "\nIS LIST EMPTY?" << endl;
	if (test.empty())
	{
		cout << "Yes\n" << endl;
	}
	else
	{
		cout << "No\n" << endl;
	}

	cout << "END PROGRAM" << endl;
	system("pause");

	return 0;
}