# parallel

Run some commands in parallel.

## Usage

```bash
git clone https://github.com/liu-congcong/ThreadPool.git
git clone https://github.com/liu-congcong/parallel.git
mv ThreadPool/threadPool.c ThreadPool/threadPool.h parallel/
cd parallel
gcc -o parallel parallel.c threadPool.c -lpthread
```

```bash
parallel -h
Run some commands in parallel (https://github.com/liu-congcong/parallel)
Usage:
    ./parallel [--threads <int>] [--parameters <parameters>] --input <file>.
Options:
    -t/--threads: number of threads [default: 1].
    -p/--parameters: list of parameters.
    -i/--input: commands or shell file.
```

```bash
parallel -t 3 -i "sleep \$1" -p 10 10 10 10 10 10
```

## Change logs

* 0.1 (20240805): Initial version.
