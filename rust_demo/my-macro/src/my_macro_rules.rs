macro_rules! patterns {
    (pat: $pat:pat) => {
        println!("pat: {}", stringify!($pat));
    };
    (pat_param: $($pat:pat_param)|+) => {
        $( println!("pat_param: {}", stringify!($pat)); )+
    };
}

macro_rules! paths {
    ($($path:path)*) => {
        $(
          println!("paths is {:?}", stringify!($path));
        )*
    };
}

macro_rules! pats {
    ($($path:pat)*) => {
        $(
          println!("pats is {:?}", stringify!($path));
        )*
    };
}

macro_rules! types {
    ($($type:ty)*) =>  {
        $(
          println!("types is {:?}", stringify!($type));
        )*
    };
}

macro_rules! visibilities {
    //         ∨~~注意这个逗号，`vis` 分类符自身不会匹配到逗号
    ($($vis:vis,)*) => ();
}


fn _println(s: &str) {
    println!("s is {}", s);
}

macro_rules! it_is_opaque {
    (()) => { _println("()") };
    (($tt:tt)) => { _println(concat!("$tt is ", stringify!($tt))) };
    ($vis:vis ,) => { it_is_opaque!( ($vis) ) ; }
}



#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_1() {
        patterns! {
       pat: 0 | 1 | 2 | 3
    }
        patterns! {
       pat_param: 0 | 1 | 2 | 3
    }




        paths! {
        ASimplePath
        ::A::B::C::D
        G::<eneri>::C
        FnMut(u32) -> ()
        Fn(i32) -> i32
        FnOnce(u32) -> i32
    }


        pats! {
        ASimplePath
        ::A::B::C::D
        G::<eneri>::C
        FnMut(u32)
    }



        types! {
        foo::bar
        bool
        [u8]
        impl IntoIterator<Item = u32>
        FnOnce(u32) -> i32
    }



        visibilities! {
        , // 没有 vis 也行，因为 $vis 隐式包含 `?` 的情况
        pub,
        pub(crate),
        pub(in super),
        pub(in some_path),
    }

        it_is_opaque!{
        ,
    };

    }

}