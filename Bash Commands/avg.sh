echo "Enter the value of n"
read n
i=1
sum=0
while [ $i -le $n ]
do
    echo "Enter number"
    read num
    sum=$((sum + num))
    i=$((i + 1))
done
avg=$(echo "scale=2; $sum / $n" | bc)
echo "Average of $n numbers is $avg"