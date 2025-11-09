use std::ffi::CString;
use std::fs::File;
use std::os::raw::c_char;
use tempfile::NamedTempFile;
use std::io::{Cursor, Write, Seek, SeekFrom, copy};
use std::ffi::CStr;

mod utils;
mod tools;
mod node;
mod tree;
mod calculator;
mod common;
mod mybox;
mod parser;
mod func;
mod pin;

#[repr(C)]
pub struct Person {
    name: *const c_char,
    age: i32,
}

#[derive(Debug)]
enum Mode {
    Push,
    Pop,
}

#[derive(Debug)]
struct Student {
    name: String,
    age: i32,
    mode: Mode,
    vec: Vec<String>,
}

impl Student {
    pub fn new(name: String, age: i32) -> Self {
        Student { name, age, vec: vec![], mode: Mode::Push }
    }

    pub fn add(&mut self, message: String) {
        self.vec.push(message);
    }
}

#[no_mangle]
pub extern "C" fn make_person() -> Person {
    let name = CString::new("Alice").unwrap_or_else(|_| CString::new("Invalid").unwrap());
    let p = Person {
        name: name.into_raw(),
        age: 30,
    };

    // Rust 调用模块方法
    match (utils::add(3, 4), tools::mul(3, 4)) {
        (r, r2) => println!("r: {:?}, r2: {:?}", r, r2),
    }

    // Cursor -> 临时文件
    if let Err(e) = handle_temp_file() {
        eprintln!("临时文件处理失败: {}", e);
    }

    let mut m = Student::new("Alice".to_string(), 30);
    m.add("C++".to_string());
    m.add("Python".to_string());
    println!("Student: {:#?}", m);

    p
}

fn handle_temp_file() -> std::io::Result<()> {
    let mut cursor = Cursor::new(Vec::new());
    cursor.write_all(b"temporary data")?;
    cursor.seek(SeekFrom::Start(0))?;

    let mut tmp = NamedTempFile::new()?;
    println!("临时文件路径: {:?}", tmp.path());

    copy(&mut cursor, tmp.as_file_mut())?;

    // 工具模块中假设提供文件操作接口
    if let Err(e) = tools::fs::list_dir(tmp.as_file()) {
        eprintln!("list_dir 出错: {}", e);
    }

    Ok(())
}

#[no_mangle]
pub extern "C" fn rust_free_string(s: *mut c_char) {
    if s.is_null() {
        return;
    }
    unsafe {
        let _ = CString::from_raw(s);
    }
}


#[no_mangle]
pub extern "C" fn rust_make_string() -> *const c_char {
    let s = CString::new("这个函数在别的语言（C ABI）实现").unwrap();
    let p = s.as_ptr();
    std::mem::forget(s); // 避免 Rust 释放
    p
}

#[no_mangle]
pub extern "C" fn free_inner_person_ptr(p: *mut Person) {

    if p.is_null() {
        return;
    }
    unsafe {
        // let mut s = p -> name;
        let person: &Person = &*p;
        let c_str = CStr::from_ptr(person.name);
        println!("free string: {:?}", c_str.to_str().unwrap());


        let s: *mut c_char = person.name as *mut c_char;

        let _ = CString::from_raw(s as *mut c_char);
    }
}


#[no_mangle]
pub extern "C" fn make_person_ptr() -> *mut Person {
    let name = CString::new("正确方法：把 *const c_char 转成 Rust 字符串").unwrap();
    let p = Box::new(Person {
        name: name.into_raw(),
        age: 30,
    });
    Box::into_raw(p)
}

// 该方法目前没有用到，目前的上下文场景是在c++的环境中调用的代码
#[no_mangle]
pub extern "C" fn free_person_ptr(p: *mut Person) {

    if !p.is_null() {
        println!("Person is freeing ");
        unsafe {
            let p = Box::from_raw(p);
            if !p.name.is_null() {
                let _ = CString::from_raw(p.name as *mut c_char);
            }
        }
    }
}



#[no_mangle]
pub extern "C" fn process_img(path: *const c_char) -> *const c_char {
    unsafe {
        let cstr = CStr::from_ptr(path);
        let s = cstr.to_str().unwrap_or("<invalid utf8>");
        println!("Processing img: {}", s);
        let output = format!("Processed: {}", s);
        bar_add();
        utils::make_cstring(&output)
    }
}

extern "C" {
    fn foo_add(a: i32, b: i32) -> i32;
    fn getPoint(a: i32, b: i32, name: *const c_char) -> Point;
    fn freePersonInner(person: *mut Point);
}

#[repr(C)]
#[derive(Clone, Debug)]
struct Point {
    x: i32,
    y: i32,
    name: *const c_char

}

impl Point {
    pub fn show(self: &Point) {
        unsafe {
            let cstr = CStr::from_ptr(self.name as *const c_char);
            let s = cstr.to_str().unwrap_or("<invalid utf8>");
            println!("Point name: {}--{}--{}", self.x, self.y, s);
        }
    }
}

impl Drop for Point {
    fn drop(&mut self) {
        unsafe {
            freePersonInner(self)
        }
    }
}


fn bar_add() {
    unsafe {
        let point = getPoint(1, 2, CString::new("自动编译 cpp_core（包含所有 .cpp）").unwrap().into_raw());
        // print!("Point x: {}, y: {}", point.x, point.y);
        point.show();
        println!("foo_add(3,4) = {}", foo_add(3, 4));
    }
}

// use pyo3::prelude::*;
//
// #[pyclass]
// pub struct Person2 {
//     #[pyo3(get, set)]
//     pub name: String,
//     #[pyo3(get, set)]
//     pub age: u32,
// }
//
// #[pymethods]
// impl Person2 {
//     #[new]
//     fn new(name: String, age: u32) -> Self {
//         Person2 { name, age }
//     }
//
//     fn greet(&self) -> String {
//         format!("Hello, {} ({})", self.name, self.age)
//     }
// }
//
// #[pymodule]
// fn rust_demo2(m: &Bound<'_, PyModule>) -> PyResult<()> {
//     m.add_class::<Person2>()?;
//     Ok(())
// }
