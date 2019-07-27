import cs50
import math

while True:
    num = cs50.get_int("Number: ")
    if num >= 0:
        break

# number of digits
digits = int(math.log10(num)+1)


# sum digits
tot, first, second = 0, 0, 0

for i in range(1, digits+1):
    n = int(num % 10)

    # find the first digit
    if i == digits:
        first = n
    # find the second digit
    elif i == digits - 1:
        second = n

    if i % 2 == 0:
        n *= 2
        if n >= 10:
            r = int(n % 10)
            n = int(n / 10)
            tot += n + r
        else:
            tot += n
    else:
        tot += n
    num /= 10

if first == 3 and (second == 4 or second == 7) and digits == 15 and tot % 10 == 0:
    print("AMEX")
elif first == 5 and second < 6 and digits == 16 and tot % 10 == 0:
    print("MASTERCARD")
elif first == 4 and (digits == 13 or digits == 16) and tot % 10 == 0:
    print("VISA")
else:
    print("INVALID")

