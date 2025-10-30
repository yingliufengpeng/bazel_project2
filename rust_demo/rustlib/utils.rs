use std::ffi::CString;
use std::os::raw::c_char;

pub  fn make_cstring(src: &String) -> *const c_char {
    let c_string = CString::new(src.as_str()).unwrap();
    c_string.into_raw() // ✅ 转移所有权
}

pub fn add(x: i32, y: i32) -> i32 {
    x + y
}