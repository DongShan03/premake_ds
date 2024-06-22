{
    depfiles_gcc = "main.o: Vector/main.cpp Vector/headers/vector.h Vector/headers/visit.h  Vector/headers/fibSearch.h Vector/headers/fib.h  Vector/headers/binSearch.h Vector/headers/increase.h  Vector/headers/permute.h Vector/headers/compare.h  Vector/headers/shrink.h Vector/headers/expand.h  Vector/headers/copyFrom.h Vector/headers/bubbleSort.h  Vector/headers/find.h Vector/headers/search.h Vector/headers/max.h  Vector/headers/mergeSort.h Vector/headers/quickSort.h  Vector/headers/selectionSort.h Vector/headers/shellSort.h  Vector/headers/remove.h Vector/headers/sort.h Vector/headers/insert.h  Vector/headers/unsort.h Vector/headers/deduplicate.h  Vector/headers/traverse.h Vector/headers/uniquify.h\
",
    files = {
        "Vector/main.cpp"
    },
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-O3",
            "-std=c++14",
            "-IVector/headers",
            "-DNDEBUG"
        }
    }
}