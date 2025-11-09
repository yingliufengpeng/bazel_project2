use std::marker::PhantomData;
use crate::utils;

#[derive(Debug)]
struct Calculator<'a> {
    cache: Vec<i32>,
    str: &'a str,
    _maker: PhantomData<&'a str>,
}


impl<'a> Calculator<'a> {

    pub fn new(str: &'a str) -> Self {
        Self { cache: vec![], str, _maker: PhantomData }
    }

    /// 按值返回结果（安全、简单）
    fn div_value(&mut self, x: i32, y: i32) -> i32 {
        let r = x / y;
        self.cache.push(r);
        r
    }


    fn last_result(& self) -> Option<&i32> {
        self.cache.last()
    }

    /// 更复杂：传入引用参数，返回一个引用到内部缓存的结果
    fn div_ref(&mut self, x: &i32, y: &i32) -> &i32 {
        let r = *x / *y;
        self.cache.push(r);
        self.cache.last().unwrap()
    }
}



#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_tree() {
        let s = format!("{}", "hello, world");
        let mut calc = Calculator::new(&s);

        let x = 20;
        let y = 5;

        // {
        //     let s = format!("{}", "hello, world");
        //
        //     calc.str = &s;
        // }

        let s2 = format!("ee");
        calc.str = s2.as_str();
        // 返回值方式
        let v = calc.div_value(x, y);
        println!("div_value = {}", v);

        // 引用返回方式
        let r = calc.div_ref(&x, &y);
        println!("div_ref (from cache) = {}", r);

        // 读取缓存中的最后结果
        if let Some(last) = calc.last_result() {
            println!("last_result = {}", last);
        }

        // cache 存储多个结果
        println!("cache = {:?}", calc.cache);

    }

    #[test]
    fn test_async() {
        utils::process_url("https://www.google.com/cc_library/v1.2.3.zip");

    }

    #[tokio::test(flavor = "multi_thread", worker_threads = 4)]
    async fn test_mul_process() {
        utils::multi_process("https://www.google.com/rules_python/v1.2.3.zip").await;
    }
}