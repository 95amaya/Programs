#!/bin/bash
let sum=$1+$2
let product=$(($1 * $2))
diff=$(($1 - $2))
((quotient = $1 / $2))

echo "sum is $sum, product is $product"
echo "diff is $diff, quotient is $quotient"