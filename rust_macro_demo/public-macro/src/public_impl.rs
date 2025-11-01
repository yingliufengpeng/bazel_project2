use proc_macro::TokenStream;

use quote::quote;
use syn::{DataStruct, DeriveInput, FieldsNamed, Ident, LitStr, MetaList, parse_macro_input, Token};
use syn::Data::Struct;
use syn::Fields::Named;
use syn::parse::Parse;
use syn::parse::ParseStream;
use syn::meta::ParseNestedMeta;
use syn::token::Group;
use syn::PathArguments::Parenthesized;
use syn::punctuated::Punctuated;
use syn::PathSegment;
use syn::parse::Parser;


use super::fields::{AlternativeExcludedFields, ExcludedFields};

pub fn public(attr: TokenStream, item: TokenStream) -> TokenStream {
    let ast = parse_macro_input!(item as DeriveInput);

    // let excluded_fields = parse_macro_input!(attr as ExcludedFields);

    let mut excluded_fields = AlternativeExcludedFields::default();
    let attr_parser = syn::meta::parser(|meta| excluded_fields.parse(meta));
    parse_macro_input!(attr with attr_parser);

    let name = ast.ident;

    let fields = match ast.data {
        Struct(
            DataStruct {
                fields: Named(
                    FieldsNamed {
                        ref named, ..
                    }), ..
            }
        ) => named,
        _ => unimplemented!(
            "only works for structs with named fields"
        ),
    };

    let builder_fields = fields.iter().map(|f| {
        let name = &f.ident;
        let ty = &f.ty;
        let vis = &f.vis;

        if excluded_fields.matches_ident(name) {
            quote! { #vis #name: #ty }
        } else {
            quote! { pub #name: #ty }
        }
    });

    let public_version = quote! {
        pub struct #name {
            #(#builder_fields,)*
        }
    };

    public_version.into()
}