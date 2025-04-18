# Fast Split of Fasta Sequences

## Synopsis

    $ splitfast [-h] [-v] [-s] [-m <maxlength>] [-w <wraplength>] infile(s).

## Description

Split long fasta entries to shorter.

If a fasta sequence is longer than `maxlength`, then the sequence is split, and
a new fasta entry is created. Headers are reused and relabeled with an added
integer suffix. For example, if original header is `>label`, then the new
sequence parts will receive labels `>label__0`, and `>label__1`, etc.

## Options

- `-h` --- help
- `-v` --- print version
- `-s` --- output only the first string of the header line
- `-m` --- max sequence length (default 100,000)
- `-w` --- line width (default 80)

`infile`(s) should be in fasta format.

## Examples

The example file `data/fasta.fas` has two sequences, each of length 160
positions, and with labels `Apa` and `Bpa`. Splitting these fasta entries to
maximum length of 50, will yield the following output:

    $ splitfast -m 50 fasta.fas
    >Apa__0
    AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
    >Apa__1
    AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
    >Apa__2
    AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
    >Apa__3
    AAAAAAAAAA
    >Bpa__0
    BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
    >Bpa__1
    BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
    >Bpa__2
    BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
    >Bpa__3
    BBBBBBBBBB

The example file `data/longer.fas` has two sequences, each of length 230,495
positions, and with labels `2233 LN:i:230495 KC:i:774035 km:f:3.362` and `2234
LN:i:230496 KC:i:774036 km:f:3.363`. Splitting these fasta entries using
default max length (100,000), and using the `-s` option to only use the first
string as output header, will yield the following output (note that we only
display the output headers by filtering using `grep`):

    $ splitfast -s longer.fas | grep '>'
    >2233__0
    >2233__1
    >2233__2
    >2234__0
    >2234__1
    >2234__2

## Installation

See the provided [INSTALL](INSTALL) document.

## Copyright and License

Copyright Johan Nylander 2018-2025. [MIT License](LICENSE)

## Download

<https://github.com/nylander/split-fasta-seq>
