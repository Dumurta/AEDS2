public class QuickSortLA {
    public static void QuickSortLast( int[] array, int left, int right)
    {
        int pivot = right;
        int i = left, j = right;
        int temp;
        while(i <= j)
        {
            while(array[i] < pivot)
            {
                i++;
            }
            while(array[j] > pivot)
            {
                j--;
            }
            if(i <= j)
            {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }//end while
        if( left < j )
        {
            QuickSortLast(array, left, j);
        }
        if(i < right)
        {
            QuickSortLast(array, i, right);
        }
    }//end quicksortLast
    public static void imprimir(int[] array)
    {
        int n = array.length;
        for(int i = 0; i < n; i++)
        {
            System.out.print(array[i]);
        }
        System.out.print("\n");
    }
    public static void main(String[] args) {
        int[] arr = {0,1, 2, 3, 4, 5, 6, 7, 8, 9};
        
        imprimir(arr);
        QuickSortLast(arr, 0, arr.length - 1);
        imprimir(arr);
    }
}
