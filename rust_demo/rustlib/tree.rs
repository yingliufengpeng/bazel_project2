
use std::collections::HashSet;
use std::hash::{Hash, Hasher};

#[derive(Debug, Clone)]
pub struct TreeNode {
    pub id: u32,
    pub name: String,
    pub parent_id: Option<u32>,
    pub children: HashSet<u32>,
}

impl TreeNode {
    pub fn from_id(id: u32) -> Self {
        Self {
            id,
            name: String::new(),
            parent_id: None,
            children: HashSet::new(),
        }
    }
}

// 唯一性基于 id
impl PartialEq for TreeNode {
    fn eq(&self, other: &Self) -> bool {
        self.id == other.id
    }
}
impl Eq for TreeNode {}

impl Hash for TreeNode {
    fn hash<H: Hasher>(&self, state: &mut H) {
        self.id.hash(state);
    }
}

#[derive(Debug)]
pub struct Tree {
    pub nodes: HashSet<TreeNode>,
}

impl Tree {
    pub fn new() -> Self {
        Self {
            nodes: HashSet::new(),
        }
    }

    pub fn add_node(&mut self, id: u32, name: &str, parent_id: Option<u32>) -> bool {
        if let Some(pid) = parent_id {
            // ✅ 使用 take + 再插入 修改 parent
            if let Some(mut parent) = self.nodes.take(&TreeNode::from_id(pid)) {
                parent.children.insert(id);
                self.nodes.insert(parent);
            } else {
                println!("⚠️ Parent {} not found", pid);
            }
        }

        self.nodes.insert(TreeNode {
            id,
            name: name.to_string(),
            parent_id,
            children: HashSet::new(),
        })
    }

    pub fn find_node(&self, id: u32) -> Option<&TreeNode> {
        self.nodes.get(&TreeNode::from_id(id))
    }

    pub fn print_tree(&self, id: u32, depth: usize) {
        if let Some(node) = self.find_node(id) {
            println!("{}- {} ({})", "  ".repeat(depth), node.name, node.id);
            for &cid in &node.children {
                self.print_tree(cid, depth + 1);
            }
        }
    }
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_tree() {
        let mut tree = Tree::new();
        tree.add_node(1, "Root", None);
        tree.add_node(2, "Child A", Some(1));
        tree.add_node(3, "Child B", Some(1));

        tree.add_node(4, "Sub A1", Some(2));

        assert!(tree.find_node(1).unwrap().children.contains(&2));
        assert!(tree.find_node(2).unwrap().children.contains(&4));

        tree.print_tree(1, 0);
    }
}
