{
    depfiles_gcc = "main.o: List/main.cpp List/headers/list.h List/headers/listnode.h  List/headers/visit.h List/headers/compare.h List/headers/init.h  List/headers/insert.h List/headers/clear.h List/headers/copyNodes.h  List/headers/mergeSort.h List/headers/insertionSort.h  List/headers/selectionSort.h List/headers/find.h List/headers/search.h  List/headers/selectMax.h List/headers/remove.h List/headers/sort.h  List/headers/deduplicate.h List/headers/reverse.h  List/headers/uniquify.h List/headers/traverse.h\
",
    files = {
        "List/main.cpp"
    },
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-O3",
            "-std=c++14",
            "-IList/headers",
            "-DNDEBUG"
        }
    }
}