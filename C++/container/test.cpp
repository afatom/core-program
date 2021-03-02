#include <container_t.h>
#include <vector_t.h>
#include <dlist_t.h>

int main (void)
{

	//List_t<int>* pList = new List_t<int>;
	Vector_t<int>* pVec = new Vector_t<int>;
	
	
	int cont = 1;
	int option =0;
		while (cont) {
		cout << "\n  Vector/List Test - Choose option: " << endl;
		cout << "1:  Append element " << endl;
		cout << "2:  Prepend element " << endl;
		cout << "3:  Is Contains " << endl;
		cout << "4:  Find element " << endl;
		cout << "5:  Find element Index " << endl;
		cout << "6:  PushBack (Insert at end) " << endl;
		cout << "7:  Remove  " << endl;
		cout << "8:  Remove All " << endl;
		cout << "9:  Remove and delete " << endl;
		cout << "10: Remove and delete all " << endl;
		cout << "11: Get Num Of Elements" << endl;
		cout << "12: Print" << endl;
		
		

		cin >>  option;
		switch (option) 
		{
			case 1://Append element
				{
					int index,val;
					cout << "Please enter an index value: ";
					cin >> index;
					cout << "Please enter value: ";
					cin >> val;
					
					int* ptr1 = new int;
					*ptr1=val;
					cout<<"Append Result: "<<pVec->Append(ptr1, index)<<endl;
				}
					break;
				
			case 2://Prepend element
			{
					int index,val;
					cout << "Please enter an index value: ";
					cin >> index;
					cout << "Please enter value: ";
					cin >> val;
					
					int* ptr1 = new int;
					*ptr1=val;
					cout<<"Prepend Result: "<<pVec->Prepend(ptr1, index)<<endl;		
				}
					break;
			
				
			case 3://Is Contains
			{
					int val;
					cout << "Please enter value for searching: ";
					cin >> val;
					cout<<"Is Contains Retval: "<<pVec->IsContains(val)<<endl;
						}
					break;
		
				
			case 4://Find
				{
					int val;
					cout << "Please enter value for searching: ";
					cin >> val;
					int* ptr = pVec->Find(val);
					if(ptr)
					{
						cout<<"Element was founded ! val of element "<<*ptr<<endl;
						
					}
					else
					{
						cout<<"Element Not Exisit"<<endl;
						
					}
				}	
				break;
			
			case 5://find element index
			{
					int val;
					cout << "Please enter value for searching: ";
					cin >> val;
					cout<<"element index retval: "<<pVec->ElementIndex(val)<<endl;
					}
					break;
			
				
			case 6://push back
					{
					int val;
					cout << "Please enter value: ";
					cin >> val;
					
					int* ptr1 = new int;
					*ptr1=val;
					cout<<"PushBack Result: "<<pVec->PushBack(ptr1)<<endl;
						}
					break;
				
			case 7://remove
			{
					int val;
					cout << "Please enter value for removing: ";
					cin >> val;
					if(int* ptr = pVec->Remove(val))
					{
						cout<<"Element was Removed ! val of element "<<*ptr<<endl;
						break;
					}
					cout<<"Element Not Exisit"<<endl;
					}
					break;
				
			case 8://remove all
			{
					pVec->RemoveAll();
					cout<<"elements Removed! "<<endl;	
				}
					break;
							
			case 9://remove and delete
			{
			int val;
					cout << "Please enter value for remove: ";
					cin >> val;
					pVec->RemoveAndDelete(val);	
				}
					break;
				
			case 10://removeand delete all
			{
					pVec->RemoveAndDeleteAll();
					cout<<"elements Removed and deleted! "<<endl;
				}
					break;
				
			case 11://get noe
			{
					cout<<"Num of elements "<<pVec->GetNumOfElements()<<endl;
			}
					break;
				
			case 12://cout
			{
				cout <<"Vector items"<<endl;
				//cout<<x<<endl;
			}	
			
			
				
			default: break;
		}
	}
	
	
	
	return 0;
}


