# Fast Split of Fasta Sequence

- Last modified: fre dec 06, 2019  02:21
- Sign: Johan Nylander

### Synopis

    $ splitfast [-h] [-m MAXLENGTH] [-w WRAPLENGTH]

### Options

- `-h`  Show short help text
- `-m MAXLENGTH`  Set the maximum sequence length (MAXLENGTH) for each
  individual entry. Default to `100000`.
- `-w WRAPLENGTH` Set the maximum sequence length to be printed on each line
  (WRAPLENGTH). Defaults to `80`.

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
