{
    depfiles_gcc = "main.o: Heap/main.cpp Heap/headers/heap.h  Heap/headers/../../Vector/headers/vector.h  Heap/headers/../../Vector/headers/visit.h  Heap/headers/../../Vector/headers/fibSearch.h  Heap/headers/../../Vector/headers/fib.h  Heap/headers/../../Vector/headers/binSearch.h  Heap/headers/../../Vector/headers/increase.h  Heap/headers/../../Vector/headers/permute.h  Heap/headers/../../Vector/headers/compare.h  Heap/headers/../../Vector/headers/shrink.h  Heap/headers/../../Vector/headers/expand.h  Heap/headers/../../Vector/headers/copyFrom.h  Heap/headers/../../Vector/headers/bubbleSort.h  Heap/headers/../../Vector/headers/find.h  Heap/headers/../../Vector/headers/search.h  Heap/headers/../../Vector/headers/max.h  Heap/headers/../../Vector/headers/mergeSort.h  Heap/headers/../../Vector/headers/quickSort.h  Heap/headers/../../Vector/headers/selectionSort.h  Heap/headers/../../Vector/headers/shellSort.h  Heap/headers/../../Vector/headers/remove.h  Heap/headers/../../Vector/headers/sort.h  Heap/headers/../../Vector/headers/insert.h  Heap/headers/../../Vector/headers/unsort.h  Heap/headers/../../Vector/headers/deduplicate.h  Heap/headers/../../Vector/headers/traverse.h  Heap/headers/../../Vector/headers/uniquify.h Heap/headers/getMax.h  Heap/headers/insert.h Heap/headers/percolateUp.h Heap/headers/delMax.h  Heap/headers/percolateDown.h Heap/headers/heapify.h  Heap/headers/heapSort.h\
",
    files = {
        "Heap/main.cpp"
    },
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-O3",
            "-std=c++14",
            "-IHeap/headers",
            "-DNDEBUG"
        }
    }
}