
#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stdexcept>
#include <t_tcontainer.h>
#include <cstddef>


#define TEMPLATE_TEMPLATE_CONTAINER

#define TYPE int
#ifdef 	TEMPLATE_TEMPLATE_CONTAINER
#define CONTR list
#else   
#define CONTR list<TYPE>
#endif

using namespace std;
int main()
{

	tContainer_t<TYPE, CONTR> container;

	int cont = 1;			// trigger to stop loop	
	unsigned int option;

	while (cont)
	{
		cout << "Choose option:" << endl;
		cout << "	1: Insert a number" << endl;
		cout << "	2: Find a number" << endl;
		cout << "	3: Number Of Elements" << endl;
		cout << "	4: Remove an element" << endl;
		cout << "	5: Remove all elements" << endl;
		cout << "	6: Is empty?" << endl;
		cout << "	7: Get first element in container" << endl;
		cout << "	8: Get last element in container" << endl;
		cout << "	9: Remove & Delete an item" << endl;
		cout << "	10: Remove & Delete all items" << endl;
		cout << "	11: Print all items" << endl;
		
		cout << "	Any other number - exit " << endl;

		cin >> option;
		switch(option)
		{
			case 1:
			{	
				cout << "Plz enter num to insert: "<<endl;
				TYPE* num = new TYPE;
				cin >> *num;
				cout << endl;
				container.InsertAtEnd((TYPE*)num);
				cout << "Item has been inserted" << endl;

				break;
			}
			case 2:
			{
				cout << "Plz enter number to search: "<<endl;
				int num;
				cin >> num;
				
				TYPE * res;
				res = container.Find(num);
				if(res)
				{
					cout << "Item was found: Item Adress " << res <<"  Item Val "<<*res<< endl;
				}
				else
				{
					cout << "Item Not Exist"<< endl;
				}
				
				 
				break;
			}
			case 3:
			{
				cout << "Container's num of elements is: " << container.ItemsNum() << endl;
				break;
			}
			case 4:
			{
				int num;
				cout << "Insert a number to remove: "<<endl;
				cin >> num;
				container.Remove(num);

				break;
			}
			case 5:
			{
				container.RemoveAll();
				cout << "All items has been removed from container\n"<<endl;
				break;
			}
			case 6:
			{
				cout << "Container is empty? ";
				if(container.IsEmpty())
				{
					cout<<"Yes"<<endl;
				}
				else{
					cout<<"No"<<endl;
				}

				break;
			}
			case 7:
			{	
				TYPE * res = (int*)(container.GetFirst());
				if (NULL != res)
				{
					cout << "The 1st element in container is: " << *res << endl;
				}
				else cout << "Container is empty" << endl;
			
				break;
			}
			case 8:
			{
				TYPE * res = (int*)(container.GetLast());
				if (NULL != res)
				{
					cout << "The last element in container is: " << *res << endl;
				}
				else cout << "Container is empty" << endl;

				break;
			}

			case 9:
			{
				cout << "Plz insert item to delete: "<<endl;
				int num;
				cin >> num;

				container.RemoveAndDelete(num);
				cout << "Item has been removed & deleted\n"<<endl;

				break;
			}
			case 10:
			{
				container.RemoveAndDeleteAll();

				cout << "All items have been removed & deleted\n"<<endl;

				break;
			}
			
			case 11:
			{
				cout<<container<<endl;

				break;
			}

			default: return 0;	
					 break;
		}	

	}
	return 0;
}
