## boggle-path-search

This program enumerates all the possible paths on a boggle board.

## Usage

```
tup upd
./boggle-search -d <dim> -m <min_len> -M <max_len>
```

where `<dim>` is the dimension of the board, `<min_len>` is the minimum length
of a boggle word, `<max_len>` is the maximum length of a boggle word.

## TODO

- [ ] parallelise search for different starting positions
- [ ] use symmetry to reduce search space
