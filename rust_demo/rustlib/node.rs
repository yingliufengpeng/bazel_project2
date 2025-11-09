use std::cell::RefCell;
use std::rc::{Rc, Weak};
use std::collections::HashSet;

#[derive(Debug)]
pub struct Node<T> {
    pub value: T,
    pub parent: RefCell<Option<Weak<Node<T>>>>,
    pub children: RefCell<Vec<Rc<Node<T>>>>,
}

impl<T> Node<T> {
    pub fn new(value: T) -> Rc<Self> {
        Rc::new(Node {
            value,
            parent: RefCell::new(None),
            children: RefCell::new(Vec::new()),
        })
    }

    pub fn add_child(self: &Rc<Node<T>>, child: &Rc<Node<T>>) {
        // 子节点指向父节点
        *child.parent.borrow_mut() = Some(Rc::downgrade(self));
        // 父节点加入子节点
        if self.find_child(child).is_none() {
            self.children.borrow_mut().push(Rc::clone(child));

        }
    }

    pub fn add_to_parent(self:&Rc<Node<T>>, parent: &Rc<Node<T>>) {
        parent.add_child(self);
    }

    pub fn find_child(self: &Rc<Node<T>>, child: &Rc<Node<T>>) -> Option<Rc<Node<T>>> {
        self.children.borrow().iter().find(|e| Rc::ptr_eq(e, child)).cloned()
    }


    pub fn remove_child(self: &Rc<Self>, child: &Rc<Self>) -> bool {
        let mut children = self.children.borrow_mut();
        if let Some(pos) = children.iter().position(|c| Rc::ptr_eq(c, child)) {
            children.remove(pos);
            *child.parent.borrow_mut() = None; // 清空子节点的 parent
            true
        } else {
            false
        }
    }
}




#[cfg(test)]
mod tests {
    use super::*;

    #[derive(Debug,Hash,PartialEq,Eq)]
    struct Peng {
        name: String,
        age: i32,
    }

    #[derive(Debug,Hash,PartialEq,Eq)]
    struct Peng2<T> {
        name: String,
        age: T
    }


    #[test]
    fn test_new() {

        println!("test_new in Node.rs");

        let parent = Node::new(42);
        let child = Node::new(7);

        // Node::add_child(&parent, &child);
        parent.add_child(&child);

        println!("Parent value: {:#?}", parent.value);
        println!("Child's parent exists: {:?}", child.parent.borrow().is_some());

        println!("parent is {:?}", parent);

        assert!(parent.find_child(&child).is_some());

        assert!(parent.remove_child(&child));
        assert!(!parent.remove_child(&child));

        let mut set = HashSet::new();
        set.insert(Peng {name: "ddd".to_string(), age: 42});
        set.insert(Peng {name: "ddd".to_string(), age: 7});
        assert!(set.contains(&Peng {name: "ddd".to_string(), age: 7}));

        let mut set2 = HashSet::new();
        set2.insert(Peng2 {name: "ddd".to_string(), age: 333_u32});
        set2.remove(&Peng2 {name: "ddd".to_string(), age: 333_u32});

    }

}