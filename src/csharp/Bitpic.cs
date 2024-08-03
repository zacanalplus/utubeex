using System;
using System.Collections.Generic;

class Setbag{
    private List<Pixcounter> pc;
    private int minidx;
    private int maxidx;
    
    public Setbag(){
        pc = new List<Pixcounter>();
        minidx = 0;
        maxidx = 0;
    }
    
    public Setbag add(Pixcounter pcnt){
        if(!add_count(pcnt)){
            pc.Add(pcnt);
        }
        return this;
    }
    
    public bool add_count(Pixcounter pcnt){
        for(int i = 0; i < pc.Count; i++){
            if(pc[i].value() == pcnt.value()){
                pc[i].add();
                if(pc[i].count() > pc[maxidx].count()){
                    maxidx = i;
                }
                return true;
            }
            if(pc[i].count() < pc[minidx].count()){
                minidx = i;
            }
        }
        return false;
    }
    ~Setbag(){
        pc = null;
    }
    public void print_maxmin(){
        Console.Write("Maximum ");
        pc[maxidx].print();
        Console.Write("Minimum ");
        pc[minidx].print();
    }
    public void print_all(){
        foreach(Pixcounter pcnt in pc){
            pcnt.print();
        }
    }
}

class Pixcounter{
    private int v; // Pixel value
    private int c; // Pixel count
    
    public int value(){
        return v;
    }
    public int count(){
        return c;
    }
    public Pixcounter add(){
        c++;
        return this;
    }
    
    public Pixcounter(int pval){
        v = pval;
        c = 1;
    }
    public void print(){
        Console.Write("Pixel value ");
        Console.Write(v);
        Console.Write(" has count ");
        Console.Write(c);
        Console.WriteLine(". ");
    }
}

class Bitpic
{
    private int[] p; // list of pixel value in array
    private int _wid; // width of picture
    private int _hig; // height of picture
    public Bitpic(int width, int height){
        if(width > 0 && height > 0){
            _wid = width;
            _hig = height;
        }
        p = new int[_wid * _hig];
    }
    public Bitpic setpixel(int x, int y, int pval){
        if(x > -1 && y > -1 && x < _wid && y < _hig){
            p[x * _wid + y] = pval;
        }
        return this;
    }
    public int getpixel(int x, int y){
        if(x > -1 && y > -1 && x < _wid && y < _hig){
            return p[x * _wid + y];
        }
        return 0;
    }
    public void print(){
        for (int i = 0; i < _wid; i++)
        {
            for (int j = 0; j < _hig; j++)
            {
                Console.Write(getpixel(i, j));
                Console.Write(' ');
            }
            Console.WriteLine();
        }
    }
    ~Bitpic(){
        p = null;
    }
    static void Main(string[] args)
    {
        const int DEF_PIX_LEN = 80;
        var rnd = new Random();
        Bitpic bp = new Bitpic(DEF_PIX_LEN, DEF_PIX_LEN);
        Setbag sb = new Setbag();
        for(int i = 0; i < DEF_PIX_LEN; i++){
            for(int j = 0; j < DEF_PIX_LEN; j++){
                var raw_val = rnd.Next();
                if(raw_val < 0){
                    raw_val = -raw_val;
                }
                raw_val %= 10;
                bp.setpixel(i, j, raw_val);
                Pixcounter pc = new Pixcounter(raw_val);
                sb.add(pc);
            }
        }
        sb.print_maxmin();
        sb.print_all();
        bp.print();
    }
}