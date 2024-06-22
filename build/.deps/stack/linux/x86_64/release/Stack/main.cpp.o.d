{
    depfiles_gcc = "main.o: Stack/main.cpp Stack/headers/stack.h  Stack/headers/../../Vector/headers/vector.h  Stack/headers/../../Vector/headers/visit.h  Stack/headers/../../Vector/headers/fibSearch.h  Stack/headers/../../Vector/headers/fib.h  Stack/headers/../../Vector/headers/binSearch.h  Stack/headers/../../Vector/headers/increase.h  Stack/headers/../../Vector/headers/permute.h  Stack/headers/../../Vector/headers/compare.h  Stack/headers/../../Vector/headers/shrink.h  Stack/headers/../../Vector/headers/expand.h  Stack/headers/../../Vector/headers/copyFrom.h  Stack/headers/../../Vector/headers/bubbleSort.h  Stack/headers/../../Vector/headers/find.h  Stack/headers/../../Vector/headers/search.h  Stack/headers/../../Vector/headers/max.h  Stack/headers/../../Vector/headers/mergeSort.h  Stack/headers/../../Vector/headers/quickSort.h  Stack/headers/../../Vector/headers/selectionSort.h  Stack/headers/../../Vector/headers/shellSort.h  Stack/headers/../../Vector/headers/remove.h  Stack/headers/../../Vector/headers/sort.h  Stack/headers/../../Vector/headers/insert.h  Stack/headers/../../Vector/headers/unsort.h  Stack/headers/../../Vector/headers/deduplicate.h  Stack/headers/../../Vector/headers/traverse.h  Stack/headers/../../Vector/headers/uniquify.h\
",
    files = {
        "Stack/main.cpp"
    },
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-O3",
            "-std=c++14",
            "-IStack/headers",
            "-DNDEBUG"
        }
    }
}