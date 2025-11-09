
#[derive(Debug)]
struct M<T> {
    value: T
}

impl <T> M<T> {

    fn as_mut<'a>(&'a mut self) -> M<&'a mut T> {
        M{value: & mut self.value}
    }

    // 下面是等价的写法
    fn as_mut_alt(& mut self) -> M<&mut T> {
        M{value: & mut self.value}
    }
}

impl <'a, T> M<&'a mut T> {

    fn as_ref2<'b:'a>(&'b mut self) -> &'a mut T {
        self.value
    }

    fn as_ref(self) -> &'a mut T {
        self.value
    }


}


fn f1() {
    let mut m = M { value: 42 };
    let mut n = m.as_mut();
    println!("{:?}", n);
    let c = n.as_ref();
    println!("{:?}", c);
}

fn f2() {
    let mut m = M { value: 42 };
    let mut n = m.as_mut();
    println!("{:?}", n);
    let c = n.as_ref2();

    println!("{:?}", c);
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_my_borow_rule() {
        f1();
        f2();

    }
}