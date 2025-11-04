use std::cell::Cell;
use std::marker::PhantomData;
use std::ops::Deref;

type DynFunc = dyn Fn(i32) -> i32;
type VBoxFunc = Vec<Box<dyn Fn(i32) -> i32>>;
type VFunc = Vec<fn(i32) -> i32>;

#[derive(Debug,    )]
struct Cursor<'a> {
    pos: usize,
    src: &'a str,
}
// impl <'a> Drop for Cursor<'a> {
//     fn drop(&mut self) {
//         println!("Cursor out of bounds");
//     }
// }


#[derive(Debug)]
struct MImp {
    i: i32,
    j: i32,
}

impl Copy for MImp {}

impl Clone for MImp {
    fn clone(&self) -> Self {
        *self
        // println!("触发clone开发...");
        // Self {
        //     i: self.i,
        //     j: self.j,
        // }

    }
}

struct M<T> {
    a: T
}

impl<T> Deref for M<T> {

    type Target = T;
    fn deref(&self) -> &Self::Target {
        &self.a
    }
}



impl<'a> Copy for Cursor<'a> {}

impl<'a> Clone for Cursor<'a> {
    fn clone(&self) -> Self {
        Self {
            pos: 0,
            src: "",
        }
    }
}


struct ParseBuffer<'a> {
    src: &'a str,
    cell: Cell<Cursor<'static>>,
    marker: PhantomData<Cursor<'a>>,
}



impl<'a> ParseBuffer<'a> {


}

impl<'a> Drop for ParseBuffer<'a> {
    fn drop(&mut self) {
        let _ = self.cell.get();
    }
}


trait Work<T> where T: Default {
    fn work(&self) -> T;
}

fn f1() {
    // let code = String::from("hello");
    let buf = ParseBuffer {
        src: "hello world",
        cell: Cell::new(Cursor { pos: 0, src: "fsfsfsf" }),
        marker: PhantomData,
    };

    let c = buf.cell.get();

    let s1 = "ddd".to_string();
    let s2 = s1.to_owned();

    println!("s1 is {:?}", s1);
    println!("s2 is {:?}", s2);

    let mut m = M{a: MImp{i: 0, j: 0}};
    println!("m {:?}", m.a);
    let c = *m;
    m.a.i = 44;
    println!("c {:?}", c);
    println!("m.a {:?}",  m.a);

    let c = *m;
    println!("c {:?}", c);

    let mut v: Vec<Box<dyn Fn(i32)->i32>> = Vec::new();

    for i in 0..3 {
        let f = |e: i32| {e + 3};
        v.push(Box::new(f));
    }
    //
    v.iter().for_each( |f   |  {
        f(4);

    });


    fn apply(f: &DynFunc, v: i32) -> i32 {
        f(v)
    }

    fn add(a: i32) -> i32 {
        a + 1
    }


    let offset = 2;
    let c = move  |x: i32| {

        let s1 = format!("file: {}, line: {}", file!(), line!());
        println!("{}", s1);
        x + offset
    };

    fn push_f(vec: &mut VBoxFunc) {
        let s1 = format!("file: {}, line: {}", file!(), line!());
        println!("vec pushed in {}", s1);
        let c = move  |x: i32| {
            println!("s1 is {:?}", s1);
            x + 4
        };
        vec.push(Box::new(c));
    }

    let mut vvs = VFunc::new();
    vvs.push(|e| {e + 3});
    vvs.push(add);

    vvs.iter().for_each(|f| {
        apply(f, 4);
    });

    let mut vvs_clouse = VBoxFunc::new();
    vvs_clouse.push(Box::new(c));

    push_f(&mut vvs_clouse);

    vvs_clouse.iter().for_each(|f| {
        apply(f, 4);
    });

}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_my_box() {
        f1();
    }
}