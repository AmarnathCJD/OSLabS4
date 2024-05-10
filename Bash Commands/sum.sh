i=1
echo "Enter the value of n"
read n
sum=0
while [ $i -le $n ]
do
    sum=$((sum + i))
    i=$((i + 1))
done
echo "Sum of $n numbers is $sum"