import sys
import cs50

# check for a single key
if len(sys.argv) != 2:
    print("ERROR: Must enter a single key to continue.")
    exit(1)

# check if key entered is alphabetical
elif not (sys.argv[1].isalpha()):
    print("ERROR: Must enter a key with alphabet only to continue.")
    exit(1)

else:
    keys = []
    for key in sys.argv[1]:
        if key.isupper():
            keys.append(ord(key) - 65)
        elif key.islower():
            keys.append(ord(key) - 97)

    p = cs50.get_string("plaintext: ")

    j = 0
    c = ""

    for i in range(len(p)):
        # j index for key list is reset once it reaches the length of the list
        if j == len(keys):
            j = 0
        if p[i].islower():
            c += chr((ord(p[i]) - 97 + keys[j]) % 26 + 97)
            j += 1
        elif p[i].isupper():
            c += chr((ord(p[i]) - 65 + keys[j]) % 26 + 65)
            j += 1
        else:
            c += p[i]

    print("ciphertext: {}".format(c))