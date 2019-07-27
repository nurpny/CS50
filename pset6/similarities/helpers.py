from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""
    aline = a.split('\n')
    bline = b.split('\n')
    aset = {x for x in aline}
    bset = {x for x in bline}
    x = [x for x in aset if x in bset]
    return x


def sentences(a, b):
    """Return sentences in both a and b"""
    asen = sent_tokenize(a)
    bsen = sent_tokenize(b)
    aset = {x for x in asen}
    bset = {x for x in bsen}
    x = [x for x in aset if x in bset]
    return x


def sub(a, n):
    """Return substring of length n in a"""
    x = []
    for y in range(n, len(a)+1):
        x.append(a[y-n:y])
    return x


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    asub = sub(a, n)
    bsub = sub(b, n)
    aset = {x for x in asub}
    bset = {x for x in bsub}
    x = [x for x in aset if x in bset]
    return x
