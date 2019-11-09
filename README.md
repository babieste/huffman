# Huffman


```sh
# using makefile
make clean && make  # clean previously generated bin
make run            # execute
```

```sh
# using gcc directly

# clean previously generated bin
rm -rf bin

# execute
mkdir -p bin
gcc -I./include -Wall -Wextra -lstdc++ src/heap.c src/huffman.c src/main.c -o bin/huffman
./bin/huffman
```
