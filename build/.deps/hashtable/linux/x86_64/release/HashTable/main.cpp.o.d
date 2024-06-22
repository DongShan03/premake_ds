{
    depfiles_gcc = "main.o: HashTable/main.cpp HashTable/headers/hashtable.h  HashTable/headers/../../Bitmap/headers/bitmap.h  HashTable/headers/Dictionary.h HashTable/headers/Entry.h  HashTable/headers/utility.h HashTable/headers/get.h  HashTable/headers/probe4Hit.h HashTable/headers/probe4Free.h  HashTable/headers/remove.h HashTable/headers/put.h  HashTable/headers/rehash.h\
",
    files = {
        "HashTable/main.cpp"
    },
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-O3",
            "-std=c++14",
            "-IHashTable/headers",
            "-DNDEBUG"
        }
    }
}