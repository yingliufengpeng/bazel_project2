use std::ffi::CString;
use std::os::raw::c_char;

#[repr(C)]
pub struct Person {
    name: *const c_char,
    age: i32,
}

#[no_mangle]
pub extern "C" fn make_person() -> Person {
    let name = CString::new("Alice").unwrap();
    let p = Person {
        name: name.into_raw(),  // 将 CString 转为裸指针
        age: 30,
    };
    p
}
#[no_mangle]
pub extern "C" fn free_person_name(s: *mut c_char) {
    if s.is_null() { return; }
    unsafe { CString::from_raw(s); } // 回收内存
}
