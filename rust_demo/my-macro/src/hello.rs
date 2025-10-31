use quote::quote;
use proc_macro::{TokenStream, TokenTree};
use syn::{parse_macro_input, DeriveInput};
use venial::{parse_declaration, Declaration, Struct, Enum};


// pub fn hello_impl(_item: TokenStream) -> TokenStream {
//     let ast = parse_macro_input!(_item as DeriveInput);
//     let name = ast.ident;
//     let add_hello_world = quote! {
//         impl #name {
//              fn hello_world(&self) {
//                 println!("Hello, World")
//              }
//              }
//
//       };
//     add_hello_world.into()
//
// }


// pub fn hello_impl(item: TokenStream) -> TokenStream {
//     fn ident_name(item: TokenTree) -> String {
//         match item {
//             TokenTree::Ident(i) => i.to_string(),
//             _ => panic!("no ident")
//         }
//     }
//     let name = ident_name(item.into_iter().nth(1).unwrap());
//
//     format!("impl {} {{ fn hello_world(&self) \
//     {{ println!(\"Hello world\") }} }} ", name
//     ).parse()
//         .unwrap()
// }

pub fn hello_impl(item: TokenStream) -> TokenStream {
    let declaration = parse_declaration(item.into()).unwrap();

    let name = match declaration {
        Declaration::Struct(Struct { name, .. }) => name,
        Declaration::Enum(Enum { name, .. }) => name,
        _ => panic!("only implemented for struct and enum")
    };

    let add_hello_world = quote! {
        impl #name {
            fn hello_world(&self) {
                println!("Hello {}", stringify!(#name));
            }

            fn testing_testing() {
                println!("one two three");
            }
        }
    };

    add_hello_world.into()
}


pub fn uppercase_impl(item: TokenStream) -> TokenStream {
    let ast = parse_macro_input!(item as DeriveInput);
    let name = ast.ident;
    let uppercase_name = name.to_string().to_uppercase();

    let add_uppercase = quote! {
        impl #name {
            fn uppercase(&self) {
                println!("{}", #uppercase_name);
            }
        }
    };
    add_uppercase.into()
}