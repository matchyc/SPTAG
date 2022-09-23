for i in 0 2346 5421 8797
do
    for j in 1 3 5 10 25 50 100 300 500
    do
            cp /home/cm/projects/ann/SPTAG/buildconfig.ini /home/cm/projects/ann/SPTAG/cm_test_config/query_${i}_${j}_search
            sed -i -e '8d' -e '7a\QueryPath=/ann/cm/data/deep10M/query_nn/deep10M_query_'"${i}"'_nn_'"${j}"'' \
            -e '12d' -e '11a\TruthPath=/ann/cm/data/deep10M/query_nn/deep10M_query_'"${i}"'_nn_'"${j}"'_gt' \
            "/home/cm/projects/ann/SPTAG/cm_test_config/query_${i}_${j}_search"
    done
done
    

