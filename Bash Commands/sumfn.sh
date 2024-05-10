echo "Enter two numbers"
read a
read b
add() {
    sum=$(echo "$a + $b" | bc)
    echo "Sum of $a and $b is $sum"
}
add