echo "Enter two numbers"
read a
read b
echo "Enter operation"
read op
case $op in
    +) echo "Sum of $a and $b is $(echo "$a + $b" | bc)";;
    -) echo "Difference of $a and $b is $(echo "$a - $b" | bc)";;
    x) echo "Product of $a and $b is $(echo "$a * $b" | bc)";;
    /) echo "Quotient of $a and $b is $(echo "scale=2; $a / $b" | bc)";;
    %) echo "Remainder of $a and $b is $(echo "$a % $b" | bc)";;
    *) echo "Invalid operation";;
esac