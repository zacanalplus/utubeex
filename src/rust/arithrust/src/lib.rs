pub mod zlibg{
    
    //! # prime checking function
    //! 
    //! A simple function takes 64 bits integer and check whether it is prime or not
    //! [`checkprime`]
    #! [warn(missing_docs)]
    /// check the interger parameter and return true if the number is prime, false otherwise.
    pub fn checkprime(num : i64) -> bool{
        if num < 2 {
            return false;
        }
        else if num % 2 == 0 {
            return num == 2;
        }
        else if num % 3 == 0 {
            return num == 3;
        }
        else{
            let mut div = 5;
            while div * div <= num{
                if num % div == 0 {
                    return false;
                }
                div += 2;
                if num % div == 0 {
                    return false;
                }
                div += 4;
            }
        }
        return true;
    }
    
    use rand::{thread_rng, Rng};
    
    /// Module level static variable for sharing data
    pub static mut TEN :i32 = 0; 
    
    /// Main function change module level static variable value and takes part in assignment. 
    pub fn main() {
        unsafe {
            TEN = 10;
        }
    }
    
    
    /// #magic square generator function
    /// 
    /// A simple function generates magic square for a given sum number
    /// [`magic_square`]
    /// Calculate a simple 3x3 magic square based on given sum value. 
    pub fn magic_square(sum : i32) -> [i32;9]{
        let mut msq = [1, 2, 3, 4, 5, 6, 7, 8, 9];
        let mut rng = thread_rng();
        
        if (sum - 15) % 3 != 0{
            println!("Unable to find magic square with the sum {sum}.");
            return msq;
        }
        let addum = (sum - 15) / 3;
        if addum < 0{
            println!("Cannot find magic square less than 3x3 perfect, sorry!");
            return msq;
        }
        for i in 0..9 {
            msq[i] += addum;
        }
        let mut eq_count = 0;
        while eq_count != 8 {
            for i in 0..9 {
                let tmpidx = rng.gen::<usize>() % 9;
                let tmp = msq[tmpidx];
                msq[tmpidx] = msq[i];
                msq[i] = tmp;
            }
            if (msq[0] + msq[1] + msq[2]) == sum {
                eq_count += 1;
            }
            else{
                eq_count = 0;
                continue;
            }
            if (msq[3] + msq[4] + msq[5]) == sum {
                eq_count += 1;
            }
            else{
                eq_count = 0;
                continue;
            }
            if (msq[6] + msq[7] + msq[8]) == sum {
                eq_count += 1;
            }
            else{
                eq_count = 0;
                continue;
            }
            if (msq[0] + msq[3] + msq[6]) == sum {
                eq_count += 1;
            }
            else{
                eq_count = 0;
                continue;
            }
            if (msq[1] + msq[4] + msq[7]) == sum {
                eq_count += 1;
            }
            else{
                eq_count = 0;
                continue;
            }
            if (msq[2] + msq[5] + msq[8]) == sum {
                eq_count += 1;
            }
            else{
                eq_count = 0;
                continue;
            }
            if (msq[0] + msq[4] + msq[8]) == sum {
                eq_count += 1;
            }
            else{
                eq_count = 0;
                continue;
            }
            if (msq[2] + msq[4] + msq[6]) == sum {
                eq_count += 1;
            }
            else{
                eq_count = 0;
                continue;
            }
        }
        return msq;
    }
    
    /// Arithmetic series nth term sum function
    /// .
    pub fn sumnterms(ft : u32, n : u32, d : u32) -> u32{
        return ((2 * ft) + (n - 1)) * d * n / 2;
    }
    
    /// Simple exponent function to calculate power of integer. 
    pub fn power(base : u32, mut exp : u32) -> u32{
        let mut prod = 1;
        while exp > 0{
            prod *= base;
            exp -= 1;
        }
        return prod;
    }
    
    /// `power` function calculate multiple times of `base`, `exp` exponent is unsigned integer
    pub fn power(base : f32, mut exp : u16) -> f32 {
        // product of power
        let mut prod : f32 = 1.0;
        while exp > 0 {
            prod *= base;
            exp -= 1;
        }
        return prod;
    }
    
    /// `digitprd` function returns product of digits decimal values as n digits in `ndigs`. 
    pub fn digitprod(digits : &str, ndigs : usize) -> i64 {
        let dgs = digits.as_bytes();
        let zero = b'0';
        let mut maxsum :i64 = 0;
        for i in 0.. (dgs.len() - ndigs){
            let mut sum : i64 = 1;
            for j in 0..ndigs{
                sum *= (dgs[i + j] - zero) as i64;
            }
            if maxsum < sum{
                maxsum = sum;
            }
        }
        return maxsum;
    }
    
    /// Sum the digit in `n`, `todigit` true is for sum all digits to single digit, otherwise only do sum once
    pub fn sum2digit(mut n : u64, todigit : bool) -> u64 {
        if n < 10{
            return n;
        }
        let mut sum = 0;
        while n > 0 {
            sum += n % 10;
            n /= 10;
        }
        if todigit && sum > 10{
            return sum2digit(sum, true);
        }
        sum
    }
    
    /// Pythagorean triplet function return valid pythagoras value pair of 3 whose sum is `sum`. 
    pub fn pythagorean_triplet(sum : u32) -> (u32, u32, u32) {
        let mut rng = thread_rng();
        loop {
            let first = rng.gen::<u32>() % sum;
            let second = rng.gen::<u32>() % sum;
            if first + second > sum {
                continue;
            }
            let third = sum - (first + second);
            if first == 0 || second == 0 || third == 0 {
                continue;
            }
            let maxnum = max(first, second, third);
            if maxnum == first{
                if power(first, 2) == (power(second, 2) + power(third, 2)){
                    return (first, second, third);
                }
            }
            else if maxnum == second{
                if power(second, 2) == (power(first, 2) + power(third, 2)){
                    return (second, first, third);
                }
            }
            else{
                if power(third, 2) == (power(first, 2) + power(second, 2)){
                    return (third, first, second);
                }
            }
        }
    }
    
    /*
    /// Simple max function to return maximum of `x`, `y`, and `z`. 
    pub fn max(x : u32, y : u32, z : u32) -> u32 {
        if x > y {
            if x > z{
                return x;
            }
            else{
                return z;
            }
        }
        else{
            if y > z{
                return y;
            }
            else{
                return z;
            }
        }
    }
    */
    
    use std::cmp::PartialOrd;
    
    /// Simple generic max function to return maximum of `x`, `y`, and `z`. 
    pub fn max<T : PartialOrd>(t1 : T, t2 : T, t3 : T) -> T{
        if t1 > t2{
            if t1 > t3{
                return t1;
            }
            else{
                return t3;
            }
        }
        else{
            if t2 > t3{
                return t2;
            }
            else{
                return t3;
            }
        }
    }
    
    
    #[derive(PartialEq)]
    /// Enum for directions in two dimensional array
    pub enum Direction { 
        /// `Horizontal` horizontal slice of array
        Horizontal, 
        /// `Vertical` vertical slice of array
        Vertical, 
        /// `DiagonalUp` upward diagonal slice of array
        DiagonalUp, 
        /// `DiagonalDown` downward diagonal slice of array
        DiagonalDown, }
    
    /// Get slice of two dimensional array by slice length
    pub fn nslice<T : Copy>(arr : &Vec<T>, len : usize, width : usize, slen : usize, r : usize, c : usize, d: Direction) -> Vec<T>{
        let mut found : Vec<T> = Vec::new();
        let alen = arr.len();
        if slen == 0 || alen != (len * width) || ((r+slen) >= len && d == Direction::DiagonalDown) || ((c+slen) >= width && d == Direction::DiagonalUp) {
            return found;
        }
        for i in 0..slen{
            let mut row = r;
            let mut col = c;
            if d == Direction::Horizontal { 
                col += i;
            }
            else if d == Direction::Vertical { 
                row += i;
            }
            else if d == Direction::DiagonalUp {
                row -= i; 
                col += i;
            }
            else if d == Direction::DiagonalDown {
                row += i; 
                col += i;
            }
            let num = arr[row * len + col];
            found.push(num);
        }
        return found;
    }
    
    /// Horizontally sliced and calculate maximum sum of slices
    pub fn horizontal_max<T : Copy + PartialOrd + std::ops::AddAssign + Default>(arr : &Vec<T>, len : usize, slen : usize) -> Vec<T>{
        let mut max : T = create::<T>();
        let mut v : Vec<T> ;
        let mut vmax : Vec<T> = Vec::new();
        for r in 0..len {
            for c in 0.. (len - slen){
                v = nslice(arr, len, len, slen, r, c, Direction::Horizontal);
                let sum = sum_array(&v, slen);
                if max < sum{
                    max = sum;
                    vmax = v;
                }
            }
        }
        return vmax;
    }
    
    /// Vertically sliced and calculate maximum sum of slices
    pub fn vertical_max<T : Copy + PartialOrd + std::ops::AddAssign + Default>(arr : &Vec<T>, len : usize, slen : usize) -> Vec<T>{
        let mut max : T = create::<T>();
        let mut v : Vec<T> ;
        let mut vmax : Vec<T> = Vec::new();
        for r in 0..(len - slen) {
            for c in 0.. len {
                v = nslice(arr, len, len, slen, r, c, Direction::Vertical);
                let sum = sum_array(&v, slen);
                if max < sum{
                    max = sum;
                    vmax = v;
                }
            }
        }
        return vmax;
    }
    
    /// Upward diagonally sliced and calculate maximum sum of slices
    pub fn udiagonal_max<T : Copy + PartialOrd + std::ops::AddAssign + Default>(arr : &Vec<T>, len : usize, slen : usize) -> Vec<T>{
        let mut max : T = create::<T>();
        let mut v : Vec<T> ;
        let mut vmax : Vec<T> = Vec::new();
        for r in (slen-1)..len {
            for c in 0.. (len - slen) {
                v = nslice(arr, len, len, slen, r, c, Direction::DiagonalUp);
                let sum = sum_array(&v, slen);
                if max < sum{
                    max = sum;
                    vmax = v;
                }
            }
        }
        return vmax;
    }
    
    /// Downward diagonally sliced and calculate maximum sum of slices
    pub fn ddiagonal_max<T : Copy + PartialOrd + std::ops::AddAssign + Default>(arr : &Vec<T>, len : usize, slen : usize) -> Vec<T>{
        let mut max : T = create::<T>();
        let mut v : Vec<T> ;
        let mut vmax : Vec<T> = Vec::new();
        for r in 0.. (len - slen) {
            for c in 0.. (len - slen) {
                v = nslice(arr, len, len, slen, r, c, Direction::DiagonalDown);
                let sum = sum_array(&v, slen);
                if max < sum{
                    max = sum;
                    vmax = v;
                }
            }
        }
        return vmax;
    }
    
    /// Sum array
    pub fn sum_array<T : Copy + std::ops::AddAssign + Default>(arr : &Vec<T>, len : usize) -> T{
        let mut sum : T = create::<T>(); 
        for i in 0..len{
            sum += arr[i];
        }
        return sum;
    }
    
    fn create<T: Default>() -> T
    {
        T::default()
    }
}

