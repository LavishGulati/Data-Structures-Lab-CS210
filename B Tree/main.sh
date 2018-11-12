# Random number generator

file=test.txt
echo 1 > $file
echo 3 >> $file

i=1
while ((i < 100)); do
    echo 2 >> $file
    echo $RANDOM >> $file
    i=$((i+1))
done

echo 4 >> $file
echo -1 >> $file
