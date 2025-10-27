class MergeSort implements Runnable {
    private final int[] array;
    private final int[] temp; //zamiast kopiowania arr do kazdego watku
    private final int leftIndex;
    private final int rightIndex;

    public MergeSort(int[] array, int[] temp, int leftIndex, int rightIndex) {
        this.array = array;
        this.temp = temp;
        this.leftIndex = leftIndex;
        this.rightIndex = rightIndex;
    }

    // niepotrzebne synchronized
    // wątki działają na rozłącznych elementach tablicy
    private void merge(int[] array, int[] temp, int left, int middle, int right) {
        int i = left;
        int j = middle + 1;
        int k = left;

        // scalanie do tymczasowej tablicy
        while (i <= middle && j <= right) {
            if (array[i] <= array[j]) {
                temp[k++] = array[i++];
            } else {
                temp[k++] = array[j++];
            }
        }

        // pozostałe elementy
        while (i <= middle) temp[k++] = array[i++];
        while (j <= right) temp[k++] = array[j++];

        // z powrotem do tablicy głównej
        for (i = left; i <= right; i++) {
            array[i] = temp[i];
        }
    }

    private void sequentialMergeSort(int[] array, int[] temp, int left, int right) {
        if (left < right) {
            int middle = (left + right) / 2;
            sequentialMergeSort(array, temp, left, middle);
            sequentialMergeSort(array, temp, middle + 1, right);
            merge(array, temp, left, middle, right);
        }
    }

    @Override
    public void run() {
        if (leftIndex < rightIndex) {
            int size = rightIndex - leftIndex + 1;

            if (size <= 4) {
                sequentialMergeSort(array, temp, leftIndex, rightIndex);
                return;
            }
            int middle = (leftIndex + rightIndex) / 2;
            
            // nie ma potrzeby dwoch nowych watkow.
            // Aktualny watek moze pracowac zamiast jedneg z nowych
            MergeSort leftTask = new MergeSort(array, temp, leftIndex, middle);
            MergeSort rightTask = new MergeSort(array, temp, middle + 1, rightIndex);

            Thread leftThread = new Thread(leftTask);
            // Thread rightThread = new Thread(rightTask);
            rightTask.run();

            leftThread.start();
            // rightThread.start();

            try {
                leftThread.join();
                // rightThread.join();
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                return;
            }

            merge(array, temp, leftIndex, middle, rightIndex);
        }
    }
}


public class RookieMergeSort {

    public static void main(String[] args) {
        int arr[] = {4, 3, 2, 1, 5, 3, 43, 8, 9, 57};
        int[] temp = new int[arr.length];

        MergeSort job = new MergeSort(arr, temp, 0, arr.length - 1);
        job.run();
        // Thread t = new Thread(w);

        // t.start();
        // try {
        //     t.join();
        // } catch (InterruptedException e) {
        //     e.printStackTrace();
        // }

        for (int i = 0; i < arr.length; i++)
            System.out.printf("%d ", arr[i]);
        System.out.println();
    }
}