use syn::{parse_macro_input};
use proc_macro::TokenStream;
use syn::{parse::Parser, ExprArray, LitStr};

pub fn get_impl(attr: TokenStream, item: TokenStream) -> TokenStream {
    let attr_clone = attr.clone();

    // 尝试先解析为单字符串
    if let Ok(lit) = syn::parse::<LitStr>(attr_clone.clone()) {
        let route = lit.value();
        return expand(vec![route], item);
    }

    // 否则解析为数组
    let array = syn::parse::<ExprArray>(attr_clone).expect("Expect string literal or array");
    let routes = array
        .elems
        .iter()
        .filter_map(|e| match e {
            syn::Expr::Lit(expr_lit) => match &expr_lit.lit {
                syn::Lit::Str(s) => Some(s.value()),
                _ => None,
            },
            _ => None,
        })
        .collect::<Vec<_>>();

    expand(routes, item)
}


fn expand(routes: Vec<String>, item: TokenStream) -> TokenStream {
    let func = syn::parse_macro_input!(item as syn::ItemFn);
    let func_name = &func.sig.ident;
    let fn_block = &func.block;

    let expanded = quote::quote! {
        fn #func_name() {
            #(
                println!("Matched route: {}", #routes);
            )*
            let result = (|| #fn_block)();
            result
        }
    };

    expanded.into()
}