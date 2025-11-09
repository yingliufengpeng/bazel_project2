# rust 生命周期规则 
        变性类型	允许替换的方向	举例
    ✅ 协变（Covariant）	'shorter 可替代 'longer	&'a T 是协变的
    🔁 逆变（Contravariant）	'longer 可替代 'shorter	函数参数位置的生命周期
    🚫 不变（Invariant）	不允许任何替换	Cell<T>、RefCell<T>

 
```rust
    trait Parse: Sized {
        fn parse(input: ParseStream) -> Result<Self>;
    }
    type ParseStream<'x> = &'x ParseBuffer<'x>;

    pub struct ParseBuffer<'a> {
        // 当前解析位置（用 'static 存储）
        cell: Cell<Cursor<'a>>,
        // 告诉编译器：我们“名义上”持有 'a 数据
        _marker: PhantomData<Cursor<'a>>,
    }
    impl <'a> ParseBuffer<'a> {
  
        fn parse<T: Parse>(&self) -> Result<T> {
            T::parse(self)
        }
     
    }
```
    
   
    当我的结构体这样定义的时候, 我的parse方法会编译失败, 因为&self引用的生命周期为 &'1 ParserBuffer<'a> 
    但是T::parse参数的入口点的要求的生命周期为   &'x ParserBuffer<'x> 又因为 ParserBuffer<'a> 是不变的,
    所以参数 &'x ParserBuffer<'x>就变为了  &'a ParserBuffer<'a>, 有上面的 生命周期规则, 我们可以知道必须
    满足 '1 : 'x 即 '1 : 'a 即 '1的生命周期必须高于'a的生命周期.  这个就是下面为什么要报错的结果.
    
```rust
        impl <'a> ParseBuffer<'a> {
        |       -- lifetime `'a` defined here
 
        133 |     fn parse<T: Parse>(&self) -> Result<T> {
        |                        - let's call the lifetime of this reference `'1`
        134 |         T::parse(self)
        |         ^^^^^^^^^^^^^^ argument requires that `'1` must outlive `'a`
        |
```


# 修正做法  
```rust
        pub struct ParseBuffer<'a> {
            // 当前解析位置（用 'static 存储）
            cell: Cell<Cursor<'static>>,
            // 告诉编译器：我们“名义上”持有 'a 数据
            _marker: PhantomData<Cursor<'a>>,
        }
```

    当我们把 Cell<Cursor<'a>>  改为 Cell<Cursor<'static>>时候, ParserBuffer<'a> 就变成协变类型.
    T::parse接收 &'1 ParserBuffer<'a>时,  参数的引用 &'x ParserBuffer<'x>, 由于'1的生命周期 < 'a
    的生命周期, 取x = 1, 我们有 ParserBuffer<'1> 小于 ParserBuffer<'a> 切  '1 < 'a 所以我们有 
    &'1 ParserBuffer<'1>  小于 &'a ParserBuffer<'a> 所以可以顺利通过编译.