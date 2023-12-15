#ifndef SORTEDARRAY_CPP
#define SORTEDARRAY_CPP

#include "SortedArray.h"


//Default Constructor
//PRE-Condition: None
//POST-Condition: theSize and theCapacity Initialized to 0
//Memory Dynamically Allocated For Array
template <typename Object>
SortedArray<Object>::SortedArray() {
	//Initialize Size to 0
	theSize = 0;

	//Dynamically Allocated Memory For Array 
	objects = new Object[theCapacity];

	//Initialize Capacity to Size 
	theCapacity = theSize;
}

//Copy Constructor
//PRE-Condition: Both arrays have been created. Copy Constructor has called it.
//POST-Condition: New array object initialized to another of it's type.
//Calls = operator for deep copy.
template <typename Object>
SortedArray<Object>::SortedArray(const SortedArray <Object>& from) : objects(NULL) {
	//Call to Assignment Operator For Deep Copy
	operator=(from);
}

//Destructor
//PRE-Condition: SortedArray contains class objects.
//POST-Condition: Frees up memory allocated for the objects.
template <typename Object>
SortedArray<Object>::~SortedArray() {
	delete[] objects;
}

//Overloaded Assignment Operator
//PRE-Condition: Both arrays have been created.
//POST-Condition: Deep copy of from array
template <typename Object>
const SortedArray<Object>& SortedArray<Object>::operator= (const SortedArray& from) {
	//If Statement to Loop Until Copy Completed
	if (this != &from) {
		//Delete Previously Allocated Array
		delete[] objects;
		//Size and Capacity Change to Copied Size and Capacity
		theSize = from.theSize;
		theCapacity = from.theCapacity;

		//Dynamically Allocate New Array of Specified Capacity
		objects = new Object[theCapacity];
		//For Loop to Copy Each Element of Array
		for (int i = 0; i < theSize; i++)
			objects[i] = from.objects[i];
	}
	//Return Information Copied
	return *this;
}

//Accessor Operator []
//PRE-Condition: Objects has been initialized.
//The first element is the element in front.
//POST-Condition: Returns specific element stored in objects.
template <typename Object>
const Object& SortedArray<Object>::operator[](int idx) const {
	//Return Element in Specified Position
	return objects[idx];
}

//Check if Two Sorted Arrays are the Same
//PRE-Condition: objects and rhs Are Initialized.
//POST-Condition: Returns True if objects and rhs array have elements in
//same order, otherwise returns false.
template <typename Object>
bool SortedArray<Object>::equals(const SortedArray <Object>& rhs) {
	//If Statement to Compare Array Sizes And Return False if Not Equal
	if (rhs.theSize != theSize)
		return false;

	//For Loop to Iterate Through Array for Each Element Comparision
	for (int i = 0; i < rhs.theSize; i++) {
		//If Statement to Return False if Element Compared is Not The Same
		if (rhs.objects[i] != objects[i]) {
			return false;
			break;
		}
	}
	//Return True if All Elements in Arrays Are The Same
	return true;
}

//Check if Array is Empty
//PRE-Condition: Objects has been initialized.
//POST-Condition: Returns true if objects contains no elements, otherwise false.
template <typename Object>
bool SortedArray<Object>::empty() const {
	//If Statement If No Elements Currently in Array Return True
	if (theSize == 0)
		return true;
	//Else Statement For All Other Cases
	else
		return false;
}

//Get the Size
//PRE-Condition: theSize is a data member.
//POST-Condition: Returns number of elements stored in objects.
template <typename Object>
int SortedArray<Object>::size() const {
	//Return Array Size
	return theSize;
}

//Get the Capacity
//PRE-Condition: theCapacity is a data member.
//POST-Condition: Returns current capacity of objects.
template <typename Object>
int SortedArray<Object>::capacity() const {
	//Return Array Capacity
	return theCapacity;
}

// Reserve
//PRE-Condition: Call from insert.
//POST-Condition: Sets new capacity if theSize less than new capacity and 
//existing capacity is less than requested capacity.
template<typename Object>
void SortedArray<Object>::reserve(int newCapacity) {
	//If Capacity Requested is Smaller Than Size 
	if (newCapacity < theSize) {
		cout << "ERROR, Current Size is Larger Than Requested Capacity!";
		return;
	}

	if (newCapacity < theCapacity)
		return;

	//Dynamic Allocation For New Array With New Capacity
	Object* temp = objects;
	objects = new Object[newCapacity];
	//For Loop to Copy Each Element Into New Array
	for (int i = 0; i < theSize; i++)
		objects[i] = temp[i];

	//Capacity Assigned to New Capacity
	theCapacity = newCapacity;

	//Deallocate Memory of Array Created
	delete[] temp;

}

//Print Array Elements
//PRE-Condition: There is an array.
//POST-Condition: All elements in array printed to ostream os 
//followed by character delimiter
template <typename Object>
void SortedArray<Object>::print(ostream& out, char delimiter) const {
	//For Loop to Display Each Element in Array 
	for (int i = 0; i < theSize; i++)
		out << objects[i] << delimiter;


}


//Clear Array Elements
//PRE-Condition: None
//POST-Condition: Removes all elements via theSize change.
template <typename Object>
void SortedArray<Object>::clear() {
	//Clear Array Via Size Change to Zero
	theSize = 0;

}

//Insert Element into Sorted Array
//PRE-Condition: objects Has Been Initialized. 
//POST-Condition: New element inserted into correct position in array.
//Calls reserve if full to expand capacity.
template <typename Object>
void SortedArray<Object>::insert(const Object& obj) {
	//If Size Equals Capacity Array is At Maximum Size
	if (theSize >= theCapacity)
		//Call to Reserve to Increase Capacity
		reserve(theSize * 2 + 1);

	int i;
	for (i = theSize - 1; (i >= 0 && objects[i] > obj); i--)
		objects[i + 1] = objects[i];

	objects[i + 1] = obj;
	theSize++;
}


//Delete the Minimum Element in Sorted Array
//PRE-Condition: objects has been initialized.
//POST-Condition: Array with one element cleared. Minimum
//deleted and elements in array shifted left one position.
template <typename Object>
void SortedArray<Object>::deleteMin() {
	//If Statement If Only 1 Element in Array
	if (theSize == 1)
		//Call to Clear Method
		clear();

	//For Loop to Move Elements Left by One Position Pushing Min Value Out
	for (int i = 0; i < theSize; i++) {
		objects[i] = objects[i + 1];
	}
	//Decrement Size By One
	theSize--;


}

//Delete the Maximum Element in Sorted Array
//PRE-Condition: objects has been initialized.
//POST-Condition: Maximum deleted and array size decremented by one.
template <typename Object>
void SortedArray<Object>::deleteMax() {
	//Maximum Value Deleted by Shortening Size of Sorted Array
	theSize--;


}

//Find the Min Element in Sorted Array
//PRE-Condition: theSize > 0
//POST-Condition: Minimum Value Returned to Calling Function
template <typename Object>
const Object& SortedArray<Object>::findMin() const {
	//Return Element in First Position Since it is Sorted
	return objects[0];

}

//Find the Max Element in Sorted Array
//PRE-Condition: theSize > 0
//POST-Condition: Maximum Value Returned to Calling Function
template <typename Object>
const Object& SortedArray<Object>::findMax() const {
	//Return Element in Last Position Since It is Sorted
	return objects[theSize - 1];

}

//Binary Search Array
//PRE-Condition: theSize > 0, Array is Sorted
//POST-Condition: Location of Element Returned, or Not Found if Not in Array
template <typename Object>
int SortedArray<Object>::binarySearch(const Object& obj) {
	//Variable Declarations Used in Search
	int low = 0;
	int high = theSize - 1;
	int mid;
	bool found = false;

	//While Loop to Cycle Through Until Done With Array Or Found Becomes True
	while ((low <= high) && !found) {
		//Binary Search Splits Array Down Middle For Searching
		mid = (low + high) / 2;

		//If Statement If Element at Middle Location Larger Than Search Item
		if (obj < objects[mid])
			//High Value Changed to Left Side Maximum Value 
			high = mid - 1;

		//Else If Statement If Element at Middle Location Smaller Than Search Item
		else if (obj > objects[mid])
			//Low Value Changed to Right Side Minimum Value
			low = mid + 1;
		//Else Statement If Element Found
		else
			found = true;
	}
	//If Found Return Where Found
	if (found)
		return mid;
	//Else Return Not Found
	else
		return -1;
}



#endif
