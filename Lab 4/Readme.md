The input is a list of n integers, and an integer k. The selection problem is to find the k
th largest element.

### Algo 1
Takes input in a *Max Heap* then apply k times *extract-max* operations. Return the last element extracted from
the heap as the answer. *Running time is O(n + k log n).*
### Algo 2
A *min heap* S is maintained of size k. When any new element is inserted if it larger than smallest element then it is inserted and smallest is deleted. At the end the smallest element in S and return it
as the answer.*running time is O(n log k).*
> 1st enter n and k in new line or space separated
and then enter "n" numbers either space separated or in new line. 