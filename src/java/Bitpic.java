import java.util.*;

class PixCounter{
    public PixCounter(Integer pval){
        p = pval;
        c = 1;
    }
    public PixCounter add(){
        c++;
        return this;
    }
    public Integer value(){
        return p;
    }
    public int count(){
        return c;
    }
    public void print(){
        System.out.print("Pixel value ");
        System.out.print(value());
        System.out.print(" has count ");
        System.out.print(count());
        System.out.println(". ");
    }
    private Integer p; // Pixel value 
    private int c; // Count of pixel value `p`
}

class SetBag{
    private Vector<PixCounter> pc;
    private int minidx;
    private int maxidx;
    public SetBag(){
        pc = new Vector<PixCounter>();
        minidx = 0;
        maxidx = 0;
    }
    public SetBag add(PixCounter c){
        if(!addCount(c)){
            pc.add(c);
        }
        return this;
    }
    public boolean addCount(PixCounter c){
        for(int i = 0; i < pc.size(); i++){
            if(c.value() == pc.elementAt(i).value()){
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
    public void print_maxmin(){
        System.out.print("Maximum ");
        pc.elementAt(maxidx).print();
        System.out.print("Minimum ");
        pc.elementAt(minidx).print();
    }
    public void print_all(){
        for(PixCounter c : pc){
            c.print();
        }
    }
}

class Bitpic {
    public final Integer DEF_PIX_VAL = 0;
    private Vector<Integer> base;
    private Integer w; // width of picture
    private Integer h; // height of picture
    public Bitpic alloc(){
        for(int i = 0; i < (w * h); i++){
            base.add(DEF_PIX_VAL);
        }
        return this;
    }
    public Bitpic(int width, int height){
        base = new Vector<Integer>();
        if(width > 0 && height > 0){
            w = width;
            h = height;
            alloc();
        }
    }
    public Bitpic setpixel(int x, int y, Integer pval){
        if(x > -1 && y > -1 && x < w && y < h){
            base.setElementAt(pval, x * w + y);
        }
        return this;
    }
    public Integer getpixel(int x, int y){
        if(x > -1 && y > -1 && x < w && y < h){
            return base.elementAt(x * w + y);
        }
        return DEF_PIX_VAL;
    }
    public void print(){
        for(int i = 0; i < w; i++){
            for(int j = 0; j < h; j++){
                System.out.print(getpixel(i, j));
                System.out.print(' ');
            }
            System.out.println();
        }
    }
    public static void main(String[] args) {
        final int SAMPLE_PIX_LEN = 80;
        Bitpic bp = new Bitpic(SAMPLE_PIX_LEN, SAMPLE_PIX_LEN);
        SetBag sb = new SetBag();
        //System.out.print("Sample pixel value at upper left corner of picture is ");
        //System.out.println(bp.getpixel(0, 0));
        for(int i = 0; i < SAMPLE_PIX_LEN; i++){
            for(int j = 0; j < SAMPLE_PIX_LEN; j++){
                Random rng = new Random();
                int raw_val = rng.nextInt();
                if(raw_val < 0){
                    raw_val = -raw_val;
                }
                int raw_pixel_val = raw_val % 10;
                bp.setpixel(i, j, raw_pixel_val);
                PixCounter pc = new PixCounter(raw_pixel_val);
                sb.add(pc);
            }
        }
        sb.print_maxmin();
        sb.print_all();
        bp.print();
    }
}