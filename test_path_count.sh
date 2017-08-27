#!/bin/bash

rm ./path_count_test;

for dim in 1 2 3 4 5
do
    n_threads=$(nproc --all);
    echo "" |& tee -a path_count_test;
    echo "==================================================" |& tee -a path_count_test;
    echo "" |& tee -a path_count_test;
    ( time ./boggle_search -c -d $dim -p $n_threads ) |& tee -a path_count_test;
done
