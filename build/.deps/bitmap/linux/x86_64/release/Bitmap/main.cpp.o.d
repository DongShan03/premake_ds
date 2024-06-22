{
    depfiles_gcc = "main.o: Bitmap/main.cpp Bitmap/headers/bitmap.h\
",
    files = {
        "Bitmap/main.cpp"
    },
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-O3",
            "-std=c++14",
            "-IBitmap/headers",
            "-DNDEBUG"
        }
    }
}