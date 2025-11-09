use std::cell::Cell;
use std::error;
use std::fmt::Display;
use std::marker::PhantomData;
use std::ops::Deref;
use std::rc::Rc;
use syn::{

    spanned::Spanned,
};

struct Error {
    messages: Vec<String>,
}


pub type Result<T> = std::result::Result<T, Error>;


type ParseStream<'x> = &'x ParseBuffer<'x>;

trait Parse: Sized {
    fn parse(input: ParseStream) -> Result<Self>;
}

// 模拟 syn::Cursor —— 指向剩余输入的游标
#[derive(Clone, Copy, Debug)]
pub struct Cursor<'a> {
    // 指向剩余未解析的输入
    rest: &'a str,
    _marker: PhantomData<Cursor<'a>>,

}

#[derive(Clone, Copy, Debug)]
struct StepCursor<'c, 'a> {
    cursor: Cursor<'c>,
    _marker: PhantomData<fn(Cursor<'c>) -> &'a Cursor<'a>>,
}

impl <'c, 'a> Deref for StepCursor<'c, 'a> {
    type Target = Cursor<'c>;
    fn deref(&self) -> &Self::Target {
        &self.cursor
    }


}


impl <'c, 'a> StepCursor<'c, 'a> {
    pub fn error<T: Display>(self, message: T) -> Error {
        Error{
            messages: vec![message.to_string()],
        }
    }
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

    pub fn punct(mut self) -> Option<(Punct, Cursor<'a>)> {
        let p = Punct{ch: 'a'};
        let cursor = Cursor::new(&self.rest[1..]);
        Some((p, cursor))
        // unimplemented!()

    }
}


// 关键：ParseBuffer
pub struct ParseBuffer<'a> {
    // 当前解析位置（用 'static 存储）
    cell: Cell<Cursor<'static>>,
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

    fn new(cursor: Cursor<'static>) -> ParseBuffer<'a> {
        ParseBuffer{
            cell: Cell::new(cursor),
            _marker: PhantomData,
        }
    }


    fn is_empty(&self) -> bool {
        self.cell.get().rest.is_empty()
    }

    fn peek(&self) -> Cursor<'a> {
        // let c = self.cell.get();
        self.cell.clone().get()

    }


    fn step<F, R>(&self, function: F) -> Result<R>
    where F: for <'c> FnOnce(StepCursor<'c, 'a>) -> Result<(R, Cursor<'c>)>,
    {

        let (res, others) = function(StepCursor{
            cursor: self.cell.get(), // cell.get() is to copy the value of cell
            _marker: PhantomData,
        })?;

        self.cell.set(others);

        Ok(res)

    }

    fn parse<T: Parse>(&self) -> Result<T> {
        T::parse(self)
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

impl Parse for Punct {
    fn parse(input: ParseStream) -> Result<Self> {
        input.step(|cursor| match cursor.punct() {
            Some((punct, rest)) => Ok((punct, rest)),
            None => Err(cursor.error("expected punctuation token")),
        })
    }
}

#[derive(Clone)]
pub struct Punct {
    ch: char,

}

struct Punctuated<T, P> {
    inner: Vec<(T, P)>,
    last: Option<Box<T>>,
}

impl <T, P> Punctuated<T, P> {
    fn new() -> Self {
        Punctuated{
            inner: vec![],
            last: None,
        }
    }


    pub fn push_value(&mut self, value: T) {

        self.last = Some(Box::new(value));
    }


    fn push_punct(&mut self, punctuation: P) {

        let last = self.last.take().unwrap();
        self.inner.push((*last, punctuation));
    }
    fn parse_terminated(input: ParseStream) -> Result<Self>
    where
        T: Parse,
        P: Parse,
    {
        Self::parse_terminated_with(input, T::parse)
    }


    pub fn parse_terminated_with<'a>(
        input:  ParseStream<'a>,
        parser: fn( ParseStream<'a>) ->  Result<T>,
    ) ->  Result<Self>
    where
        P: Parse,
    {
        let mut punctuated = Punctuated::new();

        loop {
            if input.is_empty() {
                break;
            }
            let value = parser(input)?;
            let p = punctuated.last.take().unwrap();
            punctuated.push_value(value);
            if input.is_empty() {
                break;
            }
            let punct  = input.parse()?;
            punctuated.push_punct(punct);
        }

        Ok(punctuated)
    }

}

struct ParamArgs {
    args: Vec<String>,
}

impl Parse for char {
    fn parse(input: ParseStream) -> Result<Self> {
        Ok('a')
    }
}

impl Parse for String {
    fn parse(input: ParseStream) -> Result<Self> {
        Ok('a'.to_string())
    }
}

impl Parse for ParamArgs {
    fn parse(input: ParseStream) -> Result<Self> {
        let punctuated = <Punctuated<_, char>>::parse_terminated(input)?;
        Ok(Self {
            args: punctuated.inner.into_iter().map(|e| e.0).collect(),
        })
    }
}



#[cfg(test)]
mod tests {
    use tokio::io::AsyncReadExt;
    use super::*;

    #[test]
    fn test_my() {
        let stream = "abcdaafsfsfafsfasfafsfs";
        let p1 = ParseBuffer::new(Cursor{rest: stream, _marker: PhantomData});

        println!("begin parsing:  {:?}", p1.peek());



    }
}

