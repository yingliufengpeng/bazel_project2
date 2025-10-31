use std::ffi::CString;
use std::os::raw::c_char;
use tokio::time::{sleep, Duration};

pub  fn make_cstring(src: &String) -> *const c_char {
    let c_string = CString::new(src.as_str()).unwrap();
    c_string.into_raw() // ✅ 转移所有权
}

pub fn add(x: i32, y: i32) -> i32 {
    x + y
}

pub fn mul(x: &i32, y: &i32) -> i32 {
    x * y
}

pub fn choose<'a>(x: &'a i32, y: &'a i32) -> &'a i32 {
    if *x > *y { x } else { y }
}


async fn get_resource(url: &str) -> String {
    sleep(Duration::from_secs(2)).await;

    (url.to_string() + ".zip").to_string()
}

async fn download(url: &str) -> String {

    let path = get_resource(url).await;

    println!("Downloading {}", path);

    format!("New Path : {}", path)


}


pub fn process_url(url: &str) {
    let result = tokio::runtime::Runtime::new()
        .unwrap()
        .block_on(download(url));
    println!("Result = {:?}", result);

}

