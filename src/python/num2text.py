#!/usr/bin/env python3

numtxtlt20 = ["", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sizteen", "seventeen", "eighteen", "nineteen"]
numtxt10th = ["", "ten", "twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety"]
hundreds = "hundred"
thousands = "thousand"
millions = "million"
billions = "billion"
trillions = "trillion"

MAX_NUM = 999_999_999_999_999
TRILLION =  1_000_000_000_000
BILLION =       1_000_000_000
MILLION =           1_000_000
THOUSAND = 1000
HUNDRED = 100

def num2text(n) -> str:
    if(n == 0):
        return ""
    txt = list()
    if(n < 0):
        n = -n
        txt.append("minus")
    if(n > MAX_NUM):
        return "I do not know number more than 999 trillions. "
    # one trillion to 999 trillions
    dig2 = int(n / TRILLION)
    if(dig2 > 0):
        txt.append(num2text(dig2) + " " + trillions)
    dig2 = int((n / BILLION) % THOUSAND)
    if(dig2 > 0):
        txt.append(num2text(dig2) + " " + billions)
    dig2 = int((n / MILLION) % THOUSAND)
    if(dig2 > 0):
        txt.append(num2text(dig2) + " " + millions)
    dig2 = int((n / THOUSAND) % THOUSAND)
    if(dig2 > 0):
        txt.append(num2text(dig2) + " " + thousands)
    dig2 = int((n / HUNDRED) % 10)
    if(dig2 > 0):
        txt.append(numtxtlt20[dig2] + " " + hundreds)
    dig2 = int(n % HUNDRED)
    if(dig2 > 19):
        #txt.append(numtxt10th[int(dig2/10)])
        tenthtxt = numtxt10th[int(dig2/10)]
        singledig = ""
        dig2 %= 10
        if(dig2 > 0):
            #txt.append(numtxtlt20[dig2])
            singledig = numtxtlt20[dig2]
        if(len(tenthtxt) > 0 and len(singledig) > 0):
            txt.append(tenthtxt + "-" + singledig)
        else:
            txt.append(tenthtxt)
            txt.append(singledig)
    else:
        txt.append(numtxtlt20[dig2])
        
    return ' '.join([numtxt for numtxt in txt]).strip()

if __name__ == "__main__":
    bignum = -123456789
    print(num2text(bignum))