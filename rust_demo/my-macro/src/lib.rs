extern crate proc_macro;
use proc_macro::TokenStream;

use quote::quote;
use syn::{parse_macro_input, ItemFn};

mod hello;

/// 一个简单属性宏，打印函数开始和结束
#[proc_macro_attribute]
pub fn log_fn(_attr: TokenStream, item: TokenStream) -> TokenStream {
    // 解析输入为一个函数
    let input = parse_macro_input!(item as ItemFn);

    let fn_name = &input.sig.ident;
    let fn_block = &input.block;
    let fn_sig = &input.sig;

    // 生成新的函数代码
    let expanded = quote! {
        #fn_sig {
            println!("Entering function: {}", stringify!(#fn_name));
            let result = (|| #fn_block)();
            println!("Exiting function: {}", stringify!(#fn_name));
            result
        }
    };

    TokenStream::from(expanded)
}


#[proc_macro_derive(Hello)]
pub fn hello_world(_item: TokenStream) -> TokenStream {
    hello::hello_impl(_item)
}


#[proc_macro_derive(UpperCaseName)]
pub fn uppercase(item: TokenStream) -> TokenStream {
    hello::uppercase_impl(item)
}