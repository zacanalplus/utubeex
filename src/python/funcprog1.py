#!/usr/bin/env python3

def nextCollatz(n):
    if(n % 2 == 0):
        return int(n / 2);
    else:
        return 3 * n + 1;

def reverse(s):
    return s[::-1];

nextC = nextCollatz
#print(nextC(10))
#print(nextC(13))

print(list(map(nextC, range(13))))

fishes = ["ငါးရံ", "ငါးခူ", "ငါးကျည်း", "ငါးနီတူ", "ငါးကြင်း", "ငါးဖယ်"]

#print(sorted(fishes))

print(sorted(fishes, key = reverse))
balphas = ["ကညန", "ကကက", "ကထလ", "ကမက", "ကတလ", "ကစက"]

print(sorted(balphas))
print(sorted(balphas, key = reverse))


print(sorted(balphas, key = lambda s: s[::-1]))