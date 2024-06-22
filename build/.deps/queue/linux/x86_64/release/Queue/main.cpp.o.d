{
    depfiles_gcc = "main.o: Queue/main.cpp Queue/headers/queue.h  Queue/headers/../../List/headers/list.h  Queue/headers/../../List/headers/listnode.h  Queue/headers/../../List/headers/visit.h  Queue/headers/../../List/headers/compare.h  Queue/headers/../../List/headers/init.h  Queue/headers/../../List/headers/insert.h  Queue/headers/../../List/headers/clear.h  Queue/headers/../../List/headers/copyNodes.h  Queue/headers/../../List/headers/mergeSort.h  Queue/headers/../../List/headers/insertionSort.h  Queue/headers/../../List/headers/selectionSort.h  Queue/headers/../../List/headers/find.h  Queue/headers/../../List/headers/search.h  Queue/headers/../../List/headers/selectMax.h  Queue/headers/../../List/headers/remove.h  Queue/headers/../../List/headers/sort.h  Queue/headers/../../List/headers/deduplicate.h  Queue/headers/../../List/headers/reverse.h  Queue/headers/../../List/headers/uniquify.h  Queue/headers/../../List/headers/traverse.h\
",
    files = {
        "Queue/main.cpp"
    },
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-O3",
            "-std=c++14",
            "-IQueue/headers",
            "-DNDEBUG"
        }
    }
}