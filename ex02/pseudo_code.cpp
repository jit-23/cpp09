
function mergeInsertionSort(array A):
    if length(A) <= 1:
        return A  // Base case: already sorted

    // todo n == (x,y)
    //todo Step 1: Pair elements (x,y) : para todo n , x < y;
    pairs = [] // todo criar container para os pares
    leftovers = [] // todo criar container para o que sobrar
    i = 0
    // todo /* fill the pairs container with the std::pairs(int,int) */
    while i < length(A) - 1:
        if A[i] > A[i+1]:
            pairs.append((A[i], A[i+1]))
        else:
            pairs.append((A[i+1], A[i]))
        i += 2
    if length(A) % 2 == 1:
        leftovers.append(A[-1]) //odd element left
    //todo if there is a lef over nbr, fill it here;

    //!
    //todo Step 2: Extract larger elements and sort them recursively
    // todo| by this it means -> to take the biggest of each pair, and 
    // todo| put it separately in largerElements container   
                    // todo |
                    // todo V
    largerElements = [pair[0] for pair in pairs]
    //! the recursion will make the larger elements  list smaller and smaller
    //! till the point that we have the biggest off all the list,   
    sortedLarger = mergeInsertionSort(largerElements)
    
    //todo Step 3: Insert smaller elements into sorted larger list
    smallerElements = [pair[1] for pair in pairs]
    for elem in smallerElements:
        sortedLarger = insertInOrder(sortedLarger, elem)

    //todoStep 4: Insert any leftover element
    for elem in leftovers:
        sortedLarger = insertInOrder(sortedLarger, elem)

    return sortedLarger

// Helper function: insert element into sorted array
function insertInOrder(sortedArray, x):
    // Use binary search to find correct position for x
    pos = binarySearchPosition(sortedArray, x)
    return sortedArray[0:pos] + [x] + sortedArray[pos:]


using namespace std;
int Binary_search(int x[],int size,int target){
    int maximum= size-1;
    int minimum = 0;
    int mean;
    while (maximum>minimum){
        mean = (maximum+minimum)/2;
        if (x[mean] == target){
            cout << "The number you're looking for is found! \n";
            return mean;
        }
        else if(x[mean] > target){
            maximum = (mean-1);
        }
        else{
            minimum = (mean+1);
        }
    }
    return -1;
}
int main(){
    int x[]={1,2,3,4,5};
    int a=sizeof(x)/sizeof(x[0]);
    int target=4;
    int show=Binary_search(x,a,target);
    if (show != -1){
        cout << "Your result is in the index: " << show;
    }
    return 0;
}
