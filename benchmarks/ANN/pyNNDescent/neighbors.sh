#!/bin/bash

make clean all
./neighbors -R 40 -L 1000 -a 10 -d 1.2 -Q 250 -k 200 -b 2 -q /ssd1/ANN/yandex/yandex_query.fvecs -o outFile -c /ssd1/ANN/yandex/yandex_groundtruth.ivecs /ssd1/ANN/yandex/yandex_1M.fvecs
./neighbors -R 60 -L 1000 -a 10 -d 1.2 -Q 250 -k 200 -b 2 -q /ssd1/ANN/yandex/yandex_query.fvecs -o outFile -c /ssd1/ANN/yandex/yandex_groundtruth.ivecs /ssd1/ANN/yandex/yandex_1M.fvecs
./neighbors -R 80 -L 1000 -a 10 -d 1.2 -Q 250 -k 200 -b 2 -q /ssd1/ANN/yandex/yandex_query.fvecs -o outFile -c /ssd1/ANN/yandex/yandex_groundtruth.ivecs /ssd1/ANN/yandex/yandex_1M.fvecs

# echo "10 M tests"
# ./neighbors -R 40 -L 1000 -a 10 -d 1.2 -Q 250 -k 200 -b 2 -q /ssd1/ANN/sift/bigann_query.bvecs -o outFile -c /ssd1/ANN/sift/idx_10M.ivecs /ssd1/ANN/sift/sift10M.bvecs
# ./neighbors -R 60 -L 1000 -a 10 -d 1.2 -Q 250 -k 200 -b 2 -q /ssd1/ANN/sift/bigann_query.bvecs -o outFile -c /ssd1/ANN/sift/idx_10M.ivecs /ssd1/ANN/sift/sift10M.bvecs
# ./neighbors -R 80 -L 1000 -a 10 -d 1.2 -Q 250 -k 200 -b 2 -q /ssd1/ANN/sift/bigann_query.bvecs -o outFile -c /ssd1/ANN/sift/idx_10M.ivecs /ssd1/ANN/sift/sift10M.bvecs
# echo ''
# echo "50 M Tests"
# ./neighbors -R 40 -L 1000 -a 10 -d 1.2 -Q 250 -k 200 -b 2 -q /ssd1/ANN/sift/bigann_query.bvecs -o outFile -c /ssd1/ANN/sift/idx_50M.ivecs /ssd1/ANN/sift/sift50M.bvecs
# ./neighbors -R 60 -L 1000 -a 10 -d 1.2 -Q 250 -k 200 -b 2 -q /ssd1/ANN/sift/bigann_query.bvecs -o outFile -c /ssd1/ANN/sift/idx_50M.ivecs /ssd1/ANN/sift/sift50M.bvecs
# ./neighbors -R 80 -L 1000 -a 10 -d 1.2 -Q 250 -k 200 -b 2 -q /ssd1/ANN/sift/bigann_query.bvecs -o outFile -c /ssd1/ANN/sift/idx_50M.ivecs /ssd1/ANN/sift/sift50M.bvecs
# echo ''
# echo "100 M tests"
# ./neighbors -R 40 -L 1000 -a 10 -d 1.2 -Q 250 -k 200 -b 2 -q /ssd1/ANN/sift/bigann_query.bvecs -o outFile -c /ssd1/ANN/sift/idx_100M.ivecs /ssd1/ANN/sift/sift100M.bvecs
# ./neighbors -R 60 -L 1000 -a 10 -d 1.2 -Q 250 -k 200 -b 2 -q /ssd1/ANN/sift/bigann_query.bvecs -o outFile -c /ssd1/ANN/sift/idx_100M.ivecs /ssd1/ANN/sift/sift100M.bvecs
# ./neighbors -R 80 -L 1000 -a 10 -d 1.2 -Q 250 -k 200 -b 2 -q /ssd1/ANN/sift/bigann_query.bvecs -o outFile -c /ssd1/ANN/sift/idx_100M.ivecs /ssd1/ANN/sift/sift100M.bvecs
