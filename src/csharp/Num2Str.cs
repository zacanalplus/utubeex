using System;
using System.Text;
using System.Collections.Generic;

class Num2Str
{
    public static readonly string[] DECS = new string[] {
        "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
        "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", 
        "nineteen"
    }; 
    public static readonly string[] TENTHS = new string[] {
        "", "ten", "twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety"
    };
    public static readonly string[] S_THOUSANDS = new string[] {
        "zero", "thousand", "million", "billion", "trillion"
    };
    public static readonly string S_HUNDRED = new string ("hundred");
    
    public static readonly ulong TEN = 10;
    public static readonly ulong TWENTY = 20;
    public static readonly ulong HUNDRED = 100;
    public static readonly ulong THOUSAND = 1000;
    
    public static readonly ulong MAX_NUM  = 999999999999999;
    public static readonly string NUM2BIG = new string("Number is too big, only know trillion max!");
    public static readonly string AND = new string("and");
    
    private ulong n;
    
    public Num2Str(ulong num){
        n = num;
    }
    
    string toString(){
        return Num2Str.to_string(n); 
    }
    
    static string to_string(ulong num){
        var sb = new List<string> ();
        if(num == 0){
            return DECS[0];
        }
        ulong hunds;
        if(num >= THOUSAND){
            for(ulong i=4; i > 0; i--){
                ulong div = pow(THOUSAND, i);
                if(num >= div){
                    sb.Add(to_string(num/div));
                    sb.Add(S_THOUSANDS[i]);
                    num %= div;
                }
            }
        }
        num %= THOUSAND;
        hunds = num / HUNDRED;
        if(hunds > 0){
            sb.Add(DECS[hunds]);
            sb.Add(S_HUNDRED);
            sb.Add(AND);
        }
        num %= HUNDRED;
        
        if(num >= TWENTY){
            hunds = num / TEN;
            string tenth = TENTHS[hunds];
            hunds = num % TEN;
            if(hunds > 0){
                StringBuilder st = new StringBuilder();
                st.Append(tenth);
                st.Append("-");
                st.Append(DECS[hunds]);
                sb.Add(st.ToString());
            }
            else{
                sb.Add(tenth);
            }
        }
        else{
            sb.Add(DECS[num]);
        }
        if(sb.Count > 1){
            sb.RemoveAll(r => r == DECS[0]);
        }
        return string.Join(" ", sb.ToArray());
    }
    
    static ulong pow(ulong n, ulong x){
        ulong prod = 1;
        while(x > 0){
            prod *= n;
            x--;
        }
        return prod;
    }
    
    static void Main(string[] args)
    {
        Num2Str num = new Num2Str(83947563);
        System.Console.WriteLine(num.toString());
        System.Console.WriteLine(to_string(10184753902611));
    }
}