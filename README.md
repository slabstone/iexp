# IEXP - Infinity Engine Extractor & Parser

Currently supports parsing `KEY V1` and `BIFF V1` into CSV.

## Building with CMake

This project uses git submodules so either clone with `--recurse-submodules` or execute `git submodule update --init` after cloning.

```shell
cd iexp
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .
```

## Example

Parse `KEY` file:

```shell
./src/iexp ../data/chitin.key > ../data/chitin.csv
```

Result:

```
bif_index,bif_length,bif_filename_offset,bif_filename_length,bif_location,cd6,cd5,cd4,cd3,cd2,cd1,cache,data,bif_filename
0,2476460,0x000007ec,17,0x0001,0,0,0,0,0,0,0,1,data/VVCETAL.bif
1,171136,0x000007fd,17,0x0001,0,0,0,0,0,0,0,1,data/EFFFILE.bif
2,228692,0x0000080e,18,0x0001,0,0,0,0,0,0,0,1,data/PROJECTL.bif
<...>
164,113731320,0x00001252,15,0x0001,0,0,0,0,0,0,0,1,data/IWDEE.bif
165,8750880,0x00001261,17,0x0001,0,0,0,0,0,0,0,1,data/PATCH26.BIF
166,7112536,0x00001272,18,0x0001,0,0,0,0,0,0,0,1,data/BDTP_DLC.BIF
resource_name,resource_type,resource_locator,source_index,tileset_index,file_index
#7eyes1a,0x03fb,0x00000000,0,0,0
#7eyes1b,0x03fb,0x00000001,0,0,1
#7eyes1c,0x03fb,0x00000002,0,0,2
<...>
bdtpto14,0x0004,0x0a600095,166,0,149
bdtpto15,0x0004,0x0a600096,166,0,150
bdtpto16,0x0004,0x0a600097,166,0,151
```



## Acknowledgements

Infinity Engine file formats information taken from [IESDP](https://gibberlings3.github.io/iesdp/main.htm).
