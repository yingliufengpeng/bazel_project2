use proc_macro::TokenStream;
use syn::{parse_macro_input, LitStr, Token, punctuated::Punctuated, Ident};
use quote::quote;


pub fn multi_args_impl(input: TokenStream) -> TokenStream {
    // 用 Punctuated 解析逗号分隔列表
    let args = parse_macro_input!(input with Punctuated::<syn::Expr, Token![,]>::parse_terminated);

    let mut iter = args.iter();

    // 取第一个字符串字面量
    let first = iter.next().expect("Expected at least one argument");
    let msg = if let syn::Expr::Lit(expr_lit) = first {
        if let syn::Lit::Str(litstr) = &expr_lit.lit {
            litstr.value()
        } else {
            panic!("First argument must be a string literal");
        }
    } else {
        panic!("First argument must be a string literal");
    };

    // 处理后续参数，直接打印标识符名字
    let extras: Vec<_> = iter.map(|e| {
        if let syn::Expr::Path(p) = e {
            let ident = &p.path.segments.first().unwrap().ident;
            quote! { println!("Extra: {}", stringify!(#ident)); }
        } else {
            quote! {}
        }
    }).collect();

    let expanded = quote! {
        fn hello() {
            println!("Hello, {}", #msg);
            #(#extras)*
        }
    };

    expanded.into()
}
