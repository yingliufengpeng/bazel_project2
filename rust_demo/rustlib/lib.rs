use std::ffi::CString;
use std::os::raw::c_char;

#[repr(C)]
pub struct Person {
    name: *const c_char,
    age: i32,
}

#[derive(Debug)]
struct Student {
    name: String,
    age: i32,
    vec: Vec<String>,
}

fn main() {
    let p = Person {
        name: "Alice".to_string(),
        age: 30,
        vec: vec!["C++".to_string(), "Rust".to_string()],
    };

    println!("{:?}", p);
}

impl Student {
    pub fn new(name: String, age: i32) -> Self {
        Person { name, age, vec: vec![] }
    }

    pub fn add(&mut self, message: String) {
        self.vec.push(message);
    }

}

#[no_mangle]
pub extern "C" fn make_person() -> Person {
    let name = CString::new("Alice").unwrap();
    let p = Person {
        name: name.into_raw(),  // 将 CString 转为裸指针
        age: 30,
    };

    let mut m = Student::new(name.into_raw(), 30);
    m.add("C++".to_string());
    m.add("Python");
    println!("Student: {#?}", m);
    p
}
#[no_mangle]
pub extern "C" fn free_person_name(s: *mut c_char) {
    if s.is_null() { return; }
    unsafe { CString::from_raw(s); } // 回收内存
}
