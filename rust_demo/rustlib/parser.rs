use std::cell::Cell;
use std::marker::PhantomData;
use std::rc::Rc;
use syn::{
    parse::Result,
    spanned::Spanned,
};


// 模拟 syn::Cursor —— 指向剩余输入的游标
#[derive(Clone, Copy, Debug)]
pub struct Cursor<'a> {
    // 指向剩余未解析的输入
    rest: &'a str,
    _marker: PhantomData<Cursor<'a>>,

}

impl <'a> Cursor<'a> {
    fn new (rest: &'a str) -> Self {
        Cursor{
            rest: rest,
            _marker: PhantomData,
        }
    }

    fn get_rest(&self, advance: usize) -> &'a str {
        &self.rest[advance..]
    }
}




// 关键：ParseBuffer
pub struct ParseBuffer<'a> {
    // 当前解析位置（用 'static 存储）
    cell: Cell<Cursor<'a>>,
    // 告诉编译器：我们“名义上”持有 'a 数据
    _marker: PhantomData<Cursor<'a>>,
}

impl Drop for ParseBuffer<'_> {
    fn drop(&mut self) {
        println!("Dropping ParseBuffer");
        let _ = self.cell.get();

    }
}

impl <'a> ParseBuffer<'a> {

    fn new(cursor: Cursor<'a>) -> ParseBuffer<'a> {
        ParseBuffer{
            cell: Cell::new(cursor),
            _marker: PhantomData,
        }
    }

    fn peek(&self) -> Cursor<'a> {
        // let c = self.cell.get();
        self.cell.clone().get()

    }

    fn parse(&self) -> Cursor<'a> {

        let c = self.cell.get();
        let r = Cursor::new(c.get_rest(1));
        self.cell.set(r);
        // m.rest = &m.rest[1..];

        parse_impl(self, self);


        {
            let fork = self.fork();
            let fork2 = self.fork();
            parse_impl(&fork2, &fork2);
        }

        r
    }


    fn fork(&self) -> ParseBuffer<'a> {
        ParseBuffer{
            cell: self.cell.clone(),
            _marker: PhantomData,
        }
    }



}


fn parse_impl<'b, 'a: 'b>(m: &'b ParseBuffer<'a>, n: &'b ParseBuffer<'a>) {

}

struct ParamArgs {
    args: syn::AttributeArgs,
}

impl syn::parse::Parse for ParamArgs {
    fn parse(input: syn::parse::ParseStream) -> Result<Self> {
        let punctuated = <syn::punctuated::Punctuated<_, syn::Token![,] >>::parse_terminated(input)?;
        Ok(Self {
            args: punctuated.into_iter().collect::<Vec<_>>(),
        })
    }
}



#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_my() {
        let stream = "abcdaafsfsfafsfasfafsfs";
        let p1 = ParseBuffer::new(Cursor{rest: stream, _marker: PhantomData});

        println!("begin parsing:  {:?}", p1.peek());

        for i in 0..3 {
            let c = p1.parse();
            println!("c is {:?}", c)
        }

    }
}

