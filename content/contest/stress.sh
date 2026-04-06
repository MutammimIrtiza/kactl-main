set -e
g++ gen.cpp -o gen
g++ brute.cpp -o bru
for((i = 1; ; ++i)); do
    ./gen $i > tcase
    ./a.out < tcase > myans
    ./bru < tcase > corans
    diff -Z myans corans > /dev/null || break
    echo "Passed test: " $i
done
echo "WA on test:"
cat tcase
echo "Your answer:"
cat myans
echo "Correct answer:"
cat corans