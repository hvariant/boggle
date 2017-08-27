## boggle-path-search

This program enumerates all the possible paths on a boggle board.

Dictionary downloaded from [here](http://www.cs.duke.edu/courses/cps100/spring05/assign/boggle/), renamed from `enable1.txt` to `dictionary.txt`.

Dice configuration for english taken from [here](https://boardgames.stackexchange.com/questions/29264/boggle-what-is-the-dice-configuration-for-boggle-in-various-languages).

## Usage

```
tup upd
./boggle-search -d <dim> -m <min_len> -M <max_len>
```

where `<dim>` is the dimension of the board, `<min_len>` is the minimum length
of a boggle word, `<max_len>` is the maximum length of a boggle word.

## TODO

- [x] generate boggle puzzle
- [x] solve boggle using dictionary
- [ ] generate boggle dice configuration of random dimension
- [ ] parallelise search for different starting positions
- [ ] use symmetry to reduce search space when counting
