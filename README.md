# parallel

Run some commands in parallel.

## Installation

### Pre-compiled file

```bash
wget https://github.com/liu-congcong/parallel/blob/main/parallel
chmod 755 parallel
```

### Compile from source files

```bash
git clone https://github.com/liu-congcong/ThreadPool.git
git clone https://github.com/liu-congcong/parallel.git
mv ThreadPool/threadPool.c ThreadPool/threadPool.h parallel/
cd parallel
gcc -o parallel parallel.c threadPool.c -lpthread
```

## Usage

```bash
parallel -h
Run some commands in parallel (https://github.com/liu-congcong/parallel)
Usage:
    ./parallel [--threads <int>] [--parameters <str>] --input <str>.
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

* 0.2 (20240821): xxx.
