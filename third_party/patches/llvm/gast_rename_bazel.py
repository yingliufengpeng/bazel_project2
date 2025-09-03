import gast
import ast 
import black

from pathlib import Path 

 


class Glob_visitor(gast.NodeTransformer):

    def visit_Call(self, node):
        if isinstance(node.func, gast.Name) and node.func.id == "glob":
           
            kws = node.keywords
            for kw in kws:
                if kw.arg == "allow_empty":
                    return self.generic_visit(node)

         
            node.keywords = node.keywords + [
                gast.keyword(arg="allow_empty", value=gast.Constant(value=True, kind=None))
            ]
            
            return node
     

            
        return self.generic_visit(node)
    
class CC_library_visitor1(gast.NodeTransformer):

    def visit_Call(self, node):
         
        
        if isinstance(node.func, gast.Name) and node.func.id == "cc_library":
            kws = node.keywords
            for kw in kws:
                if kw.arg == "includes":
                    return self.generic_visit(node)
            
            code = '''['include']  '''
            code_node = gast.parse(code).body[0].value
            code = ast.unparse(code_node)
            node.keywords = node.keywords + [
                gast.keyword(arg="includes", value=gast.List(elts=[gast.Constant(value='include', kind=None)], ctx=gast.Load()))
            ]

            return node
            
        return self.generic_visit(node)
    


class CC_library_visitor2(gast.NodeTransformer):

    def visit_Call(self, node):
         
        
        if isinstance(node.func, gast.Name) and node.func.id == "cc_library":
          
            is_found = False
            link_node = None 
            kws = node.keywords
            for kw in kws:
                if kw.arg == "linkopts"  :
                    is_found = True
                    link_node = kw
                    # return self.generic_visit(node)
            
            if is_found:
                pass 
            else:
                link_node = gast.keyword(arg="linkopts", value=gast.List(elts=[], ctx=gast.Load()))
                kws.append(
                    link_node
                )

            if isinstance(link_node.value, gast.List):
                visited = set()
                for n in link_node.value.elts:
                    visited.add(n.value)
                
                for n in ['-lpthread', '-ltinfo']:
                    if n in visited:
                        continue 
                    else:
                        visited.add(n)
                        link_node.value.elts.append(gast.Constant(value=n, kind=None))
                

            return node

           
            
        return self.generic_visit(node)

 

for f in Path('.').rglob('*.origin'):
    if 'test' in str(f) or 'third_party' in str(f):
        continue

    print(f'Processing file: {f}    ')


    with open(f, "r") as source:
        tree = gast.parse(source.read())   
        glob_visitor = Glob_visitor()
        c1 = CC_library_visitor1()
        c2 = CC_library_visitor2()
        tree = glob_visitor.visit(tree)
        tree = c1.visit(tree)
        tree = c2.visit(tree)


        # print(gast.dump(transformed_tree, indent=4))
        # print(ast.unparse(transformed_tree))


        out_f = str(f).replace('.origin', '')
        print(f'Writing to file: {out_f}    ')

        with open(out_f, 'w') as out_f:
            out_f.write(black.format_str(ast.unparse(gast.gast_to_ast(tree)), mode=black.Mode()))
            out_f.write('\n')