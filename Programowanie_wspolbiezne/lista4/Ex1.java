import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveTask;
import java.util.Arrays;

class Subsequence extends RecursiveTask<int[]> 
{
    private final int[] array;
    private final int leftIndex;
    private final int rightIndex;
    private static final int THRESHOLD = 3;

    public Subsequence(int[] arr, int start, int end) 
    {
        this.array = arr;
        this.leftIndex = start;
        this.rightIndex = end;
    }

    @Override
    public int[] compute()
    {
        if (rightIndex - leftIndex <= THRESHOLD) 
        {
            return findLongest(array, leftIndex, rightIndex);
        }
        else 
        {
            int mid = (leftIndex + rightIndex) / 2;
            Subsequence left = new Subsequence(array, leftIndex, mid);
            Subsequence right = new Subsequence(array, mid, rightIndex);

            left.fork();
            int[] rightResult = right.compute();
            int[] leftResult = left.join();

            int[] middle = middle(array, leftIndex, mid, rightIndex);

            if(leftResult.length >= middle.length && leftResult.length >= rightResult.length)
            {
                return leftResult;
            }
            if(middle.length >= rightResult.length)
            {
                return middle;
            }
            return rightResult;
        }
    }

    private int[] findLongest(int[] arr, int left, int right)
    {
        int maxLen = 1;
        int currentLen = 1;
        int maxNum = arr[left];
        for (int i = left + 1; i < right; i++) {
            if (arr[i] == arr[i - 1]) {
                currentLen++;
            } else {
                currentLen = 1;
            }
            if (currentLen > maxLen) {
                maxLen = currentLen;
                maxNum = arr[i];
            }
        }
        int[] result = new int[maxLen];
        for (int i = 0; i < maxLen; i++) {
            result[i] = maxNum;
        }
        return result;
    }

    private int[] middle(int[] array, int left, int mid, int right)
    {
        int leftVal  = array[mid - 1];
    int rightVal = array[mid];

    if (leftVal != rightVal)
    {
        return new int[] {array[mid]};
    }

    int countLeft = 0;
    int i = mid - 1;
    while (i >= left && array[i] == leftVal) {
        countLeft++;
        i--;
    }

    int countRight = 0;
    int j = mid;
    while (j < right && array[j] == rightVal) {
        countRight++;
        j++;
    }

    int mergedLen = countLeft + countRight;

    
    int[] merged = new int[mergedLen];
    Arrays.fill(merged, leftVal);
    return merged;
    }
}


public class Ex1 {
    public static void main(String[] args) {
        int arr[] = {1,2,3,3,4,1};

        ForkJoinPool pool = new ForkJoinPool();
        Subsequence task = new Subsequence(arr, 0, arr.length);

        int[] result = pool.invoke(task);

        for (int x : result)
            System.out.print(x + " ");
        System.out.println();
    }
}