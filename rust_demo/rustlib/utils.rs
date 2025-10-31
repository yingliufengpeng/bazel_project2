use std::ffi::CString;
use std::os::raw::c_char;
use tokio::time::{sleep, Duration};
use tokio::sync::mpsc;
use rand::SeedableRng;
use rand::rngs::StdRng;
use rand::Rng; // 用于使用 gen_range 等 Rng 方法

use std::sync::Arc;


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

pub async fn download(url: &str) -> String {

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



pub async fn multi_process(url: &str) {
    let url = Arc::new(url.to_string());

    // 创建异步通道 (sender, receiver)
    let (tx, mut rx) = mpsc::channel::<String>(100);

    // 启动多个生产者任务
    for id in 0..3 {
        let tx_clone = tx.clone();
        let url = Arc::clone(&url);

        tokio::spawn(async move {
            let mut rng = StdRng::from_os_rng();

            download(&url).await;
            for i in 0..5 {
                // 模拟异步计算
                let delay = rng.gen_range(200..800);
                sleep(Duration::from_millis(delay)).await;
                let msg = format!("Producer-{id} -> item-{i}");
                if tx_clone.send(msg).await.is_err() {
                    println!("channel closed");
                    return;
                }
            }
        });
    }

    // 主任务充当消费者
    drop(tx); // 关闭发送端，防止死锁
    println!("Consumer waiting for messages...");

    while let Some(msg) = rx.recv().await {
        println!("[Consumer] got: {}", msg);
    }

    println!("All producers done, channel closed.");
}

