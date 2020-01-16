# signature

The program which splits the input file on blocks with the selected size and
computes the signature of the each block. The signatures is saved in output
file.


## Usage
```
Usage:
    signature [KEYS]... INPUT_FILE OUTPUT_FILE

DESCRIPTION
    The program which splits the input file on blocks with the selected size
and computes the signature of the each block. The signatures is saved in
output file.

KEYS
    -h, --help
        this message

    --version
        Print version

    -v, --verbose LEVEL (default: WRN)
        Print information verbosly. Possible values: DBG, INF, WRN, ERR.

    -b, --block-size BLOCK_SIZE (default: 1M)
        the size of block on which input file is split. The value supports
        suffixes: K=KiloByte, M=MegaByte, G=GigaByte. A number without suffix
        is KiloBytes.

    -o, --option OPTION
        set special option:
        * sign_algo=[crc32,md5] (default: md5)
            signature algorithm
        * threads=NUM (default: as many threads as possible)
            integer number of threads for processing
            (at least 2: one -- manager, others -- workers)
        * log_file=<file path> (default: stdout)
            the log file path
        * log_batch_size=<number> (default: 100)
            the integer number of log messages for writing in async mode during
            multithread execution

EXAMPLES
    signature input.dat output.dat
    signature -b 32K input.dat output.dat -o threads=5
    signature --block-size 32K input.dat out.dat -o sign_algo=md5 -o threads=5
```



## TODO
1. Rename the directory *algos* to *algo*.
2. Create class which unions `Pool`, `ItemPool` (rename to *PoolItem*) and
   managers logic: *AddItemToList* and *HandleBatchOfItems*. Look up the same
   code for `LoggerManager` and `WorkerManager`.
3. Change `FileReader` and `FileWriter` classes by `std::ofstream` and
   `std::ifstream`.

