import java.util.*;

/*
    bitpic class is storage of pixel values. 
    it has same properties as picture.
    width and height. 
*/
class bitpic {
    private int xlen; // width of picture
    private int ylen; // height of picture
    private int[] base;
    /*
    // default constructor
    public bitpic(){
        
    }*/
    // initialize class's object with picture width and height
    public bitpic(int width, int height){
        if(width > 0 && height > 0){
            xlen = width;
            ylen = height;
            base = new int[xlen * ylen];
        }
    }
    
    public bitpic setpixel(int x, int y, int pval){
        if(x > -1 && y > -1 && x < xlen && y < ylen){
            base[x * xlen + y] = pval;
        }
        return this;
    }
    
    public int getpixel(int x, int y){
        if(x > -1 && y > -1 && x < xlen && y < ylen){
            return base[x * xlen + y];
        }
        return 0;
    }
    
    public void print(){
        for (int i = 0; i < xlen; i++) {
            for (int j = 0; j < ylen; j++) {
                System.out.print(getpixel(i, j));
                System.out.print(' ');
            }
            System.out.println();
        }
    }
    
    public static void main(String[] args) {
        final int DEF_PIX_LEN = 80;
        bitpic bp = new bitpic(DEF_PIX_LEN, DEF_PIX_LEN);
        setbag sb = new setbag();
        Random rnd = new Random();
        for (int i = 0; i < DEF_PIX_LEN; i++) {
            for (int j = 0; j < DEF_PIX_LEN; j++) {
                int raw_val = rnd.nextInt() % 10;
                if(raw_val < 0){
                    raw_val = -raw_val;
                }
                bp.setpixel(i, j, raw_val);
                pix_counter pc = new pix_counter(raw_val);
                sb.add(pc);
            }
        }
        sb.print_maxmin();
        sb.print_all();
        bp.print();
        
    }
}

class pix_counter{
    public pix_counter(int pval){
        p = pval;
        cnt = 1;
    }
    int value(){
        return p;
    }
    int count(){
        return cnt;
    }
    pix_counter add(){
        cnt++;
        return this;
    }
    void print(){
        System.out.print("Pixel value ");
        System.out.print(p);
        System.out.print(" has count ");
        System.out.print(cnt);
        System.out.println(". ");
    }
    private int p; // pixel value
    private int cnt; // pixel counter
}

class setbag{
    private Vector<pix_counter> pc;
    private int minidx;
    private int maxidx;
    
    public setbag(){
        minidx = 0;
        maxidx = 0;
        pc = new Vector<pix_counter>();
    }
    public boolean add_count(pix_counter cnt){
        for (int i = 0; i < pc.size(); i++) {
            if(pc.elementAt(i).value() == cnt.value()){
                pc.elementAt(i).add();
                if(pc.elementAt(i).count() > pc.elementAt(maxidx).count()){
                    maxidx = i;
                }
                return true;
            }
            if(pc.elementAt(i).count() < pc.elementAt(minidx).count()){
                minidx = i;
            }
        }
        return false;
    }
    
    public setbag add(pix_counter cnt){
        if(!add_count(cnt)){
            pc.add(cnt);
        }
        return this;
    }
    public void print_maxmin(){
        System.out.print("Minimum ");
        pc.elementAt(minidx).print();
        System.out.print("Maximum ");
        pc.elementAt(maxidx).print();
    }
    public void print_all(){
        for (pix_counter item : pc) {
            item.print();
        }
    }
}