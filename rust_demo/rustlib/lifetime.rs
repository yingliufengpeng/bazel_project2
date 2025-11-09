

#[derive(Debug)]
struct MN<'a> {
    vec: Vec<&'a str>
}

impl <'a> MN<'a> {

    fn push_v<'b: 'a>(&mut self, v: &'b str) {
        self.vec.push(v);
    }
}

fn push_v<'a: 'c, 'b: 'a, 'c>(self_mn:&'c mut MN<'a>, v: &'b str) {
    self_mn.push_v(v);
}


fn f1() {
    let mut m = MN{vec: vec!["a", "b", "c", "d", "e", "f"]};
    let s = String::from("Jerry");
    let v = s.as_str();
    m.push_v("Hello");
    push_v(&mut m, v);
    println!("{:?}", m);
}



#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_my() {
        f1();
    }
}
