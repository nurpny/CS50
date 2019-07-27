import cs50

while True:
    n = cs50.get_int("Height: ")
    if (n <= 23 and n >=0):
        break

for i in range(n):
    print(" "*(n-1-i), end = "")
    print("#"*(i+1), end = "")
    print("  ", end = "")
    print("#"*(i+1), end ="")
    print("")
