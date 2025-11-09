use std::marker::PhantomPinned;
use std::ops::{Deref, DerefMut};

#[derive(Debug)]
struct SelfRef {
    v: String,
    ptr: *const String,
    _pin: PhantomPinned, // marker
}

impl SelfRef {
    pub fn new(v: String) -> Self {
        Self {
            v,
            ptr: std::ptr::null(),
            _pin: PhantomPinned,
        }
    }

    pub fn correct_ptr(&mut self) {
        self.ptr = &self.v;
    }
}

fn create_self_ref(v: String) -> SelfRef {
    let mut res = SelfRef::new(v);
    res.correct_ptr();
    println!("xxx - {}", unsafe { &*res.ptr });

    res
}


pub struct MyPin<Ptr> {
    ptr: Ptr,
}

impl<Ptr: Deref> MyPin<Ptr> { // Ptr 需要是一个指针类型
    pub fn new(ptr: Ptr) -> Self {
        Self { ptr }
    }
}


impl<Ptr: Deref> Deref for MyPin<Ptr> {
    type Target = Ptr::Target;
    fn deref(&self) -> &Self::Target {
        self.ptr.deref()
    }
}

impl<Ptr: DerefMut<Target: Unpin>> DerefMut for MyPin<Ptr> {
    fn deref_mut(&mut self) -> &mut Self::Target {
        self.ptr.deref_mut()
    }
}

impl<Ptr: DerefMut> MyPin<Ptr> {
    // as_mut 的主要作用是解决生命周期的问题, 因为 Ptr 没有生命周期, 但是 &mut T 有
    // 建立起一个从 MyPin<Ptr> -> MyPin<&'a mut T> -> &'a mut T 的桥梁
    pub fn as_mut(&mut self) -> MyPin<&mut Ptr::Target> {
        MyPin {
            ptr: &mut *self.ptr,
        }
    }
}

impl<'a, T> MyPin<&'a mut T> {
    // 对于 T: Unpin, 直接获取 &mut T
    pub fn get_mut(self) -> &'a mut T
    where
        T: Unpin,
    {
        self.ptr
    }

    // 对于 T: !Unpin, 通过 unsafe fn 获得 &mut T
    unsafe fn get_unchecked_mut(self) -> &'a mut T {
        self.ptr
    }
}

fn print(name: &str, pinned: &MyPin<Box<SelfRef>>) {
    println!(
        "addr of {name}.v: {:?}, value of {name}.ptr {:?}, value of {name}.v: {} , deref value of {name}.ptr: {}",
        &pinned.ptr.v as *const String,
        pinned.ptr.ptr,
        pinned.v,
        unsafe { &*pinned.ptr.ptr }
    );
}

impl SelfRef {
    pub fn say_string(&self) {
        unsafe {
            println!("My value is: {}", *self.ptr);
        }
    }


}

fn handle<T>(v: MyPin<T>) -> MyPin<T> {
    v
}


fn f2() {
    let mut a = Box::new(SelfRef::new("hello".to_string()));
    a.correct_ptr();
    let mut pinned_a = MyPin::new(a);

    let mut b = Box::new(SelfRef::new("world".to_string()));
    b.correct_ptr();
    let mut pinned_b = MyPin::new(b);

    print("a", &pinned_a);
    print("b", &pinned_b);

    unsafe {
        let a_mut = pinned_a.as_mut().get_unchecked_mut();
        let b_mut = pinned_b.as_mut().get_unchecked_mut();
        std::mem::swap(a_mut, b_mut);

        // 添加矫正逻辑. 手工
        a_mut.correct_ptr();
        b_mut.correct_ptr();
    }

    print("a", &pinned_a);
    print("b", &pinned_b);
}

fn f1() {
    // crate 2
    let sr = SelfRef::new("hello".to_string());
    let mut boxed = Box::new(sr);
    boxed.correct_ptr();
    let my_pinned_sr = MyPin::new(boxed);

    my_pinned_sr.say_string();
    println!("{}", my_pinned_sr.v);

    {

        let new_my_pinned_sr = handle(my_pinned_sr);
        new_my_pinned_sr.say_string();
    }




}

#[cfg(test)]
mod tests {
    use tokio::io::AsyncReadExt;
    use super::*;

    #[test]
    fn test_my() {
        f1();
        f2();

    }
}

