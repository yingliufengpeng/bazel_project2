use std::alloc::{alloc, dealloc, Layout};
use std::marker::PhantomData;
use std::ptr;

struct MyBox<T> {
    ptr: *mut T,              // 指向堆上分配的内存
    _marker: PhantomData<T>,  // 告诉编译器拥有 T
}

impl<T> MyBox<T> {
    fn new(value: T) -> Self {
        let layout = Layout::new::<T>();
        unsafe {
            // 手动分配内存
            let ptr = alloc(layout) as *mut T;
            if ptr.is_null() {
                std::alloc::handle_alloc_error(layout);
            }

            // 将 value 放到分配的内存里
            ptr::write(ptr, value);

            MyBox {
                ptr,
                _marker: PhantomData,
            }
        }
    }

    fn get(&self) -> &T {
        unsafe { &*self.ptr }
    }

    fn get_mut(&mut self) -> &mut T {
        unsafe { &mut *self.ptr }
    }
}

impl<T> Drop for MyBox<T> {
    fn drop(&mut self) {
        unsafe {
            // 手动调用 drop
            ptr::drop_in_place(self.ptr);

            // 释放内存
            dealloc(self.ptr as *mut u8, Layout::new::<T>());
            println!("MyBox dropped");
        }
    }
}




#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_my_box() {
        let mut b = MyBox::new(123);
        println!("value = {}", b.get());

        *b.get_mut() = 456;
        println!("value = {}", b.get());
    }
}
