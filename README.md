# Fast Split of Fasta Sequence

- Last modified: Tue Jan 14, 2020  11:26AM
- Sign: Johan Nylander


### Synopis

    $ splitfast [-h] [-s] [-m MAXLENGTH] [-w WRAPLENGTH]


### Options

- `-h`  Show short help text
- `-s`  Use only first string (non-whitespace characters) as output header.
  Default is to use the whole fasta header.
- `-m MAXLENGTH`  Set the maximum sequence length (MAXLENGTH) for each
  individual entry. Default is `100000`.
- `-w WRAPLENGTH` Set the maximum sequence length to be printed on each line
  (WRAPLENGTH). Default is `80`.


### Description

Split long fasta entries to shorter.

If a fasta sequence is longer than MAXLENGTH, then the sequence is split, and a
new fasta entry is created. Headers are relabeled with an integer suffix. For
example: `>label_0`, `>label_1`, etc.


### Examples

The example file `data/fasta.fas` has two sequences, each of length 160
positions, and with labels `Apa` and `Bpa`. Splitting these fasta
entries to maximum length of 50, will yield the following output:

    $ splitfast -m 50 fasta.fas
    >Apa_0
    AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
    >Apa_1
    AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
    >Apa_2
    AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
    >Apa_3
    AAAAAAAAAA
    >Bpa_0
    BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
    >Bpa_1
    BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
    >Bpa_2
    BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB
    >Bpa_3
    BBBBBBBBBB

The example file `data/longer.fas` has two sequences, each of length 230495
positions, and with labels `2233 LN:i:230495 KC:i:774035 km:f:3.362` and `2234
LN:i:230496 KC:i:774036 km:f:3.363`. Splitting these fasta entries using
default max length (100000), and using the `-s` option to only use the first
string as output header, will yield the following output (note that we only
display the output headers by filtering using `grep`):

    $ splitfast -s longer.fas | grep '>'
    >2233_0
    >2233_1
    >2233_2
    >2234_0
    >2234_1
    >2234_2


### Installation

See the provided [src/INSTALL](src/INSTALL) document.


### Bugs

Currently, the program may print empty fasta records (for certain combinations
of sequence length, max length, and wrap length). Hence, **check output!**

For example:

    $ splitfast -m 40 -w 20 fasta.fas > err.fas

Empty entries can be found by:

    $ grep -B 1 '^$' err.fas | grep '>'

Empty entries can be filtered by:

    $ awk 'BEGIN{RS=">";FS="\n";ORS=""}$2{print">"$0}' err.fas

Hence, to be on the safe side, one may us this workaround:

    $ splitfast -m 40 -w 20 fasta.fas | \
      awk 'BEGIN{RS=">";FS="\n";ORS=""}$2{print">"$0}'


### Download

<https://github.com/nylander/split-fasta-seq>
