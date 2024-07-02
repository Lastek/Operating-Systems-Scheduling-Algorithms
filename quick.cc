#include <algorithm> // Provides swap

void quicksort(int data[], size_t n);
// Precondition: data is an array with at least n components.
// Postcondition: The elements of data have been rearranged so
// that data[0] <= data[1] <= ... <= data[n-1].

void partition(int data[], size_t n, size_t &pivot_index);
// Precondition: n > 1, and data is an array (or subarray)
// with at least n elements.
// Postcondition: The function has selected some "pivot value"
// that occurs in data[0]..data[n-1]. The elements of data
// have then been rearranged, and the pivot index set so that:
//   -- data[pivot_index] is equal to the pivot;
//   -- Each item before data[pivot_index] is <= the pivot;
//   -- Each item after data[pivot_index] is > the pivot.

void setPivot(int data[], size_t n);
// Precondition: n > 1 and data is an array or subarray
// Postcondition: data[0] holds the selected pivot value
//  The original value of data[0] has been swapped with the selected pivot value

void quicksort(int data[], size_t n)
{
	size_t pivot_index; // Array index for the pivot element
	size_t n1;			// Number of elements before the pivot element
	size_t n2;			// Number of elements after the pivot element

	if (n > 1)
	{
		// Partition the array, and set the pivot index.
		partition(data, n, pivot_index);

		// Compute the sizes of the subarrays.
		n1 = pivot_index;
		n2 = n - n1 - 1;

		// Recursive calls will now sort the subarrays.
		quicksort(data, n1);
		quicksort((data + pivot_index + 1), n2);
	}
}

void partition(int data[], size_t n, size_t &pivot_index)
{
	setPivot(data, n);
	// Set initial values
	pivot_index = 0;
	int x;
	int idx_big = 1,
		idx_small = n - 1;

	// Partition the array or sub-array
	while (idx_big <= idx_small)
	{
		while (idx_big < n && data[idx_big] <= data[pivot_index])
		{
			idx_big++;
		}
		while (data[idx_small] > data[pivot_index])
		{
			idx_small--;
		}
		// Check if resulting indeces have crossed over
		// if so then the two values are out of order and get swapped.
		if (idx_big < idx_small)
		{
			std::swap(data[idx_small], data[idx_big]);
		}
	}

	pivot_index = idx_small;
	std::swap(data[0], data[pivot_index]);
}

void setPivot(int data[], size_t n)
{
	if (n < 2)
		return;

	srand(515014); // set seed for rand(). Any value works.

	int a, b, c, x;

	// Choose 3 random values from array.
	a = rand() % n;
	b = rand() % n;
	c = rand() % n;

	// If needed, sort the three values by magnitude in two passes.
	if (data[a] > data[b])
	{
		std::swap(data[a], data[b]);
	}

	if (data[b] > data[c])
	{
		std::swap(data[b], data[c]);
	}

	//[b] is now the median value.
	// Swap median with first array element
	std::swap(data[0], data[b]);
}
