# Huffman Archiver
Build:
```
$ mkdir build
$ cd build
$ cmake ..
$ make -j8
```

The archiver supports 4 command line flags:
  * ```-c```: archiving
  * ```-u```: unzipping
  * ```-f```, ```--file <path>```: input file name
  * ```-o```, ```--output <path>```: output file name

Example:
```
$ ./archiver -c -f file.txt -o out.bin
Input file size: 15678 bytes
Output file size: 6172 bytes
Adding data size: 482 bytes
```
